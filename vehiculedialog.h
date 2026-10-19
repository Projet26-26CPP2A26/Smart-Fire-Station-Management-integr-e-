#ifndef VEHICULEDIALOG_H
#define VEHICULEDIALOG_H

#include <QDialog>
#include <QStringList>
#include "vehicule.h"

class QLineEdit;
class QComboBox;
class QDateEdit;

// Formulaire d'ajout / modification d'un véhicule (créé en code : pas de .ui supplémentaire)
class VehiculeDialog : public QDialog
{
    Q_OBJECT
public:
    // 'immatriculationsExistantes' sert à refuser les doublons
    VehiculeDialog(const QString &titre, const QString &id,
                   const QStringList &immatriculationsExistantes, QWidget *parent = 0);

    void setVehicule(const Vehicule &v); // remplit le formulaire
    Vehicule vehicule() const;           // lit le formulaire

private slots:
    void valider(); // vérifie la saisie puis ferme le formulaire

private:
    QString m_id;
    QStringList m_existantes;
    QLineEdit *m_immatriculation;
    QComboBox *m_type;
    QLineEdit *m_modele;
    QComboBox *m_etat;
    QComboBox *m_disponibilite;
    QDateEdit *m_dateMaintenance;
};

#endif // VEHICULEDIALOG_H
