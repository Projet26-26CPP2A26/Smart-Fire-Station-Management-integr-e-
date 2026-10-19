#ifndef GSMARTFIRESTATION_H
#define GSMARTFIRESTATION_H

#include <QColor>
#include <QList>
#include <QMainWindow>

#include "personnel.h"
#include "statsdialog.h"
#include "vehicule.h"

class QLabel;
class QProgressBar;
class QTableWidget;
class QTableWidgetItem;
class QLineEdit;
class QComboBox;
class QSpinBox;
class QGroupBox;
class QWidget;
class QDateEdit;
class PieChartWidget;

QT_BEGIN_NAMESPACE
namespace Ui {
class GSmartFireStation;
}
QT_END_NAMESPACE

// Fenêtre principale (G = Gestion). UN SEUL fichier .ui : les vues sont les pages
// d'un QStackedWidget (page 0 = Dashboard, 1 = Personnel, 2 = Véhicules).
//
// Intégration : le code de chaque module vient de son projet individuel (copier-coller) :
//   gsmartfirestation_personnel.cpp  = code du projet Personnel
//   gsmartfirestation_vehicules.cpp = code du projet Vehicules
class GSmartFireStation : public QMainWindow
{
    Q_OBJECT

public:
    GSmartFireStation(QWidget *parent = 0);
    ~GSmartFireStation();

private slots:
    // ----- Navigation entre les pages -----
    void on_btnNavDashboard_clicked();
    void on_btnNavPersonnel_clicked();
    void on_btnNavVehicules_clicked();
    void on_btnGererPersonnel_clicked();
    void on_btnGererVehicules_clicked();
    void on_btnRetourPersonnel_clicked();
    void on_btnRetourVehicule_clicked();
    void on_btnQuitter_clicked();
    void on_btnVoirStats_clicked();

    // ----- Module Personnel (slots créés automatiquement par le nom on_<objet>_<signal>) -----
    void on_btnAjouterPersonnel_clicked();
    void on_btnModifierPersonnel_clicked();
    void on_btnSupprimerPersonnel_clicked();
    void on_btnRechercherPersonnel_clicked();
    void on_lineEditRecherchePersonnel_textChanged(const QString &texte);
    void on_btnTrierPersonnel_clicked();
    void on_btnExportPersonnel_clicked();
    void on_btnStatsPersonnel_clicked();
    void on_tableWidgetPersonnel_cellDoubleClicked(int ligne, int colonne);
    void on_spinSeuil_valueChanged(int valeur);
    void on_btnDetailsSurcharge_clicked();
    void enregistrerPersonnelInline();
    void annulerPersonnelInline();

    // ----- Module Véhicules (slots créés automatiquement par le nom on_<objet>_<signal>) -----
    void on_btnAjouterVehicule_clicked();
    void on_btnModifierVehicule_clicked();
    void on_btnSupprimerVehicule_clicked();
    void on_btnRechercherVehicule_clicked();
    void on_lineEditRechercheVehicule_textChanged(const QString &texte);
    void on_btnTrierVehicule_clicked();
    void on_btnExportVehicule_clicked();
    void on_btnStatsVehicule_clicked();
    void on_tableWidgetVehicules_cellDoubleClicked(int ligne, int colonne);
    void on_comboIntervention_currentIndexChanged(int index);
    void on_btnUtiliserVehicule_clicked();
    void enregistrerVehiculeInline();
    void annulerVehiculeInline();

private:
    // ----- Navigation + Dashboard -----
    void goToPage(int index);
    void refreshDashboard();
    void majBarre(QProgressBar *barre, QLabel *label, int valeur, int total);
    void ajouterAlerte(const QString &texte, const QString &couleur);

    // ----- Module Personnel -----
    void setupPersonnel();
    void chargerPersonnelExemple();
    void refreshPersonnelTable();
    void refreshSurcharge();
    void filtrerPersonnel();
    int personnelSelectionne();
    QString prochainIdPersonnel();
    bool doitEchangerPersonnel(Personnel a, Personnel b, int critere);
    StatCritere statPersonnelParGrade();
    StatCritere statPersonnelParDispo();
    QList<Personnel> m_personnel;
    QGroupBox *m_formPersonnel;
    QLineEdit *m_formNom;
    QLineEdit *m_formPrenom;
    QLineEdit *m_formTelephone;
    QLineEdit *m_formEmail;
    QLineEdit *m_formMotDePasse;
    QComboBox *m_formGrade;
    QComboBox *m_formPoste;
    QComboBox *m_formDisponibilite;
    QSpinBox *m_formMissions;
    QLabel *m_formId;
    int m_personnelEditIndex;
    QWidget *m_personnelStatsChart;
    QLabel *m_personnelStatsLegend;
    QLineEdit *m_vehicleImmat;
    QComboBox *m_vehicleType;
    QLineEdit *m_vehicleModele;
    QComboBox *m_vehicleEtat;
    QComboBox *m_vehicleDispo;
    QDateEdit *m_vehicleDate;
    QLabel *m_vehicleId;
    QGroupBox *m_formVehicule;
    int m_vehiculeEditIndex;
    QWidget *m_vehiculeStatsChart;

    // ----- Module Véhicules -----
    void setupVehicules();
    void chargerVehiculesExemple();
    void refreshVehiculesTable();
    void refreshVehiculePropose();
    void filtrerVehicules();
    int vehiculeSelectionne();
    QString prochainIdVehicule();
    bool doitEchangerVehicules(Vehicule a, Vehicule b, int critere);
    StatCritere statVehiculesParEtat();
    StatCritere statVehiculesParDispo();
    QList<Vehicule> m_vehicules;
    int m_vehiculePropose; // numéro du véhicule proposé pour la mission (-1 = aucun)

    // ----- Outils communs -----
    QTableWidgetItem *creerItem(const QString &texte, const QColor &couleur, bool gras);
    void setLabelClass(QLabel *label, const QString &classe);
    void exporterTableauPdf(QTableWidget *table, const QString &titre, const QString &nomFichier);

    Ui::GSmartFireStation *ui;
};

#endif // GSMARTFIRESTATION_H
