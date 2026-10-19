#include "gsmartfirestation.h"
#include "ui_gsmartfirestation.h"

#include "statsdialog.h"
#include "vehiculedialog.h"
#include "piechartwidget.h"
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QScrollArea>
#include <QPushButton>

#include <QHeaderView>
#include <QMessageBox>
#include <QStatusBar>
#include <QTableWidgetItem>

// =====================================================================
//                        MODULE VÉHICULES
// =====================================================================

void GSmartFireStation::setupVehicules()
{
    m_vehiculePropose = -1;
    ui->frameMission->hide();

    // Colonnes du tableau : ID étroite, les autres se partagent la place
    QHeaderView *entete = ui->tableWidgetVehicules->horizontalHeader();
    entete->setSectionResizeMode(QHeaderView::Stretch);
    entete->setSectionResizeMode(0, QHeaderView::Fixed);
    entete->resizeSection(0, 70);
    entete->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_vehiculeEditIndex = -1;
    m_formVehicule = new QGroupBox("Fiche du véhicule", this);
    m_formVehicule->setStyleSheet("QGroupBox { border: 1px solid #D7DEE8; border-radius: 8px; margin-top: 10px; padding: 10px; font-weight: 600; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px; color: #1F4E79; }");
    m_vehicleId = new QLabel(prochainIdVehicule());
    m_vehicleImmat = new QLineEdit; m_vehicleImmat->setPlaceholderText("ex. 123 TU 456");
    m_vehicleType = new QComboBox; m_vehicleType->addItems(Vehicule::types());
    m_vehicleModele = new QLineEdit; m_vehicleModele->setPlaceholderText("Modèle / marque");
    m_vehicleEtat = new QComboBox; m_vehicleEtat->addItems(Vehicule::etats());
    m_vehicleDispo = new QComboBox; m_vehicleDispo->addItems(Vehicule::disponibilites());
    m_vehicleDate = new QDateEdit(QDate::currentDate().addMonths(3)); m_vehicleDate->setCalendarPopup(true); m_vehicleDate->setDisplayFormat("dd/MM/yyyy");
    // Permanent compact horizontal editor to preserve the table's height.
    QGridLayout *form = new QGridLayout(m_formVehicule);
    form->setContentsMargins(8,12,8,8); form->setHorizontalSpacing(10); form->setVerticalSpacing(5);
    auto addVehicleField = [&](int row, int col, const QString &name, QWidget *field) {
        QLabel *label = new QLabel(name); label->setStyleSheet("font-weight: normal;");
        QVBoxLayout *cell = new QVBoxLayout; cell->setContentsMargins(0,0,0,0); cell->setSpacing(2); cell->addWidget(label); cell->addWidget(field);
        QWidget *wrap = new QWidget; wrap->setLayout(cell); form->addWidget(wrap,row,col);
    };
    addVehicleField(0,0,"ID",m_vehicleId); addVehicleField(0,1,"Immatriculation",m_vehicleImmat); addVehicleField(0,2,"Type",m_vehicleType); addVehicleField(0,3,"Modèle",m_vehicleModele);
    addVehicleField(1,0,"État",m_vehicleEtat); addVehicleField(1,1,"Disponibilité",m_vehicleDispo); addVehicleField(1,2,"Date maintenance",m_vehicleDate);
    for (int c=0;c<4;++c) form->setColumnStretch(c,1);
    QPushButton *save = new QPushButton("Enregistrer"); save->setStyleSheet("QPushButton { background:#1F4E79; color:white; border-radius:5px; padding:6px 10px; font-weight:600; }");
    QPushButton *clear = new QPushButton("Effacer"); QHBoxLayout *actions = new QHBoxLayout; actions->addWidget(save); actions->addWidget(clear); form->addLayout(actions,1,3);
    ui->verticalLayoutVehiculesLeft->addWidget(m_formVehicule);
    // Keep the compact editor permanently visible below the table.
    m_formVehicule->show();
    QHBoxLayout *crud = ui->horizontalLayoutCrudVehicule;
    crud->removeWidget(ui->btnAjouterVehicule); crud->removeWidget(ui->btnModifierVehicule); crud->removeWidget(ui->btnSupprimerVehicule);
    ui->verticalLayoutVehiculesLeft->removeItem(crud);
    delete crud;
    QWidget *actionsCrud = new QWidget;
    QHBoxLayout *crudLayout = new QHBoxLayout(actionsCrud);
    crudLayout->setContentsMargins(0, 8, 0, 0);
    crudLayout->setSpacing(10);
    crudLayout->addWidget(ui->btnAjouterVehicule);
    crudLayout->addWidget(ui->btnModifierVehicule);
    crudLayout->addWidget(ui->btnSupprimerVehicule);
    crudLayout->addStretch(1);
    // Actions remain visible immediately below the vehicle table.
    ui->verticalLayoutVehiculesLeft->insertWidget(ui->verticalLayoutVehiculesLeft->indexOf(m_formVehicule), actionsCrud);
    connect(save, SIGNAL(clicked()), this, SLOT(enregistrerVehiculeInline())); connect(clear, SIGNAL(clicked()), this, SLOT(annulerVehiculeInline()));
    ui->btnStatsVehicule->hide(); ui->progressStatVehDispo->hide(); ui->labelStatVehDispo->hide(); ui->labelStatVehMaint->hide();
    m_vehiculeStatsChart = new PieChartWidget("VÉHICULES", ui->frameStatsVehicules);
    m_vehiculeStatsChart->setMinimumHeight(390);
    QScrollArea *statsScroll = new QScrollArea(ui->frameStatsVehicules);
    statsScroll->setWidgetResizable(true);
    statsScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    statsScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    statsScroll->setFrameShape(QFrame::NoFrame);
    QWidget *statsContent = new QWidget;
    QVBoxLayout *statsContentLayout = new QVBoxLayout(statsContent);
    statsContentLayout->setContentsMargins(4, 4, 4, 4);
    statsContentLayout->addWidget(m_vehiculeStatsChart);
    statsScroll->setWidget(statsContent);
    ui->verticalLayoutStatsVehicules->insertWidget(1, statsScroll, 1);
    ui->frameStatsVehicules->setMinimumWidth(285);
    ui->frameStatsVehicules->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
}

// Données de démonstration (à remplacer plus tard par la base de données)
void GSmartFireStation::chargerVehiculesExemple()
{
    m_vehicules.clear();
    m_vehicules.append(Vehicule("V001", "123 TU 456", "Fourgon", "Renault", "Bon", "Disponible", QDate(2026, 11, 10)));
    m_vehicules.append(Vehicule("V002", "124 TU 457", "Camion", "Iveco", "Bon", "En mission", QDate(2026, 10, 22)));
    m_vehicules.append(Vehicule("V003", "125 TU 458", "Ambulance", "Mercedes", "À contrôler", "Disponible", QDate(2026, 10, 2)));
    m_vehicules.append(Vehicule("V004", "126 TU 459", "Citerne", "MAN", "Bon", "Disponible", QDate(2026, 12, 18)));
    m_vehicules.append(Vehicule("V005", "127 TU 460", "Ambulance", "Renault", "Bon", "Disponible", QDate(2027, 1, 15)));
    m_vehicules.append(Vehicule("V006", "128 TU 461", "Échelle", "Iveco", "À contrôler", "En maintenance", QDate(2026, 10, 29)));
    m_vehicules.append(Vehicule("V007", "129 TU 462", "Fourgon", "MAN", "Bon", "En maintenance", QDate(2026, 10, 12)));
}

// Numéro de la ligne sélectionnée dans le tableau (-1 si aucune)
int GSmartFireStation::vehiculeSelectionne()
{
    int ligne = ui->tableWidgetVehicules->currentRow();
    if (ligne < 0 || ligne >= m_vehicules.size())
        return -1;
    return ligne;
}

// Prochain ID libre : V001, V002, ...
QString GSmartFireStation::prochainIdVehicule()
{
    int max = 0;
    for (int i = 0; i < m_vehicules.size(); i++) {
        int numero = m_vehicules[i].id().mid(1).toInt();
        if (numero > max)
            max = numero;
    }
    return QString("V%1").arg(max + 1, 3, 10, QChar('0'));
}

// ------------------------------------------------------------------ affichage
void GSmartFireStation::refreshVehiculesTable()
{
    int ligneCourante = ui->tableWidgetVehicules->currentRow();
    QColor noir("#1F1F1F");

    ui->tableWidgetVehicules->setRowCount(m_vehicules.size());
    for (int r = 0; r < m_vehicules.size(); r++) {
        Vehicule v = m_vehicules[r];

        // Couleur de l'état
        QColor couleurEtat = noir;
        bool etatGras = false;
        if (v.etat() == "À contrôler") {
            couleurEtat = QColor("#B45309");
            etatGras = true;
        } else if (v.etat() == "Hors service") {
            couleurEtat = QColor("#C00000");
            etatGras = true;
        }

        // Couleur de la disponibilité
        QColor couleurDispo("#C00000"); // En maintenance
        if (v.disponibilite() == "Disponible")
            couleurDispo = QColor("#2E7D32");
        else if (v.disponibilite() == "En mission")
            couleurDispo = QColor("#B45309");

        // Date de maintenance : orange si proche, rouge si dépassée
        QColor couleurDate = noir;
        bool dateGras = false;
        if (v.disponibilite() != "En maintenance" && v.maintenanceProche()) {
            dateGras = true;
            if (v.dateMaintenance() < QDate::currentDate())
                couleurDate = QColor("#C00000");
            else
                couleurDate = QColor("#B45309");
        }

        ui->tableWidgetVehicules->setItem(r, 0, creerItem(v.id(), noir, false));
        ui->tableWidgetVehicules->setItem(r, 1, creerItem(v.immatriculation(), noir, false));
        ui->tableWidgetVehicules->setItem(r, 2, creerItem(v.type(), noir, false));
        ui->tableWidgetVehicules->setItem(r, 3, creerItem(v.modele(), noir, false));
        ui->tableWidgetVehicules->setItem(r, 4, creerItem(v.etat(), couleurEtat, etatGras));
        ui->tableWidgetVehicules->setItem(r, 5, creerItem(v.disponibilite(), couleurDispo, true));
        ui->tableWidgetVehicules->setItem(r, 6, creerItem(v.dateMaintenance().toString("dd/MM/yyyy"), couleurDate, dateGras));
    }
    if (ligneCourante >= 0 && ligneCourante < m_vehicules.size())
        ui->tableWidgetVehicules->selectRow(ligneCourante);

    filtrerVehicules();

    // Panneau "Statistiques véhicules"
    int dispo = 0;
    int maintenance = 0;
    for (int i = 0; i < m_vehicules.size(); i++) {
        if (m_vehicules[i].disponibilite() == "Disponible")
            dispo++;
        else if (m_vehicules[i].disponibilite() == "En maintenance")
            maintenance++;
    }
    int total = m_vehicules.size();
    int maximum = total;
    if (maximum < 1)
        maximum = 1;
    ui->labelStatVehDispo->setText(QString("Disponibles : %1 / %2").arg(dispo).arg(total));
    ui->progressStatVehDispo->setMaximum(maximum); ui->progressStatVehDispo->setValue(dispo);
    ui->labelStatVehMaint->setText(QString("En maintenance : %1").arg(maintenance));
    QStringList types = Vehicule::types(); QStringList labels; QList<int> values;
    for (int t=0; t<types.size(); ++t) { int count=0; for (int i=0;i<m_vehicules.size();++i) if (m_vehicules[i].type()==types[t]) ++count; labels << types[t]; values << count; }
    static_cast<PieChartWidget*>(m_vehiculeStatsChart)->setData(labels, values);
    refreshVehiculePropose();
}

// ------------------------------------------------------------------ CRUD
void GSmartFireStation::on_btnAjouterVehicule_clicked()
{
    annulerVehiculeInline(); m_vehiculeEditIndex = -1; m_vehicleId->setText(prochainIdVehicule());
    m_formVehicule->setTitle("Fiche du véhicule — ajoutez ou modifiez les champs ci-dessous"); m_formVehicule->show(); m_vehicleImmat->setFocus();
}

void GSmartFireStation::on_btnModifierVehicule_clicked()
{
    int i = vehiculeSelectionne();
    if (i < 0) { QMessageBox::information(this, "Modifier un véhicule", "Sélectionnez d'abord un véhicule dans la liste."); return; }
    const Vehicule v=m_vehicules[i]; m_vehiculeEditIndex=i; m_vehicleId->setText(v.id());
    m_vehicleImmat->setText(v.immatriculation()); m_vehicleType->setCurrentText(v.type()); m_vehicleModele->setText(v.modele());
    m_vehicleEtat->setCurrentText(v.etat()); m_vehicleDispo->setCurrentText(v.disponibilite()); m_vehicleDate->setDate(v.dateMaintenance());
    m_formVehicule->setTitle("Modification du véhicule " + v.id());
    m_formVehicule->show();
}

void GSmartFireStation::enregistrerVehiculeInline()
{
    QString immat=m_vehicleImmat->text().trimmed().toUpper();
    if (immat.isEmpty() || m_vehicleModele->text().trimmed().isEmpty()) { QMessageBox::warning(this,"Saisie incorrecte","L'immatriculation et le modèle sont obligatoires."); return; }
    for (int i=0;i<m_vehicules.size();++i) if (i!=m_vehiculeEditIndex && m_vehicules[i].immatriculation().compare(immat,Qt::CaseInsensitive)==0) { QMessageBox::warning(this,"Doublon","Cette immatriculation existe déjà."); return; }
    Vehicule v(m_vehicleId->text(),immat,m_vehicleType->currentText(),m_vehicleModele->text().trimmed(),m_vehicleEtat->currentText(),m_vehicleDispo->currentText(),m_vehicleDate->date());
    if (m_vehiculeEditIndex>=0 && m_vehiculeEditIndex<m_vehicules.size()) { m_vehicules[m_vehiculeEditIndex]=v; statusBar()->showMessage("Véhicule modifié.",4000); }
    else { m_vehicules.append(v); m_vehiculeEditIndex=m_vehicules.size()-1; statusBar()->showMessage("Véhicule ajouté.",4000); }
    refreshVehiculesTable(); ui->tableWidgetVehicules->selectRow(m_vehiculeEditIndex); m_formVehicule->setTitle("Fiche du véhicule — ajoutez ou modifiez les champs ci-dessous"); m_formVehicule->show();
}

void GSmartFireStation::annulerVehiculeInline()
{
    m_vehiculeEditIndex=-1; m_vehicleId->setText(prochainIdVehicule()); m_vehicleImmat->clear(); m_vehicleModele->clear();
    m_vehicleType->setCurrentIndex(0); m_vehicleEtat->setCurrentIndex(0); m_vehicleDispo->setCurrentText("Disponible"); m_vehicleDate->setDate(QDate::currentDate().addMonths(3));
    m_formVehicule->setTitle("Fiche du véhicule — ajoutez ou modifiez les champs ci-dessous");
    m_formVehicule->show();
}

void GSmartFireStation::on_btnSupprimerVehicule_clicked()
{
    int i = vehiculeSelectionne();
    if (i < 0) {
        QMessageBox::information(this, "Supprimer un véhicule",
                                 "Sélectionnez d'abord un véhicule dans la liste.");
        return;
    }
    int reponse = QMessageBox::question(this, "Supprimer un véhicule",
                                        "Voulez-vous vraiment supprimer le véhicule "
                                        + m_vehicules[i].immatriculation() + " ?");
    if (reponse != QMessageBox::Yes)
        return;

    m_vehicules.removeAt(i);
    ui->tableWidgetVehicules->setCurrentCell(-1, -1);
    refreshVehiculesTable();
    statusBar()->showMessage("Véhicule supprimé.", 5000);
}

void GSmartFireStation::on_tableWidgetVehicules_cellDoubleClicked(int, int)
{
    on_btnModifierVehicule_clicked(); // double-clic = modifier
}

// ------------------------------------------------------------------ recherche
// Cache les lignes qui ne contiennent pas le texte cherché (immatriculation, type, modèle ou ID)
void GSmartFireStation::filtrerVehicules()
{
    QString texte = ui->lineEditRechercheVehicule->text().trimmed();
    int visibles = 0;
    for (int r = 0; r < m_vehicules.size(); r++) {
        Vehicule v = m_vehicules[r];
        bool trouve = texte == ""
                      || v.immatriculation().contains(texte, Qt::CaseInsensitive)
                      || v.type().contains(texte, Qt::CaseInsensitive)
                      || v.modele().contains(texte, Qt::CaseInsensitive)
                      || v.id().contains(texte, Qt::CaseInsensitive);
        ui->tableWidgetVehicules->setRowHidden(r, !trouve);
        if (trouve)
            visibles++;
    }
    if (texte != "")
        statusBar()->showMessage(QString("%1 résultat(s)").arg(visibles), 4000);
    else
        statusBar()->clearMessage();
}

void GSmartFireStation::on_btnRechercherVehicule_clicked()
{
    filtrerVehicules();
}

void GSmartFireStation::on_lineEditRechercheVehicule_textChanged(const QString &)
{
    filtrerVehicules(); // la recherche se met à jour pendant la frappe
}

// ------------------------------------------------------------------ tri (tri à bulles)
// Retourne vrai si 'a' doit passer après 'b' selon le critère choisi
bool GSmartFireStation::doitEchangerVehicules(Vehicule a, Vehicule b, int critere)
{
    if (critere == 0) // État : Bon, À contrôler, Hors service
        return Vehicule::etats().indexOf(a.etat()) > Vehicule::etats().indexOf(b.etat());
    // Type : Fourgon, Camion, Ambulance, Citerne, Échelle
    return Vehicule::types().indexOf(a.type()) > Vehicule::types().indexOf(b.type());
}

void GSmartFireStation::on_btnTrierVehicule_clicked()
{
    int critere = ui->comboTriVehicule->currentIndex();
    int n = m_vehicules.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (doitEchangerVehicules(m_vehicules[j], m_vehicules[j + 1], critere)) {
                Vehicule temp = m_vehicules[j];
                m_vehicules[j] = m_vehicules[j + 1];
                m_vehicules[j + 1] = temp;
            }
        }
    }
    ui->tableWidgetVehicules->setCurrentCell(-1, -1);
    refreshVehiculesTable();
    statusBar()->showMessage("Liste triée.", 4000);
}

// ------------------------------------------------------------------ export PDF
void GSmartFireStation::on_btnExportVehicule_clicked()
{
    exporterTableauPdf(ui->tableWidgetVehicules, "Liste des véhicules", "vehicules.pdf");
}

// ------------------------------------------------------------------ statistiques
StatCritere GSmartFireStation::statVehiculesParEtat()
{
    QStringList reelles;
    for (int i = 0; i < m_vehicules.size(); i++)
        reelles << m_vehicules[i].etat();
    return compterParValeur("État", Vehicule::etats(), reelles);
}

StatCritere GSmartFireStation::statVehiculesParDispo()
{
    QStringList reelles;
    for (int i = 0; i < m_vehicules.size(); i++)
        reelles << m_vehicules[i].disponibilite();
    return compterParValeur("Disponibilité", Vehicule::disponibilites(), reelles);
}

void GSmartFireStation::on_btnStatsVehicule_clicked()
{
    // Les statistiques sont affichées en permanence dans le panneau latéral.
}

// ------------------------------------------------------------------ métier : choix adapté à la mission
// Propose un véhicule DISPONIBLE, en BON ÉTAT, dont le type correspond à l'intervention.
// On teste les types par ordre de préférence ; parmi les candidats on prend celui dont
// la prochaine maintenance est la plus lointaine.
void GSmartFireStation::refreshVehiculePropose()
{
    m_vehiculePropose = -1;
    ui->frameMission->hide();
    QStringList typesPreferes = Vehicule::typesPourIntervention(ui->comboIntervention->currentText());

    for (int t = 0; t < typesPreferes.size() && m_vehiculePropose < 0; t++) {
        int meilleur = -1;
        for (int i = 0; i < m_vehicules.size(); i++) {
            Vehicule v = m_vehicules[i];
            if (v.type() == typesPreferes[t] && v.disponibilite() == "Disponible" && v.etat() == "Bon") {
                if (meilleur < 0 || v.dateMaintenance() > m_vehicules[meilleur].dateMaintenance())
                    meilleur = i;
            }
        }
        m_vehiculePropose = meilleur; // reste -1 si aucun véhicule de ce type
    }

    if (m_vehiculePropose < 0) {
        ui->labelVehiculePropose->setText("Aucun véhicule adapté");
        ui->labelVehiculeInfo->setText("Aucun véhicule disponible en bon état pour cette intervention.");
        setLabelClass(ui->labelVehiculeInfo, "textWarning");
        ui->btnUtiliserVehicule->setEnabled(false);
        return;
    }

    Vehicule v = m_vehicules[m_vehiculePropose];
    ui->labelVehiculePropose->setText(v.id() + " — " + v.type() + " " + v.modele());
    ui->labelVehiculeInfo->setText(v.disponibilite() + " • État : " + v.etat());
    setLabelClass(ui->labelVehiculeInfo, "textSuccess");
    ui->btnUtiliserVehicule->setEnabled(true);
}

void GSmartFireStation::on_comboIntervention_currentIndexChanged(int)
{
    refreshVehiculePropose();
}

void GSmartFireStation::on_btnUtiliserVehicule_clicked()
{
    if (m_vehiculePropose < 0)
        return;

    Vehicule v = m_vehicules[m_vehiculePropose];
    QString intervention = ui->comboIntervention->currentText();
    int reponse = QMessageBox::question(this, "Affecter le véhicule",
                                        "Affecter " + v.id() + " (" + v.type() + " " + v.modele()
                                        + ") à l'intervention « " + intervention + " » ?");
    if (reponse != QMessageBox::Yes)
        return;

    m_vehicules[m_vehiculePropose].setDisponibilite("En mission");
    refreshVehiculesTable();
    statusBar()->showMessage("Véhicule " + v.id() + " affecté : " + intervention + ".", 6000);
}
