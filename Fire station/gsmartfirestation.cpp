#include "gsmartfirestation.h"
#include "ui_gsmartfirestation.h"

#include "pdfexport.h"
#include "statsdialog.h"
#include "styleutils.h"

#include <QDesktopServices>
#include <QFileDialog>
#include <QIcon>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPixmap>
#include <QProgressBar>
#include <QStandardPaths>
#include <QStatusBar>
#include <QStyle>
#include <QTableWidget>
#include <QUrl>

GSmartFireStation::GSmartFireStation(QWidget *parent)
     : QMainWindow(parent), ui(new Ui::GSmartFireStation), m_personnelEditIndex(-1)
{
    ui->setupUi(this);
    repolish(this); // applique les class="..." du .ui au fichier style.qss

    setWindowIcon(QIcon(":/images/icon.png"));
    QPixmap logo(":/images/logo.png");
    ui->labelLogo->setPixmap(logo.scaledToWidth(192, Qt::SmoothTransformation));

    // Préparation de chaque module (le code vient des projets individuels)
    ui->frameSurcharge->hide();
    setupPersonnel();
    setupVehicules();
    chargerPersonnelExemple();
    chargerVehiculesExemple();
    refreshPersonnelTable();
    refreshVehiculesTable();

    goToPage(0); // on démarre sur le Dashboard
}

GSmartFireStation::~GSmartFireStation()
{
    delete ui;
}

// ===================== NAVIGATION =====================
// Affiche la page d'index donné du QStackedWidget : 0 = Dashboard, 1 = Personnel, 2 = Véhicules
void GSmartFireStation::goToPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    statusBar()->clearMessage();

    // Le menu latéral montre la page affichée
    ui->btnNavDashboard->setChecked(index == 0);
    ui->btnNavPersonnel->setChecked(index == 1);
    ui->btnNavVehicules->setChecked(index == 2);

    if (index == 0)
        refreshDashboard(); // le Dashboard est recalculé à chaque affichage
}

void GSmartFireStation::on_btnNavDashboard_clicked()
{
    goToPage(0);
}

void GSmartFireStation::on_btnNavPersonnel_clicked()
{
    goToPage(1);
}

void GSmartFireStation::on_btnNavVehicules_clicked()
{
    goToPage(2);
}

void GSmartFireStation::on_btnGererPersonnel_clicked()
{
    goToPage(1);
}

void GSmartFireStation::on_btnGererVehicules_clicked()
{
    goToPage(2);
}

void GSmartFireStation::on_btnRetourPersonnel_clicked()
{
    goToPage(0);
}

void GSmartFireStation::on_btnRetourVehicule_clicked()
{
    goToPage(0);
}

void GSmartFireStation::on_btnQuitter_clicked()
{
    int reponse = QMessageBox::question(this, "Quitter", "Voulez-vous vraiment quitter l'application ?");
    if (reponse == QMessageBox::Yes)
        close();
}

// ===================== DASHBOARD =====================
// Met à jour une barre de progression et son texte "valeur/total"
void GSmartFireStation::majBarre(QProgressBar *barre, QLabel *label, int valeur, int total)
{
    label->setText(QString("%1/%2").arg(valeur).arg(total));
    if (total < 1)
        total = 1;
    barre->setMaximum(total);
    barre->setValue(valeur);
}

// Ajoute une ligne dans la liste des alertes (texte coloré)
void GSmartFireStation::ajouterAlerte(const QString &texte, const QString &couleur)
{
    QListWidgetItem *ligne = new QListWidgetItem("●  " + texte);
    ligne->setForeground(QColor(couleur));
    ui->listAlertes->addItem(ligne);
}

void GSmartFireStation::refreshDashboard()
{
    // --- Comptage du personnel ---
    int personnelDispo = 0;
    int personnelMission = 0;
    for (int i = 0; i < m_personnel.size(); i++) {
        if (m_personnel[i].disponibilite() == "Disponible")
            personnelDispo++;
        else if (m_personnel[i].disponibilite() == "En mission")
            personnelMission++;
    }

    // --- Comptage des véhicules ---
    int vehiculesDispo = 0;
    int vehiculesMaintenance = 0;
    for (int i = 0; i < m_vehicules.size(); i++) {
        if (m_vehicules[i].disponibilite() == "Disponible")
            vehiculesDispo++;
        else if (m_vehicules[i].disponibilite() == "En maintenance")
            vehiculesMaintenance++;
    }

    int nbPersonnel = m_personnel.size();
    int nbVehicules = m_vehicules.size();

    // --- Cartes du haut ---
    ui->labelNbPersonnel->setText(QString::number(nbPersonnel));
    ui->labelPersonnelDispoDetail->setText(QString("Disponibles : %1").arg(personnelDispo));
    ui->labelNbVehicules->setText(QString::number(nbVehicules));
    ui->labelVehiculesDispoDetail->setText(QString("Disponibles : %1").arg(vehiculesDispo));

    // --- Barres de disponibilité ---
    majBarre(ui->progressPersonnelDispo, ui->labelPersonnelDispoCount, personnelDispo, nbPersonnel);
    majBarre(ui->progressPersonnelMission, ui->labelPersonnelMissionCount, personnelMission, nbPersonnel);
    majBarre(ui->progressVehiculesDispo, ui->labelVehiculesDispoCount, vehiculesDispo, nbVehicules);
    majBarre(ui->progressVehiculesMaint, ui->labelVehiculesMaintCount, vehiculesMaintenance, nbVehicules);

    // --- Alertes ---
    ui->listAlertes->clear();
    int nbAlertes = 0;
    int seuil = ui->spinSeuil->value();
    for (int i = 0; i < m_personnel.size(); i++) {
        if (m_personnel[i].charge() >= seuil) {
            ajouterAlerte(QString("Personnel %1 : charge opérationnelle élevée (%2 %)")
                              .arg(m_personnel[i].id()).arg(m_personnel[i].charge()), "#C00000");
            nbAlertes++;
        }
    }
    for (int i = 0; i < m_vehicules.size(); i++) {
        if (m_vehicules[i].disponibilite() != "En maintenance" && m_vehicules[i].maintenanceProche()) {
            ajouterAlerte(QString("Véhicule %1 : maintenance à prévoir (%2)")
                              .arg(m_vehicules[i].id())
                              .arg(m_vehicules[i].dateMaintenance().toString("dd/MM/yyyy")), "#C00000");
            nbAlertes++;
        }
    }
    ajouterAlerte("Préparer un véhicule pour une intervention", "#B45309");
    ui->labelNbAlertes->setText(QString::number(nbAlertes));
}

// Bouton "Voir les statistiques" : statistiques des deux modules dans une seule fenêtre
void GSmartFireStation::on_btnVoirStats_clicked()
{
    StatCritere c1 = statPersonnelParDispo();
    c1.nom = "Personnel — Disponibilité";
    StatCritere c2 = statPersonnelParGrade();
    c2.nom = "Personnel — Grade";
    StatCritere c3 = statVehiculesParDispo();
    c3.nom = "Véhicules — Disponibilité";
    StatCritere c4 = statVehiculesParEtat();
    c4.nom = "Véhicules — État";

    QList<StatCritere> criteres;
    criteres << c1 << c2 << c3 << c4;
    StatsDialog fenetre("Statistiques de la station", criteres, this);
    fenetre.exec();
}

// ===================== OUTILS COMMUNS =====================

// Crée une case de tableau avec une couleur de texte (et éventuellement en gras)
QTableWidgetItem *GSmartFireStation::creerItem(const QString &texte, const QColor &couleur, bool gras)
{
    QTableWidgetItem *item = new QTableWidgetItem(texte);
    item->setForeground(couleur);
    if (gras) {
        QFont police = item->font();
        police.setBold(true);
        item->setFont(police);
    }
    return item;
}

// Change la "class" d'un label (pour qu'il prenne un autre style du fichier style.qss)
void GSmartFireStation::setLabelClass(QLabel *label, const QString &classe)
{
    label->setProperty("class", classe);
    label->style()->unpolish(label);
    label->style()->polish(label);
}

// Exporte en PDF les lignes visibles d'un tableau (donc le résultat d'une recherche / d'un tri)
void GSmartFireStation::exporterTableauPdf(QTableWidget *table, const QString &titre, const QString &nomFichier)
{
    QStringList entetes;
    for (int c = 0; c < table->columnCount(); c++)
        entetes << table->horizontalHeaderItem(c)->text();

    QList<QStringList> lignes;
    for (int r = 0; r < table->rowCount(); r++) {
        if (table->isRowHidden(r))
            continue;
        QStringList ligne;
        for (int c = 0; c < table->columnCount(); c++)
            ligne << table->item(r, c)->text();
        lignes << ligne;
    }
    if (lignes.size() == 0) {
        QMessageBox::information(this, "Export PDF", "Aucune donnée à exporter.");
        return;
    }

    QString dossier = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString chemin = QFileDialog::getSaveFileName(this, "Exporter en PDF",
                                                  dossier + "/" + nomFichier, "Fichiers PDF (*.pdf)");
    if (chemin == "")
        return; // l'utilisateur a annulé
    if (!chemin.endsWith(".pdf"))
        chemin += ".pdf";

    if (!creerPdfTableau(chemin, titre, entetes, lignes)) {
        QMessageBox::warning(this, "Export PDF", "Impossible de créer le fichier PDF.");
        return;
    }
    statusBar()->showMessage("PDF exporté : " + chemin, 6000);
    int reponse = QMessageBox::question(this, "Export PDF",
                                        "Le PDF a été créé.\nVoulez-vous l'ouvrir maintenant ?");
    if (reponse == QMessageBox::Yes)
        QDesktopServices::openUrl(QUrl::fromLocalFile(chemin));
}
