#ifndef STYLEUTILS_H
#define STYLEUTILS_H

#include <QList>
#include <QStyle>
#include <QWidget>

// Les propriétés class="..." (ex : class="btnPrimary") ne sont prises en compte par style.qss
// qu'après un "re-polish" : on demande au style de se réappliquer sur chaque widget.
inline void repolish(QWidget *fenetre)
{
    QList<QWidget *> widgets = fenetre->findChildren<QWidget *>();
    for (int i = 0; i < widgets.size(); i++) {
        widgets[i]->style()->unpolish(widgets[i]);
        widgets[i]->style()->polish(widgets[i]);
    }
    fenetre->style()->unpolish(fenetre);
    fenetre->style()->polish(fenetre);
}

#endif // STYLEUTILS_H
