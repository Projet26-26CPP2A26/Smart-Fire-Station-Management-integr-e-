#include "gsmartfirestation.h"
#include "ui_gsmartfirestation.h"

#include "statsdialog.h"
#include "piechartwidget.h"

#include <QHeaderView>
#include <QMessageBox>
#include <QStatusBar>
#include <QTableWidgetItem>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QSizePolicy>
#include <QScrollArea>

// =====================================================================
//                        MODULE PERSONNEL
// =====================================================================

void GSmartFireStation::setupPersonnel()
{
    // Colonnes du tableau : ID étroite, les autres se partagent la place
    QHeaderView *entete = ui->tableWidgetPersonnel->horizontalHeader();
    entete->setSectionResizeMode(QHeaderView::Stretch);
    entete->setSectionResizeMode(0, QHeaderView::Fixed);
    entete->resizeSection(0, 70);
    entete->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    // Formulaire permanent : l'ajout et la modification se font directement dans la page.
    m_formPersonnel = new QGroupBox("Fiche du personnel — remplissez les champs puis validez");
    m_formPersonnel->setObjectName("formPersonnelInline");
    m_formPersonnel->setStyleSheet("QGroupBox { border: 1px solid #D7DEE8; border-radius: 8px; margin-top: 10px; padding: 10px; font-weight: 600; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px; color: #1F4E79; }");
    m_formId = new QLabel(prochainIdPersonnel());
    m_formNom = new QLineEdit; m_formNom->setPlaceholderText("Nom");
    m_formPrenom = new QLineEdit; m_formPrenom->setPlaceholderText("Prénom");
    m_formGrade = new QComboBox; m_formGrade->addItems(Personnel::grades());
    m_formPoste = new QComboBox; m_formPoste->addItems(Personnel::postes());
    m_formTelephone = new QLineEdit; m_formTelephone->setPlaceholderText("8 chiffres");
    m_formEmail = new QLineEdit; m_formEmail->setPlaceholderText("prenom.nom@firestation.tn");
    m_formMotDePasse = new QLineEdit; m_formMotDePasse->setPlaceholderText("4 caractères minimum"); m_formMotDePasse->setEchoMode(QLineEdit::Password);
    m_formDisponibilite = new QComboBox; m_formDisponibilite->addItems(Personnel::disponibilites());
    m_formMissions = new QSpinBox; m_formMissions->setRange(0, 10); m_formMissions->setToolTip("Chaque mission ajoute 20 % de charge opérationnelle");
    // Compact, permanent editor: fields are arranged horizontally in two rows.
    QGridLayout *formGrid = new QGridLayout(m_formPersonnel);
    formGrid->setContentsMargins(8, 12, 8, 8); formGrid->setHorizontalSpacing(8); formGrid->setVerticalSpacing(5);
    auto addField = [&](int row, int col, const QString &name, QWidget *field) {
        QLabel *label = new QLabel(name); label->setStyleSheet("font-weight: normal;");
        QVBoxLayout *cell = new QVBoxLayout; cell->setContentsMargins(0,0,0,0); cell->setSpacing(2); cell->addWidget(label); cell->addWidget(field);
        QWidget *wrap = new QWidget; wrap->setLayout(cell); formGrid->addWidget(wrap, row, col);
    };
    addField(0,0,"ID",m_formId); addField(0,1,"Nom",m_formNom); addField(0,2,"Prénom",m_formPrenom);
    addField(0,3,"Grade",m_formGrade); addField(0,4,"Poste",m_formPoste);
    addField(1,0,"Téléphone",m_formTelephone); addField(1,1,"Email",m_formEmail); addField(1,2,"Mot de passe",m_formMotDePasse);
    addField(1,3,"Disponibilité",m_formDisponibilite); addField(1,4,"Missions",m_formMissions);
    for (int c=0;c<5;++c) formGrid->setColumnStretch(c,1);
    QPushButton *valider = new QPushButton("Enregistrer"); valider->setObjectName("btnValiderPersonnelInline"); valider->setStyleSheet("QPushButton { background:#1F4E79; color:white; border-radius:5px; padding:6px 10px; font-weight:600; }");
    QPushButton *annuler = new QPushButton("Effacer"); annuler->setObjectName("btnAnnulerPersonnelInline");
    QHBoxLayout *actions = new QHBoxLayout; actions->addWidget(valider); actions->addWidget(annuler); formGrid->addLayout(actions, 2, 0, 1, 5);
    ui->verticalLayoutPersonnelLeft->removeWidget(m_formPersonnel);
    ui->verticalLayoutPersonnelLeft->addWidget(m_formPersonnel);
    // Keep the compact editor permanently visible below the table/actions.
    m_formPersonnel->show();
    // Déplacer les actions CRUD dans la colonne de droite, sous le formulaire.
    QHBoxLayout *crud = ui->horizontalLayoutCrudPersonnel;
    crud->removeWidget(ui->btnAjouterPersonnel); crud->removeWidget(ui->btnModifierPersonnel); crud->removeWidget(ui->btnSupprimerPersonnel);
    ui->verticalLayoutPersonnelLeft->removeItem(crud);
    delete crud;
    QWidget *actionsCrud = new QWidget;
    QHBoxLayout *crudLayout = new QHBoxLayout(actionsCrud);
    crudLayout->setContentsMargins(0, 8, 0, 0);
    crudLayout->setSpacing(10);
    crudLayout->addWidget(ui->btnAjouterPersonnel);
    crudLayout->addWidget(ui->btnModifierPersonnel);
    crudLayout->addWidget(ui->btnSupprimerPersonnel);
    crudLayout->addStretch(1);
    // Keep the table in the main area and put its actions directly underneath.
    ui->verticalLayoutPersonnelLeft->insertWidget(ui->verticalLayoutPersonnelLeft->indexOf(m_formPersonnel), actionsCrud);
    connect(valider, SIGNAL(clicked()), this, SLOT(enregistrerPersonnelInline()));
    connect(annuler, SIGNAL(clicked()), this, SLOT(annulerPersonnelInline()));

    // Statistiques circulaires toujours visibles, avec une légende par grade.
    ui->horizontalLayoutStatDispo->setEnabled(false); ui->labelStatDispo->hide(); ui->progressStatDispo->hide();
    ui->horizontalLayoutStatMission->setEnabled(false); ui->labelStatMission->hide(); ui->progressStatMission->hide();
    m_personnelStatsChart = new PieChartWidget("PERSONNEL", ui->frameStatsPersonnel);
    m_personnelStatsLegend = new QLabel(ui->frameStatsPersonnel);
    m_personnelStatsLegend->setWordWrap(true);
    m_personnelStatsLegend->hide();
    m_personnelStatsChart->setMinimumHeight(390);
    QScrollArea *statsScroll = new QScrollArea(ui->frameStatsPersonnel);
    statsScroll->setWidgetResizable(true);
    statsScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    statsScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    statsScroll->setFrameShape(QFrame::NoFrame);
    QWidget *statsContent = new QWidget;
    QVBoxLayout *statsContentLayout = new QVBoxLayout(statsContent);
    statsContentLayout->setContentsMargins(4, 4, 4, 4);
    statsContentLayout->addWidget(m_personnelStatsChart);
    statsScroll->setWidget(statsContent);
    ui->verticalLayoutStatsPersonnel->insertWidget(1, statsScroll, 1);
    ui->frameStatsPersonnel->setMinimumWidth(285);
    ui->btnStatsPersonnel->hide();
    ui->frameSurcharge->hide();
    ui->frameStatsPersonnel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

}

// Données de démonstration (à remplacer plus tard par la base de données)
void GSmartFireStation::chargerPersonnelExemple()
{
    m_personnel.clear();
    m_personnel.append(Personnel("P001", "Ben Ali", "Ahmed", "Capitaine", "Chef de garde", "22 000 111",
                              "ahmed.benali@firestation.tn", "pass1234", "Disponible", 1));
    m_personnel.append(Personnel("P002", "Trabelsi", "Yassine", "Sergent", "Intervention", "22 000 222",
                              "yassine.trabelsi@firestation.tn", "pass1234", "En mission", 3));
    m_personnel.append(Personnel("P003", "Jlassi", "Sami", "Caporal", "Secours", "22 000 333",
                              "sami.jlassi@firestation.tn", "pass1234", "Disponible", 0));
    m_personnel.append(Personnel("P004", "Gharbi", "Mehdi", "Lieutenant", "Intervention", "22 000 555",
                              "mehdi.gharbi@firestation.tn", "pass1234", "Disponible", 1));
    m_personnel.append(Personnel("P005", "Khelifi", "Walid", "Sapeur", "Secours", "22 000 666",
                              "walid.khelifi@firestation.tn", "pass1234", "Disponible", 2));
    m_personnel.append(Personnel("P006", "Ben Salah", "Karim", "Adjudant", "Logistique", "22 000 777",
                              "karim.bensalah@firestation.tn", "pass1234", "En congé", 0));
    m_personnel.append(Personnel("P007", "Dridi", "Nour", "Sapeur", "Intervention", "22 000 888",
                              "nour.dridi@firestation.tn", "pass1234", "En mission", 4));
    m_personnel.append(Personnel("P014", "Mansour", "Omar", "Sergent", "Intervention", "22 000 444",
                              "omar.mansour@firestation.tn", "pass1234", "En mission", 5));
}

// Numéro de la ligne sélectionnée dans le tableau (-1 si aucune).
// La ligne n du tableau correspond toujours au personnel n de la liste m_personnel.
int GSmartFireStation::personnelSelectionne()
{
    int ligne = ui->tableWidgetPersonnel->currentRow();
    if (ligne < 0 || ligne >= m_personnel.size())
        return -1;
    return ligne;
}

// Prochain ID libre : P001, P002, ...
QString GSmartFireStation::prochainIdPersonnel()
{
    int max = 0;
    for (int i = 0; i < m_personnel.size(); i++) {
        int numero = m_personnel[i].id().mid(1).toInt();
        if (numero > max)
            max = numero;
    }
    return QString("P%1").arg(max + 1, 3, 10, QChar('0'));
}

// ------------------------------------------------------------------ affichage
void GSmartFireStation::refreshPersonnelTable()
{
    int seuil = ui->spinSeuil->value();
    int ligneCourante = ui->tableWidgetPersonnel->currentRow();
    QColor noir("#1F1F1F");

    ui->tableWidgetPersonnel->setRowCount(m_personnel.size());
    for (int r = 0; r < m_personnel.size(); r++) {
        Personnel p = m_personnel[r];

        // Nom et prénom en rouge gras si le personnel est en surcharge
        QColor couleurNom = noir;
        bool gras = false;
        if (p.charge() >= seuil) {
            couleurNom = QColor("#C00000");
            gras = true;
        }

        // Couleur de la disponibilité
        QColor couleurDispo("#6B7280");
        if (p.disponibilite() == "Disponible")
            couleurDispo = QColor("#2E7D32");
        else if (p.disponibilite() == "En mission")
            couleurDispo = QColor("#B45309");

        ui->tableWidgetPersonnel->setItem(r, 0, creerItem(p.id(), noir, false));
        ui->tableWidgetPersonnel->setItem(r, 1, creerItem(p.nom(), couleurNom, gras));
        ui->tableWidgetPersonnel->setItem(r, 2, creerItem(p.prenom(), couleurNom, gras));
        ui->tableWidgetPersonnel->setItem(r, 3, creerItem(p.grade(), noir, false));
        ui->tableWidgetPersonnel->setItem(r, 4, creerItem(p.poste(), noir, false));
        ui->tableWidgetPersonnel->setItem(r, 5, creerItem(p.telephone(), noir, false));
        ui->tableWidgetPersonnel->setItem(r, 6, creerItem(p.disponibilite(), couleurDispo, true));
    }
    if (ligneCourante >= 0 && ligneCourante < m_personnel.size())
        ui->tableWidgetPersonnel->selectRow(ligneCourante);

    filtrerPersonnel();

    // Panneau "Statistiques"
    int dispo = 0;
    int mission = 0;
    for (int i = 0; i < m_personnel.size(); i++) {
        if (m_personnel[i].disponibilite() == "Disponible")
            dispo++;
        else if (m_personnel[i].disponibilite() == "En mission")
            mission++;
    }
    int total = m_personnel.size();
    int maximum = total;
    if (maximum < 1)
        maximum = 1;
    ui->progressStatDispo->setMaximum(maximum);
    ui->progressStatDispo->setValue(dispo);
    ui->progressStatMission->setMaximum(maximum);
    ui->progressStatMission->setValue(mission);
    ui->labelTotalPersonnel->setText(QString("Total : %1 personnel(s)").arg(total));
    QStringList grades = Personnel::grades();
    QStringList gradeLabels; QList<int> gradeValues;
    for (int g=0; g<grades.size(); ++g) {
        int count=0;
        for (int i=0; i<m_personnel.size(); ++i) if (m_personnel[i].grade()==grades[g]) ++count;
        gradeLabels << grades[g]; gradeValues << count;
    }
    static_cast<PieChartWidget *>(m_personnelStatsChart)->setData(gradeLabels, gradeValues);
    int pctDispo = total ? qRound(100.0 * dispo / total) : 0;
    int pctMission = total ? qRound(100.0 * mission / total) : 0;
    int pctConge = total ? qRound(100.0 * (total-dispo-mission) / total) : 0;
    m_personnelStatsLegend->setText(QString("Disponibles : %1 (%2 %)\nEn mission : %3 (%4 %)\nEn congé / autres : %5 (%6 %)")
        .arg(dispo).arg(pctDispo).arg(mission).arg(pctMission).arg(total-dispo-mission).arg(pctConge));

    refreshSurcharge();
}

// Métier innovant : détection de surcharge
void GSmartFireStation::refreshSurcharge()
{
    int seuil = ui->spinSeuil->value();

    int plusCharge = -1;  // numéro du personnel le plus chargé (parmi ceux en surcharge)
    int nbSurcharge = 0;
    int chargeMax = 0;
    for (int i = 0; i < m_personnel.size(); i++) {
        int c = m_personnel[i].charge();
        if (c > chargeMax)
            chargeMax = c;
        if (c >= seuil) {
            nbSurcharge++;
            if (plusCharge < 0 || c > m_personnel[plusCharge].charge())
                plusCharge = i;
        }
    }

    if (plusCharge < 0) { // personne en surcharge
        ui->labelSurchargeNom->setText("Aucun personnel en surcharge");
        ui->labelSurchargeCharge->setText(QString("Charge maximale : %1 %").arg(chargeMax));
        setLabelClass(ui->labelSurchargeCharge, "cardDetail");
        ui->labelSurchargeEtat->setText("✔ Charge opérationnelle normale");
        setLabelClass(ui->labelSurchargeEtat, "textSuccessBold");
        ui->btnDetailsSurcharge->setEnabled(false);
        return;
    }

    Personnel p = m_personnel[plusCharge];
    ui->labelSurchargeNom->setText(p.id() + " — " + p.nomComplet());
    ui->labelSurchargeCharge->setText(QString("Charge actuelle : %1 %").arg(p.charge()));
    setLabelClass(ui->labelSurchargeCharge, "textDanger");
    QString etat = "⚠ Surcharge détectée";
    if (nbSurcharge > 1)
        etat += QString(" (+%1 autre(s))").arg(nbSurcharge - 1);
    ui->labelSurchargeEtat->setText(etat);
    setLabelClass(ui->labelSurchargeEtat, "textDangerBold");
    ui->btnDetailsSurcharge->setEnabled(true);
}

// ------------------------------------------------------------------ CRUD
void GSmartFireStation::on_btnAjouterPersonnel_clicked()
{
    annulerPersonnelInline();
    m_personnelEditIndex = -1;
    m_formId->setText(prochainIdPersonnel());
    m_formPersonnel->setTitle("Ajouter un personnel — remplissez la fiche ci-dessous");
    // Editor remains visible; only the field contents change.
    m_formPersonnel->show();
    m_formNom->setFocus();
    statusBar()->showMessage("Remplissez le formulaire visible puis cliquez sur Enregistrer.", 5000);
}

void GSmartFireStation::on_btnModifierPersonnel_clicked()
{
    int i = personnelSelectionne();
    if (i < 0) {
        QMessageBox::information(this, "Modifier un personnel", "Sélectionnez d'abord un personnel dans la liste.");
        return;
    }
    const Personnel p = m_personnel[i];
    m_personnelEditIndex = i;
    m_formId->setText(p.id());
    m_formNom->setText(p.nom()); m_formPrenom->setText(p.prenom());
    m_formGrade->setCurrentText(p.grade()); m_formPoste->setCurrentText(p.poste());
    m_formTelephone->setText(p.telephone()); m_formEmail->setText(p.email());
    m_formMotDePasse->setText(p.motDePasse()); m_formDisponibilite->setCurrentText(p.disponibilite());
    m_formMissions->setValue(p.missionsEnCours());
    m_formPersonnel->setTitle("Modifier " + p.id() + " — modifiez les champs puis enregistrez");
    m_formPersonnel->show();
    m_formNom->setFocus();
}

void GSmartFireStation::enregistrerPersonnelInline()
{
    QString tel = m_formTelephone->text(); tel.remove(" "); tel.remove("-");
    bool telOk = false; tel.toLongLong(&telOk);
    QString email = m_formEmail->text().trimmed();
    QString erreur;
    if (m_formNom->text().trimmed().isEmpty()) erreur = "Le nom est obligatoire.";
    else if (m_formPrenom->text().trimmed().isEmpty()) erreur = "Le prénom est obligatoire.";
    else if (tel.length() != 8 || !telOk) erreur = "Le téléphone doit contenir exactement 8 chiffres.";
    else if (!email.contains("@") || !email.contains(".")) erreur = "L'adresse email n'est pas valide.";
    else if (m_formMotDePasse->text().length() < 4) erreur = "Le mot de passe doit contenir au moins 4 caractères.";
    if (!erreur.isEmpty()) { QMessageBox::warning(this, "Saisie incorrecte", erreur); return; }
    Personnel p(m_formId->text(), m_formNom->text().trimmed(), m_formPrenom->text().trimmed(),
                m_formGrade->currentText(), m_formPoste->currentText(), m_formTelephone->text().trimmed(),
                email, m_formMotDePasse->text(), m_formDisponibilite->currentText(), m_formMissions->value());
    if (m_personnelEditIndex >= 0 && m_personnelEditIndex < m_personnel.size()) {
        m_personnel[m_personnelEditIndex] = p;
        statusBar()->showMessage("Personnel modifié avec succès.", 4000);
    } else {
        m_personnel.append(p);
        m_personnelEditIndex = m_personnel.size() - 1;
        statusBar()->showMessage("Personnel ajouté avec succès.", 4000);
    }
    refreshPersonnelTable();
    ui->tableWidgetPersonnel->selectRow(m_personnelEditIndex);
    m_formPersonnel->setTitle("Fiche du personnel — remplissez les champs puis validez");
    m_formPersonnel->show();
}

void GSmartFireStation::annulerPersonnelInline()
{
    m_personnelEditIndex = -1;
    m_formId->setText(prochainIdPersonnel());
    m_formNom->clear(); m_formPrenom->clear(); m_formTelephone->clear();
    m_formEmail->clear(); m_formMotDePasse->clear(); m_formMissions->setValue(0);
    m_formGrade->setCurrentIndex(0); m_formPoste->setCurrentIndex(0); m_formDisponibilite->setCurrentText("Disponible");
    m_formPersonnel->setTitle("Fiche du personnel — remplissez les champs puis validez");
    m_formPersonnel->show();
}

void GSmartFireStation::on_btnSupprimerPersonnel_clicked()
{
    int i = personnelSelectionne();
    if (i < 0) {
        QMessageBox::information(this, "Supprimer un personnel",
                                 "Sélectionnez d'abord un personnel dans la liste.");
        return;
    }
    int reponse = QMessageBox::question(this, "Supprimer un personnel",
                                        "Voulez-vous vraiment supprimer " + m_personnel[i].nomComplet() + " ?");
    if (reponse != QMessageBox::Yes)
        return;

    m_personnel.removeAt(i);
    ui->tableWidgetPersonnel->setCurrentCell(-1, -1);
    refreshPersonnelTable();
    statusBar()->showMessage("Personnel supprimé.", 5000);
}

void GSmartFireStation::on_tableWidgetPersonnel_cellDoubleClicked(int, int)
{
    on_btnModifierPersonnel_clicked(); // double-clic = modifier
}

// ------------------------------------------------------------------ recherche
// Cache les lignes qui ne contiennent pas le texte cherché (ID, nom, prénom ou grade)
void GSmartFireStation::filtrerPersonnel()
{
    QString texte = ui->lineEditRecherchePersonnel->text().trimmed();
    int visibles = 0;
    for (int r = 0; r < m_personnel.size(); r++) {
        Personnel p = m_personnel[r];
        bool trouve = texte == ""
                      || p.id().contains(texte, Qt::CaseInsensitive)
                      || p.nom().contains(texte, Qt::CaseInsensitive)
                      || p.prenom().contains(texte, Qt::CaseInsensitive)
                      || p.grade().contains(texte, Qt::CaseInsensitive);
        ui->tableWidgetPersonnel->setRowHidden(r, !trouve);
        if (trouve)
            visibles++;
    }
    if (texte != "")
        statusBar()->showMessage(QString("%1 résultat(s)").arg(visibles), 4000);
    else
        statusBar()->clearMessage();
}

void GSmartFireStation::on_btnRechercherPersonnel_clicked()
{
    filtrerPersonnel();
}

void GSmartFireStation::on_lineEditRecherchePersonnel_textChanged(const QString &)
{
    filtrerPersonnel(); // la recherche se met à jour pendant la frappe
}

// ------------------------------------------------------------------ tri (tri à bulles)
// Retourne vrai si 'a' doit passer après 'b' selon le critère choisi
bool GSmartFireStation::doitEchangerPersonnel(Personnel a, Personnel b, int critere)
{
    if (critere == 0) // Grade : du plus élevé au moins élevé
        return Personnel::rangGrade(a.grade()) > Personnel::rangGrade(b.grade());
    if (critere == 1) // Disponibilité : Disponible, En mission, En congé
        return Personnel::disponibilites().indexOf(a.disponibilite())
               > Personnel::disponibilites().indexOf(b.disponibilite());
    return a.nom().toLower() > b.nom().toLower(); // Nom : ordre alphabétique
}

void GSmartFireStation::on_btnTrierPersonnel_clicked()
{
    int critere = ui->comboTriPersonnel->currentIndex();
    int n = m_personnel.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (doitEchangerPersonnel(m_personnel[j], m_personnel[j + 1], critere)) {
                Personnel temp = m_personnel[j];
                m_personnel[j] = m_personnel[j + 1];
                m_personnel[j + 1] = temp;
            }
        }
    }
    ui->tableWidgetPersonnel->setCurrentCell(-1, -1);
    refreshPersonnelTable();
    statusBar()->showMessage("Liste triée.", 4000);
}

// ------------------------------------------------------------------ export PDF
void GSmartFireStation::on_btnExportPersonnel_clicked()
{
    exporterTableauPdf(ui->tableWidgetPersonnel, "Liste du personnel", "personnel.pdf");
}

// ------------------------------------------------------------------ statistiques
StatCritere GSmartFireStation::statPersonnelParGrade()
{
    QStringList reelles;
    for (int i = 0; i < m_personnel.size(); i++)
        reelles << m_personnel[i].grade();
    return compterParValeur("Grade", Personnel::grades(), reelles);
}

StatCritere GSmartFireStation::statPersonnelParDispo()
{
    QStringList reelles;
    for (int i = 0; i < m_personnel.size(); i++)
        reelles << m_personnel[i].disponibilite();
    return compterParValeur("Disponibilité", Personnel::disponibilites(), reelles);
}

void GSmartFireStation::on_btnStatsPersonnel_clicked()
{
    return; // les statistiques sont toujours visibles dans le panneau latéral
    QList<StatCritere> criteres;
    criteres << statPersonnelParGrade() << statPersonnelParDispo();
    StatsDialog fenetre("Statistiques du personnel", criteres, this);
    fenetre.exec();
}

// ------------------------------------------------------------------ surcharge
void GSmartFireStation::on_spinSeuil_valueChanged(int)
{
    refreshPersonnelTable(); // le seuil a changé : on recalcule les surcharges
}

void GSmartFireStation::on_btnDetailsSurcharge_clicked()
{
    int seuil = ui->spinSeuil->value();
    QString texte = "";
    int nb = 0;
    int plusCharge = -1;
    for (int i = 0; i < m_personnel.size(); i++) {
        Personnel p = m_personnel[i];
        if (p.charge() >= seuil) {
            nb++;
            texte += QString("• %1 — %2 (%3) : %4 mission(s), charge %5 %\n")
                         .arg(p.id()).arg(p.nomComplet()).arg(p.grade())
                         .arg(p.missionsEnCours()).arg(p.charge());
            if (plusCharge < 0 || p.charge() > m_personnel[plusCharge].charge())
                plusCharge = i;
        }
    }
    if (nb == 0)
        return;

    QMessageBox boite(this);
    boite.setIcon(QMessageBox::Warning);
    boite.setWindowTitle("Personnel en surcharge");
    boite.setText(QString("%1 personnel(s) dépassent le seuil de %2 %.").arg(nb).arg(seuil));
    boite.setInformativeText(texte + "\nPensez à réaffecter une partie de leurs missions.");
    boite.exec();

    ui->tableWidgetPersonnel->selectRow(plusCharge); // montre le plus chargé dans le tableau
}
