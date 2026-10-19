#ifndef VEHICULE_H
#define VEHICULE_H

#include <QDate>
#include <QString>
#include <QStringList>

// Entité "Véhicule" (Module 2 : Gestion des véhicules)
class Vehicule
{
public:
    Vehicule();
    Vehicule(const QString &id, const QString &immatriculation, const QString &type,
             const QString &modele, const QString &etat, const QString &disponibilite,
             const QDate &dateMaintenance);

    // Getters
    QString id() const { return m_id; }
    QString immatriculation() const { return m_immatriculation; }
    QString type() const { return m_type; }
    QString modele() const { return m_modele; }
    QString etat() const { return m_etat; }
    QString disponibilite() const { return m_disponibilite; }
    QDate dateMaintenance() const { return m_dateMaintenance; }

    // Setters
    void setId(const QString &v) { m_id = v; }
    void setImmatriculation(const QString &v) { m_immatriculation = v; }
    void setType(const QString &v) { m_type = v; }
    void setModele(const QString &v) { m_modele = v; }
    void setEtat(const QString &v) { m_etat = v; }
    void setDisponibilite(const QString &v) { m_disponibilite = v; }
    void setDateMaintenance(const QDate &v) { m_dateMaintenance = v; }

    // Vrai si la maintenance est prévue dans les 30 prochains jours (ou déjà dépassée)
    bool maintenanceProche() const;

    // Listes de valeurs autorisées
    static QStringList types();
    static QStringList etats();
    static QStringList disponibilites();
    static QStringList typesPourIntervention(const QString &intervention);

private:
    QString m_id;
    QString m_immatriculation;
    QString m_type;
    QString m_modele;
    QString m_etat;
    QString m_disponibilite;
    QDate m_dateMaintenance;
};

#endif // VEHICULE_H
