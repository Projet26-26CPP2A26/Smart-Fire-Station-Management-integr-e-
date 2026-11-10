#ifndef PERSONNEL_H
#define PERSONNEL_H

// =====================================================================
//  SMART FIRE STATION - Module 1 : Gestion du personnel
//  UN SEUL fichier d'en-tête (.h) : personnel.h
//  UN SEUL fichier d'implémentation (.cpp) : personnel.cpp
//
//  Contenu :
//    1. Personnel        : entité + CRUD + métiers + contrôle de saisie (couche MODELE, tout le SQL)
//    2. PersonnelModel   : modèle d'affichage du tableau (couleurs, formats)
//    3. PersonnelPieChart: diagramme circulaire des statistiques
//    4. PersonnelPage    : interface (couche VUE, aucune requête SQL),
//                          page insérée dans la fenêtre principale intégrée
//
//  La connexion Oracle est fournie par DatabaseManager (gsmartfirestation.h),
//  partagée avec le module Véhicules : une seule connexion pour l'application.
// =====================================================================

#include <QList>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>
#include <QStringList>
#include <QWidget>

class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QModelIndex;
class QPushButton;
class QTableView;

// ---------------------------------------------------------------------
//  1. Entité Personnel
//     Toutes les requêtes SQL sont ici (jamais derrière un bouton).
//     Les requêtes sont préparées (prepare / bindValue / exec).
// ---------------------------------------------------------------------
class Personnel
{
public:
    Personnel();
    Personnel(int id, const QString &nom, const QString &prenom, const QString &grade,
              const QString &poste, const QString &telephone, const QString &email,
              const QString &motDePasse, const QString &questionSecrete,
              const QString &reponseSecrete, const QString &disponibilite);

    // ----- Getters -----
    int id() const { return m_id; }
    QString nom() const { return m_nom; }
    QString prenom() const { return m_prenom; }
    QString grade() const { return m_grade; }
    QString poste() const { return m_poste; }
    QString telephone() const { return m_telephone; }
    QString email() const { return m_email; }
    QString motDePasse() const { return m_motDePasse; }
    QString questionSecrete() const { return m_questionSecrete; }
    QString reponseSecrete() const { return m_reponseSecrete; }
    QString disponibilite() const { return m_disponibilite; }
    QString nomComplet() const { return m_prenom + " " + m_nom; }

    // ----- Setters -----
    void setId(int v) { m_id = v; }
    void setNom(const QString &v) { m_nom = v; }
    void setPrenom(const QString &v) { m_prenom = v; }
    void setGrade(const QString &v) { m_grade = v; }
    void setPoste(const QString &v) { m_poste = v; }
    void setTelephone(const QString &v) { m_telephone = v; }
    void setEmail(const QString &v) { m_email = v; }
    void setMotDePasse(const QString &v) { m_motDePasse = v; }
    void setQuestionSecrete(const QString &v) { m_questionSecrete = v; }
    void setReponseSecrete(const QString &v) { m_reponseSecrete = v; }
    void setDisponibilite(const QString &v) { m_disponibilite = v; }

    // ----- CRUD -----
    bool ajouter() const;                                   // Create
    bool modifier() const;                                  // Update (mot de passe / réponse inchangés si vides)
    static bool supprimer(int id);                          // Delete
    static QSqlQueryModel *afficher(const QString &recherche = QString(), int tri = 0); // Read
    static bool trouver(int id, Personnel &resultat);       // Lire un membre (remplir le formulaire)

    // ----- Métiers avancés : authentification et mot de passe oublié -----
    static bool authentifier(const QString &email, const QString &motDePasse, Personnel &connecte);
    static QString questionDe(const QString &email);        // question secrète du compte ("" si inconnu)
    static bool reinitialiserMotDePasse(const QString &email, const QString &reponse,
                                        const QString &nouveauMotDePasse);

    // ----- Statistiques : nombre de membres pour chaque grade (même ordre que grades()) -----
    static QList<int> statistiquesParGrade();

    // ----- Contrôle de saisie -----
    static bool nomValide(const QString &texte);
    static bool telephoneValide(const QString &texte);
    static bool emailValide(const QString &texte);
    static bool motDePasseValide(const QString &texte);     // 6 caractères min., au moins une lettre et un chiffre

    // ----- Outils -----
    static QString hacher(const QString &texte);            // SHA-256 (le mot de passe n'est jamais stocké en clair)
    static QString normaliser(const QString &reponse);      // réponse secrète : sans espaces ni majuscules
    static QString derniereErreur();                        // dernier message d'erreur SQL

    // ----- Listes de valeurs -----
    static QStringList grades();
    static QStringList postes();
    static QStringList disponibilites();
    static QStringList questions();

private:
    int m_id;
    QString m_nom;
    QString m_prenom;
    QString m_grade;
    QString m_poste;
    QString m_telephone;
    QString m_email;
    QString m_motDePasse;
    QString m_questionSecrete;
    QString m_reponseSecrete;
    QString m_disponibilite;
};

// ---------------------------------------------------------------------
//  2. Modèle d'affichage du tableau : ID "P001", téléphone "22 000 111",
//     disponibilité colorée. Les données viennent de Personnel::afficher().
// ---------------------------------------------------------------------
class PersonnelModel : public QSqlQueryModel
{
public:
    explicit PersonnelModel(QObject *parent = nullptr) : QSqlQueryModel(parent) {}
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

// ---------------------------------------------------------------------
//  3. Diagramme circulaire (statistiques par grade)
// ---------------------------------------------------------------------
class PersonnelPieChart : public QWidget
{
    Q_OBJECT

public:
    explicit PersonnelPieChart(QWidget *parent = nullptr);
    void setData(const QStringList &labels, const QList<int> &values);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QStringList m_labels;
    QList<int> m_values;
};

// ---------------------------------------------------------------------
//  4. Page "Gestion du personnel" (couche VUE) : aucune requête SQL ici,
//     tout passe par la classe Personnel. Insérée dans le QStackedWidget
//     de GSmartFireStation (page 1).
// ---------------------------------------------------------------------
class PersonnelPage : public QWidget
{
    Q_OBJECT

public:
    explicit PersonnelPage(QWidget *parent = nullptr);
    ~PersonnelPage();

    bool connexion();                       // dialogue d'authentification (avant d'afficher la fenêtre)
    Personnel utilisateurConnecte() const { return m_utilisateur; }

public slots:
    void rafraichir();                      // recharge le tableau + les statistiques (appelé après connexion)

private slots:
    void ajouterPersonnel();                // prépare le formulaire pour un nouveau membre
    void modifierPersonnel();               // charge le membre sélectionné dans le formulaire
    void supprimerPersonnel();
    void enregistrer();                     // valide le formulaire : INSERT ou UPDATE
    void viderFormulaire();
    void rechercher();
    void trier();
    void exporterPdf();

private:
    void construireInterface();
    void motDePasseOublie(QWidget *parent);
    bool lireFormulaire(Personnel &p, bool modification);
    int idSelectionne() const;              // ID de la ligne sélectionnée (0 si aucune)
    void mettreAJourStatistiques();
    void showMessage(const QString &texte, int duree = 0);   // relaie vers la barre d'état de la fenêtre principale
    void clearMessage();

    QSqlQueryModel *m_model;
    Personnel m_utilisateur;
    int m_idEdition;                        // 0 = nouveau membre, sinon id du membre en modification
    int m_tri;                              // critère de tri appliqué (0 = ID, 1 = grade, 2 = disponibilité, 3 = nom)

    // Recherche, tri, tableau
    QLineEdit *m_recherche;
    QComboBox *m_comboTri;
    QTableView *m_table;

    // Formulaire
    QGroupBox *m_formulaire;
    QLabel *m_labelId;
    QLineEdit *m_nom;
    QLineEdit *m_prenom;
    QLineEdit *m_telephone;
    QLineEdit *m_email;
    QLineEdit *m_motDePasse;
    QLineEdit *m_reponse;
    QComboBox *m_grade;
    QComboBox *m_poste;
    QComboBox *m_disponibilite;
    QComboBox *m_question;

    // Statistiques
    PersonnelPieChart *m_graphique;
    QLabel *m_labelTotal;
};

#endif // PERSONNEL_H