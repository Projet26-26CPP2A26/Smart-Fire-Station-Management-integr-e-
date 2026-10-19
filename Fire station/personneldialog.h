#ifndef PERSONNELDIALOG_H
#define PERSONNELDIALOG_H

#include <QDialog>
#include "personnel.h"

class QLineEdit;
class QComboBox;
class QSpinBox;

// Formulaire d'ajout / modification d'un personnel (créé en code : pas de .ui supplémentaire)
class PersonnelDialog : public QDialog
{
    Q_OBJECT
public:
    PersonnelDialog(const QString &titre, const QString &id, QWidget *parent = 0);

    void setPersonnel(const Personnel &p); // remplit le formulaire
    Personnel personnel() const;           // lit le formulaire

private slots:
    void valider(); // vérifie la saisie puis ferme le formulaire

private:
    QString m_id;
    QLineEdit *m_nom;
    QLineEdit *m_prenom;
    QComboBox *m_grade;
    QComboBox *m_poste;
    QLineEdit *m_telephone;
    QLineEdit *m_email;
    QLineEdit *m_motDePasse;
    QComboBox *m_disponibilite;
    QSpinBox *m_missions;
};

#endif // PERSONNELDIALOG_H
