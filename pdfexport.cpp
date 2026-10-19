#include "pdfexport.h"

#include <QDateTime>
#include <QFileInfo>
#include <QPdfWriter>
#include <QTextDocument>

bool creerPdfTableau(const QString &chemin, const QString &titre,
                     const QStringList &entetes, const QList<QStringList> &lignes)
{
    // 1) On écrit le contenu du PDF en HTML (titre + tableau)
    QString html = "<h2 style='color:#1F4E79;'>Smart Fire Station Management</h2>";
    html += "<h3>" + titre + "</h3>";
    html += "<p>Exporté le " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm") + "</p>";
    html += "<table border='1' cellspacing='0' cellpadding='5' width='100%'><tr>";
    for (int c = 0; c < entetes.size(); c++)
        html += "<th bgcolor='#1F4E79' style='color:white;'>" + entetes[c] + "</th>";
    html += "</tr>";
    for (int l = 0; l < lignes.size(); l++) {
        html += "<tr>";
        for (int c = 0; c < lignes[l].size(); c++)
            html += "<td>" + lignes[l][c] + "</td>";
        html += "</tr>";
    }
    html += "</table>";

    // 2) On "imprime" ce HTML dans un fichier PDF
    QPdfWriter writer(chemin);
    QTextDocument document;
    document.setHtml(html);
    document.print(&writer);

    return QFileInfo(chemin).size() > 0;
}
