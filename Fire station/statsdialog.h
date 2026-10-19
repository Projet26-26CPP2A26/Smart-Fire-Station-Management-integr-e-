#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QStringList>

class QComboBox;
class QGridLayout;

// Un critère de statistique. Exemple : nom = "Grade",
// etiquettes = Capitaine, Sergent...  et valeurs = 1, 2...
struct StatCritere
{
    QString nom;
    QStringList etiquettes;
    QList<int> valeurs;
};

// Compte, pour chaque valeur possible, combien de fois elle apparaît dans 'reelles'
StatCritere compterParValeur(const QString &nom, const QStringList &possibles,
                             const QStringList &reelles);

// Fenêtre de statistiques graphiques avec diagramme circulaire (donut) et pourcentages
class StatsDialog : public QDialog
{
    Q_OBJECT
public:
    StatsDialog(const QString &titre, const QList<StatCritere> &criteres, QWidget *parent = 0);

private slots:
    void afficherCritere(int index);

private:
    QList<StatCritere> m_criteres;
    QComboBox *m_combo;
    QGridLayout *m_grille;
};

#endif // STATSDIALOG_H
