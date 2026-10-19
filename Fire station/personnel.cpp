#include "personnel.h"

Personnel::Personnel()
{
    m_missionsEnCours = 0;
}

Personnel::Personnel(const QString &id, const QString &nom, const QString &prenom,
                 const QString &grade, const QString &poste, const QString &telephone,
                 const QString &email, const QString &motDePasse,
                 const QString &disponibilite, int missionsEnCours)
{
    m_id = id;
    m_nom = nom;
    m_prenom = prenom;
    m_grade = grade;
    m_poste = poste;
    m_telephone = telephone;
    m_email = email;
    m_motDePasse = motDePasse;
    m_disponibilite = disponibilite;
    m_missionsEnCours = missionsEnCours;
}

int Personnel::charge() const
{
    int c = m_missionsEnCours * 20; // 20 % par mission
    if (c > 100)
        c = 100;
    return c;
}

QString Personnel::nomComplet() const
{
    return m_prenom + " " + m_nom;
}

// Du grade le plus élevé au moins élevé (sert aussi pour le tri)
QStringList Personnel::grades()
{
    QStringList liste;
    liste << "Colonel" << "Commandant" << "Capitaine" << "Lieutenant"
          << "Adjudant" << "Sergent" << "Caporal" << "Sapeur";
    return liste;
}

QStringList Personnel::postes()
{
    QStringList liste;
    liste << "Chef de garde" << "Intervention" << "Secours" << "Logistique" << "Administration";
    return liste;
}

QStringList Personnel::disponibilites()
{
    QStringList liste;
    liste << "Disponible" << "En mission" << "En congé";
    return liste;
}

int Personnel::rangGrade(const QString &grade)
{
    int i = grades().indexOf(grade);
    if (i < 0)
        i = grades().size();
    return i;
}
