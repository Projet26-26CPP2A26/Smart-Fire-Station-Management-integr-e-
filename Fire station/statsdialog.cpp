#include "statsdialog.h"
#include "styleutils.h"

#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace {
class DonutChart : public QWidget
{
public:
    DonutChart(const QStringList &labels, const QList<int> &values, QWidget *parent = 0)
        : QWidget(parent), m_labels(labels), m_values(values)
    {
        setMinimumSize(280, 230);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        setFixedHeight(250);
    }
protected:
    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        const int total = [&]() { int t=0; for (int v : m_values) t += v; return t; }();
        QRectF rect((width()-190)/2.0, 14, 190, 190);
        const QColor colors[] = {QColor("#2E7D32"), QColor("#DC3C2D"), QColor("#1F4E79"), QColor("#E6A23C"), QColor("#7E57C2"), QColor("#607D8B")};
        if (total <= 0) {
            painter.setPen(QPen(QColor("#E5E7EB"), 26)); painter.setBrush(Qt::NoBrush);
            painter.drawEllipse(rect.adjusted(18,18,-18,-18));
            painter.setPen(QColor("#64748B")); painter.drawText(rect, Qt::AlignCenter, "Aucune donnée");
            return;
        }
        int start = 90 * 16;
        for (int i=0; i<m_values.size(); ++i) {
            int span = -qRound(360.0 * 16 * m_values[i] / total);
            painter.setPen(QPen(Qt::white, 2)); painter.setBrush(colors[i % 6]);
            painter.drawPie(rect, start, span); start += span;
        }
        painter.setPen(Qt::white); painter.setBrush(Qt::white);
        painter.drawEllipse(rect.adjusted(47,47,-47,-47));
        painter.setPen(QColor("#1F2937"));
        QFont f = painter.font(); f.setBold(true); f.setPointSize(20); painter.setFont(f);
        painter.drawText(rect.adjusted(35,55,-35,-55), Qt::AlignCenter, QString::number(total));
        f.setBold(false); f.setPointSize(9); painter.setFont(f); painter.setPen(QColor("#64748B"));
        painter.drawText(rect.adjusted(35,87,-35,-30), Qt::AlignCenter, "TOTAL");
    }
private:
    QStringList m_labels;
    QList<int> m_values;
};
}

StatCritere compterParValeur(const QString &nom, const QStringList &possibles,
                             const QStringList &reelles)
{
    StatCritere resultat; resultat.nom = nom;
    for (int p=0; p<possibles.size(); ++p) {
        int n=0; for (int r=0; r<reelles.size(); ++r) if (reelles[r] == possibles[p]) ++n;
        if (n>0) { resultat.etiquettes << possibles[p]; resultat.valeurs << n; }
    }
    return resultat;
}

StatsDialog::StatsDialog(const QString &titre, const QList<StatCritere> &criteres, QWidget *parent)
    : QDialog(parent)
{
    m_criteres=criteres; setWindowTitle(titre); setMinimumSize(540, 480);
    QLabel *labelTitre=new QLabel(titre); labelTitre->setProperty("class","cardTitle");
    m_combo=new QComboBox;
    for (int i=0;i<m_criteres.size();++i) m_combo->addItem(m_criteres[i].nom);
    QHBoxLayout *ligneCritere=new QHBoxLayout;
    ligneCritere->addWidget(new QLabel("Répartition selon :")); ligneCritere->addWidget(m_combo); ligneCritere->addStretch();
    m_grille=new QGridLayout; m_grille->setVerticalSpacing(10);
    QPushButton *fermer=new QPushButton("Fermer"); fermer->setProperty("class","btnPrimary");
    connect(fermer,SIGNAL(clicked()),this,SLOT(close()));
    QHBoxLayout *ligneBoutons=new QHBoxLayout; ligneBoutons->addStretch(); ligneBoutons->addWidget(fermer);
    QVBoxLayout *principal=new QVBoxLayout(this); principal->setContentsMargins(24,20,24,20); principal->setSpacing(12);
    principal->addWidget(labelTitre); principal->addLayout(ligneCritere); principal->addLayout(m_grille,1); principal->addLayout(ligneBoutons);
    connect(m_combo,SIGNAL(currentIndexChanged(int)),this,SLOT(afficherCritere(int)));
    afficherCritere(0); repolish(this);
}

void StatsDialog::afficherCritere(int index)
{
    if (index<0 || index>=m_criteres.size()) return;
    while (QLayoutItem *item=m_grille->takeAt(0)) { if (item->widget()) item->widget()->deleteLater(); delete item; }
    const StatCritere c=m_criteres[index]; int total=0; for (int v:c.valeurs) total+=v;
    DonutChart *chart=new DonutChart(c.etiquettes,c.valeurs,this); m_grille->addWidget(chart,0,0,1,3,Qt::AlignHCenter);
    const QColor colors[]={QColor("#2E7D32"),QColor("#DC3C2D"),QColor("#1F4E79"),QColor("#E6A23C"),QColor("#7E57C2"),QColor("#607D8B")};
    for (int i=0;i<c.etiquettes.size();++i) {
        QLabel *swatch=new QLabel("●"); swatch->setStyleSheet(QString("color:%1; font-size:17px;").arg(colors[i%6].name()));
        int pct=total ? qRound(100.0*c.valeurs[i]/total) : 0;
        QLabel *label=new QLabel(c.etiquettes[i]); QLabel *value=new QLabel(QString("%1  •  %2 %").arg(c.valeurs[i]).arg(pct));
        value->setStyleSheet("font-weight:600; color:#1F2937;");
        m_grille->addWidget(swatch,i+1,0); m_grille->addWidget(label,i+1,1); m_grille->addWidget(value,i+1,2,Qt::AlignRight);
    }
    QLabel *totalLabel=new QLabel(QString("Total : %1 personne(s)").arg(total)); totalLabel->setStyleSheet("font-weight:600; color:#1F4E79; padding-top:8px;");
    m_grille->addWidget(totalLabel,c.etiquettes.size()+1,0,1,3);
    m_grille->setColumnStretch(1,1);
}
