#include "personneldialog.h"
#include "styleutils.h"

#include <QComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

PersonnelDialog::PersonnelDialog(const QString &titre, const QString &id, QWidget *parent)
    : QDialog(parent)
{
    m_id = id;
    setWindowTitle(titre);
    setMinimumWidth(420);

    // Champs du formulaire
    m_nom = new QLineEdit;
    m_prenom = new QLineEdit;
    m_grade = new QComboBox;
    m_grade->addItems(Personnel::grades());
    m_poste = new QComboBox;
    m_poste->addItems(Personnel::postes());
    m_telephone = new QLineEdit;
    m_telephone->setPlaceholderText("8 chiffres, ex : 22 000 111");
    m_email = new QLineEdit;
    m_email->setPlaceholderText("prenom.nom@firestation.tn");
    m_motDePasse = new QLineEdit;
    m_motDePasse->setEchoMode(QLineEdit::Password);
    m_motDePasse->setPlaceholderText("4 caractères minimum");
    m_disponibilite = new QComboBox;
    m_disponibilite->addItems(Personnel::disponibilites());
    m_missions = new QSpinBox;
    m_missions->setMaximum(10);
    m_missions->setToolTip("Chaque mission en cours ajoute 20 % de charge opérationnelle");

    QLabel *labelTitre = new QLabel(titre);
    labelTitre->setProperty("class", "cardTitle");

    // Disposition : libellé + champ sur chaque ligne
    QFormLayout *formulaire = new QFormLayout;
    formulaire->addRow("ID :", new QLabel(m_id));
    formulaire->addRow("Nom :", m_nom);
    formulaire->addRow("Prénom :", m_prenom);
    formulaire->addRow("Grade :", m_grade);
    formulaire->addRow("Poste :", m_poste);
    formulaire->addRow("Téléphone :", m_telephone);
    formulaire->addRow("Email :", m_email);
    formulaire->addRow("Mot de passe :", m_motDePasse);
    formulaire->addRow("Disponibilité :", m_disponibilite);
    formulaire->addRow("Missions en cours :", m_missions);

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

void PersonnelDialog::setPersonnel(const Personnel &p)
{
    m_id = p.id();
    m_nom->setText(p.nom());
    m_prenom->setText(p.prenom());
    m_grade->setCurrentText(p.grade());
    m_poste->setCurrentText(p.poste());
    m_telephone->setText(p.telephone());
    m_email->setText(p.email());
    m_motDePasse->setText(p.motDePasse());
    m_disponibilite->setCurrentText(p.disponibilite());
    m_missions->setValue(p.missionsEnCours());
}

Personnel PersonnelDialog::personnel() const
{
    return Personnel(m_id, m_nom->text().trimmed(), m_prenom->text().trimmed(),
                   m_grade->currentText(), m_poste->currentText(),
                   m_telephone->text().trimmed(), m_email->text().trimmed(),
                   m_motDePasse->text(), m_disponibilite->currentText(),
                   m_missions->value());
}

void PersonnelDialog::valider()
{
    // Le téléphone doit contenir exactement 8 chiffres (les espaces sont ignorés)
    QString tel = m_telephone->text();
    tel.remove(" ");
    bool telEstUnNombre;
    tel.toLongLong(&telEstUnNombre);

    QString email = m_email->text().trimmed();

    QString erreur = "";
    if (m_nom->text().trimmed() == "")
        erreur = "Le nom est obligatoire.";
    else if (m_prenom->text().trimmed() == "")
        erreur = "Le prénom est obligatoire.";
    else if (tel.length() != 8 || !telEstUnNombre)
        erreur = "Le téléphone doit contenir exactement 8 chiffres.";
    else if (!email.contains("@") || !email.contains("."))
        erreur = "L'adresse email n'est pas valide.";
    else if (m_motDePasse->text().length() < 4)
        erreur = "Le mot de passe doit contenir au moins 4 caractères.";

    if (erreur != "") {
        QMessageBox::warning(this, "Saisie incorrecte", erreur);
        return; // on reste dans le formulaire
    }
    accept(); // tout est correct : on ferme le formulaire (résultat "Accepted")
}
