#include "vehicule.h"

Vehicule::Vehicule()
{
}

Vehicule::Vehicule(const QString &id, const QString &immatriculation, const QString &type,
                   const QString &modele, const QString &etat, const QString &disponibilite,
                   const QDate &dateMaintenance)
{
    m_id = id;
    m_immatriculation = immatriculation;
    m_type = type;
    m_modele = modele;
    m_etat = etat;
    m_disponibilite = disponibilite;
    m_dateMaintenance = dateMaintenance;
}

bool Vehicule::maintenanceProche() const
{
    QDate limite = QDate::currentDate().addDays(30);
    return m_dateMaintenance.isValid() && m_dateMaintenance <= limite;
}

QStringList Vehicule::types()
{
    QStringList liste;
    liste << "Fourgon" << "Camion" << "Ambulance" << "Citerne" << "Échelle";
    return liste;
}

QStringList Vehicule::etats()
{
    QStringList liste;
    liste << "Bon" << "À contrôler" << "Hors service";
    return liste;
}

QStringList Vehicule::disponibilites()
{
    QStringList liste;
    liste << "Disponible" << "En mission" << "En maintenance";
    return liste;
}

// Types de véhicules adaptés à chaque intervention, par ordre de préférence
QStringList Vehicule::typesPourIntervention(const QString &intervention)
{
    QStringList liste;
    if (intervention == "Incendie")
        liste << "Citerne" << "Fourgon" << "Échelle";
    else if (intervention == "Secours à personne")
        liste << "Ambulance" << "Fourgon";
    else if (intervention == "Accident de la route")
        liste << "Camion" << "Fourgon" << "Ambulance";
    else if (intervention == "Inondation")
        liste << "Camion" << "Citerne";
    else
        liste = types();
    return liste;
}
