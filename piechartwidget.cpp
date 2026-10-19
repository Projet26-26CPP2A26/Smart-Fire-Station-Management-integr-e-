#include "piechartwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QFont>
#include <QRectF>
#include <QtMath>

PieChartWidget::PieChartWidget(const QString &centerLabel, QWidget *parent)
    : QWidget(parent), m_centerLabel(centerLabel)
{
    setMinimumHeight(235);
    setMinimumWidth(250);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}
void PieChartWidget::setData(const QStringList &labels, const QList<int> &values)
{
    m_labels = labels; m_values = values; update();
}
void PieChartWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    const QColor colors[] = {QColor("#1F4E79"), QColor("#DC3C2D"), QColor("#2E7D32"), QColor("#E6A23C"), QColor("#7C3AED"), QColor("#0891B2"), QColor("#64748B"), QColor("#DB2777")};
    int total = 0;
    for (int v : m_values) total += qMax(0, v);
    // Responsive layout: reserve a clear legend area and keep the circle fully visible.
    const int legendWidth = qMin(190, qMax(112, width() * 46 / 100));
    const int availablePie = qMax(90, width() - legendWidth - 24);
    const int diameter = qMax(90, qMin(170, qMin(availablePie - 8, height() - 24)));
    const int px = 8;
    const int py = qMax(8, (height() - diameter) / 2);
    QRectF pie(px, py, diameter, diameter);
    if (total <= 0) {
        p.setPen(QPen(QColor("#E5E7EB"), 18)); p.setBrush(Qt::NoBrush);
        p.drawEllipse(pie.adjusted(10,10,-10,-10));
        p.setPen(QColor("#64748B")); p.drawText(pie, Qt::AlignCenter, "Aucune donnée"); return;
    }
    int start = 90 * 16;
    for (int i=0; i<m_values.size(); ++i) {
        int val = qMax(0,m_values[i]); if (!val) continue;
        int span = -qRound(360.0 * 16 * val / total);
        p.setPen(QPen(Qt::white, 1.5)); p.setBrush(colors[i % 8]); p.drawPie(pie, start, span); start += span;
    }
    int hole = diameter / 3;
    p.setPen(Qt::white); p.setBrush(Qt::white); p.drawEllipse(pie.adjusted(hole,hole,-hole,-hole));
    p.setPen(QColor("#1F2937")); QFont f=p.font(); f.setBold(true); f.setPointSize(17); p.setFont(f);
    p.drawText(QRectF(pie.x()+diameter/4, pie.y()+diameter/2-18, diameter/2, 24), Qt::AlignCenter, QString::number(total));
    f.setBold(false); f.setPointSize(8); p.setFont(f); p.setPen(QColor("#64748B"));
    p.drawText(QRectF(pie.x()+diameter/4, pie.y()+diameter/2+5, diameter/2, 18), Qt::AlignCenter, QStringLiteral("Total"));
    const int legendX = px + diameter + 12;
    const int lineHeight = qMin(28, qMax(20, (height()-16) / qMax(1,m_labels.size())));
    f=p.font(); f.setPointSize(8); p.setFont(f);
    for (int i=0; i<m_labels.size() && i<m_values.size(); ++i) {
        int y = 8 + i * lineHeight;
        p.setPen(Qt::NoPen); p.setBrush(colors[i%8]); p.drawRoundedRect(QRectF(legendX,y+5,9,9),2,2);
        double pct = total ? (100.0*m_values[i]/total) : 0;
        p.setPen(QColor("#334155"));
        QString line = QString("%1  %2 (%3%)").arg(m_labels[i]).arg(m_values[i]).arg(qRound(pct));
        QRectF textRect(legendX+14,y,width()-legendX-17,lineHeight);
        p.drawText(textRect, Qt::AlignLeft|Qt::AlignVCenter|Qt::TextWordWrap, line);
    }
}
