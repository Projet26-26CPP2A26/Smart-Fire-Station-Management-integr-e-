#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H
#include <QWidget>
#include <QStringList>
#include <QList>
class PieChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PieChartWidget(const QString &centerLabel, QWidget *parent = 0);
    void setData(const QStringList &labels, const QList<int> &values);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QString m_centerLabel;
    QStringList m_labels;
    QList<int> m_values;
};
#endif
