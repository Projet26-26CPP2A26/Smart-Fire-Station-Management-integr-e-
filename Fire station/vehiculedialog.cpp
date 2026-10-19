#include "vehiculedialog.h"
#include "styleutils.h"

#include <QComboBox>
#include <QDateEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

VehiculeDialog::VehiculeDialog(const QString &titre, const QString &id,
                               const QStringList &immatriculationsExistantes, QWidget *parent)
    : QDialog(parent)
{
    m_id = id;
    m_existantes = immatriculationsExistantes;
    setWindowTitle(titre);
    setMinimumWidth(420);

    // Champs du formulaire
    m_immatriculation = new QLineEdit;
    m_immatriculation->setPlaceholderText("ex : 123 TU 456");
    m_type = new QComboBox;
    m_type->addItems(Vehicule::types());
    m_modele = new QLineEdit;
    m_etat = new QComboBox;
    m_etat->addItems(Vehicule::etats());
    m_disponibilite = new QComboBox;
    m_disponibilite->addItems(Vehicule::disponibilites());
    m_dateMaintenance = new QDateEdit(QDate::currentDate().addMonths(3));
    m_dateMaintenance->setCalendarPopup(true);
    m_dateMaintenance->setDisplayFormat("dd/MM/yyyy");

    QLabel *labelTitre = new QLabel(titre);
    labelTitre->setProperty("class", "cardTitle");

    // Disposition : libellé + champ sur chaque ligne
    QFormLayout *formulaire = new QFormLayout;
    formulaire->addRow("ID :", new QLabel(m_id));
    formulaire->addRow("Immatriculation :", m_immatriculation);
    formulaire->addRow("Type :", m_type);
    formulaire->addRow("Modèle :", m_modele);
    formulaire->addRow("État :", m_etat);
    formulaire->addRow("Disponibilité :", m_disponibilite);
    formulaire->addRow("Date de maintenance :", m_dateMaintenance);

    // Boutons
    QPushButton *boutonOk = new QPushButton("Enregistrer");
    QPushButton *boutonAnnuler = new QPushButton("Annuler");
    boutonOk->setProperty("class", "btnSuccess");
    boutonAnnuler->setProperty("class", "btnSecondary");
    connect(boutonOk, SIGNAL(clicked()), this, SLOT(valider()));
    connect(boutonAnnuler, SIGNAL(clicked()), this, SLOT(reject()));

    QHBoxLayout *ligneBoutons = new QHBoxLayout;
    ligneBoutons->addStretch();
    ligneBoutons->addWidget(boutonOk);
    ligneBoutons->addWidget(boutonAnnuler);

    QVBoxLayout *principal = new QVBoxLayout(this);
    principal->setContentsMargins(24, 20, 24, 20);
    principal->setSpacing(12);
    principal->addWidget(labelTitre);
    principal->addLayout(formulaire);
    principal->addLayout(ligneBoutons);
    repolish(this);
}

void VehiculeDialog::setVehicule(const Vehicule &v)
{
    m_id = v.id();
    m_immatriculation->setText(v.immatriculation());
    m_type->setCurrentText(v.type());
    m_modele->setText(v.modele());
    m_etat->setCurrentText(v.etat());
    m_disponibilite->setCurrentText(v.disponibilite());
    m_dateMaintenance->setDate(v.dateMaintenance());
}

Vehicule VehiculeDialog::vehicule() const
{
    return Vehicule(m_id, m_immatriculation->text().trimmed().toUpper(), m_type->currentText(),
                    m_modele->text().trimmed(), m_etat->currentText(),
                    m_disponibilite->currentText(), m_dateMaintenance->date());
}

void VehiculeDialog::valider()
{
    QString immat = m_immatriculation->text().trimmed().toUpper();

    QString erreur = "";
    if (immat == "")
        erreur = "L'immatriculation est obligatoire.";
    else if (m_existantes.contains(immat))
        erreur = "Cette immatriculation existe déjà.";
    else if (m_modele->text().trimmed() == "")
        erreur = "Le modèle est obligatoire.";

    if (erreur != "") {
        QMessageBox::warning(this, "Saisie incorrecte", erreur);
        return; // on reste dans le formulaire
    }
    accept(); // tout est correct : on ferme le formulaire (résultat "Accepted")
}
