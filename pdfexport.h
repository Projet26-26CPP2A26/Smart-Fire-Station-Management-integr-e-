#ifndef PDFEXPORT_H
#define PDFEXPORT_H

#include <QList>
#include <QString>
#include <QStringList>

// Crée un fichier PDF contenant un titre et un tableau. Retourne true si le fichier est créé.
bool creerPdfTableau(const QString &chemin, const QString &titre,
                     const QStringList &entetes, const QList<QStringList> &lignes);

#endif // PDFEXPORT_H
