#include "gsmartfirestation.h"

#include <QApplication>
#include <QFile>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Style Fusion + feuille de style style.qss (charte graphique)
    a.setStyle(QStyleFactory::create("Fusion"));
    QFile fichierStyle(":/style/style.qss");
    if (fichierStyle.open(QFile::ReadOnly | QFile::Text))
        a.setStyleSheet(QString::fromUtf8(fichierStyle.readAll()));

    GSmartFireStation fenetre;
    fenetre.show();
    return a.exec();
}
