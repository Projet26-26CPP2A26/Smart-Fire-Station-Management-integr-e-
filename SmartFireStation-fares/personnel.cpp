#include "personnel.h"
#include "gsmartfirestation.h"   // DatabaseManager (connexion Oracle partagee)

#include <QComboBox>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QDialog>
#include <QFileDialog>
#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QPixmap>
#include <QPushButton>
#include <QRegularExpression>
#include <QScrollArea>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QStatusBar>
#include <QTableView>
#include <QTextDocument>
#include <QUrl>
#include <QVBoxLayout>
#include <QVariant>

static QString s_erreur; // dernier message d'erreur SQL

// =====================================================================
//  2. PERSONNEL (modèle : entité + SQL + métiers + contrôle de saisie)
// =====================================================================
Personnel::Personnel()
{
    m_id = 0;
}

Personnel::Personnel(int id, const QString &nom, const QString &prenom, const QString &grade,
                     const QString &poste, const QString &telephone, const QString &email,
                     const QString &motDePasse, const QString &questionSecrete,
                     const QString &reponseSecrete, const QString &disponibilite)
{
    m_id = id;
    m_nom = nom;
    m_prenom = prenom;
    m_grade = grade;
    m_poste = poste;
    m_telephone = telephone;
    m_email = email;
    m_motDePasse = motDePasse;
    m_questionSecrete = questionSecrete;
    m_reponseSecrete = reponseSecrete;
    m_disponibilite = disponibilite;
}

// ------------------------------------------------------------------
//  CREATE : l'identifiant est généré par la séquence seq_personnel
// ------------------------------------------------------------------
bool Personnel::ajouter() const
{
    QSqlQuery query(DatabaseManager::database());
    query.prepare("INSERT INTO personnel (id_personnel, nom, prenom, grade, poste, telephone, email, "
                  "mot_de_passe, question_secrete, reponse_secrete, disponibilite) "
                  "VALUES (seq_personnel.NEXTVAL, :nom, :prenom, :grade, :poste, :telephone, :email, "
                  ":mdp, :question, :reponse, :dispo)");
    query.bindValue(":nom", m_nom);
    query.bindValue(":prenom", m_prenom);
    query.bindValue(":grade", m_grade);
    query.bindValue(":poste", m_poste);
    query.bindValue(":telephone", m_telephone);
    query.bindValue(":email", m_email);
    query.bindValue(":mdp", hacher(m_motDePasse));
    query.bindValue(":question", m_questionSecrete);
    query.bindValue(":reponse", hacher(normaliser(m_reponseSecrete)));
    query.bindValue(":dispo", m_disponibilite);

    if (!query.exec()) {
        s_erreur = query.lastError().text();
        qDebug() << "Erreur ajouter :" << s_erreur;
        return false;
    }
    return true;
}

// ------------------------------------------------------------------
//  UPDATE : le mot de passe et la réponse ne changent que s'ils sont renseignés
// ------------------------------------------------------------------
bool Personnel::modifier() const
{
    QString sql = "UPDATE personnel SET nom = :nom, prenom = :prenom, grade = :grade, poste = :poste, "
                  "telephone = :telephone, email = :email, question_secrete = :question, "
                  "disponibilite = :dispo";
    if (!m_motDePasse.isEmpty())
        sql += ", mot_de_passe = :mdp";
    if (!m_reponseSecrete.isEmpty())
        sql += ", reponse_secrete = :reponse";
    sql += " WHERE id_personnel = :id";

    QSqlQuery query(DatabaseManager::database());
    query.prepare(sql);
    query.bindValue(":nom", m_nom);
    query.bindValue(":prenom", m_prenom);
    query.bindValue(":grade", m_grade);
    query.bindValue(":poste", m_poste);
    query.bindValue(":telephone", m_telephone);
    query.bindValue(":email", m_email);
    query.bindValue(":question", m_questionSecrete);
    query.bindValue(":dispo", m_disponibilite);
    if (!m_motDePasse.isEmpty())
        query.bindValue(":mdp", hacher(m_motDePasse));
    if (!m_reponseSecrete.isEmpty())
        query.bindValue(":reponse", hacher(normaliser(m_reponseSecrete)));
    query.bindValue(":id", m_id);

    if (!query.exec()) {
        s_erreur = query.lastError().text();
        qDebug() << "Erreur modifier :" << s_erreur;
        return false;
    }
    return true;
}

// ------------------------------------------------------------------
//  DELETE
// ------------------------------------------------------------------
bool Personnel::supprimer(int id)
{
    QSqlQuery query(DatabaseManager::database());
    query.prepare("DELETE FROM personnel WHERE id_personnel = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        s_erreur = query.lastError().text();
        qDebug() << "Erreur supprimer :" << s_erreur;
        return false;
    }
    return true;
}

// ------------------------------------------------------------------
//  READ : modèle pour le tableau, avec recherche (ID, nom, prénom ou grade) et tri
//  tri : 0 = ID, 1 = grade (du plus élevé au moins élevé), 2 = disponibilité, 3 = nom
// ------------------------------------------------------------------
QSqlQueryModel *Personnel::afficher(const QString &recherche, int tri)
{
    QString ordre = "ORDER BY p.id_personnel";
    if (tri == 1)
        ordre = "ORDER BY CASE p.grade WHEN 'Colonel' THEN 1 WHEN 'Commandant' THEN 2 "
                "WHEN 'Capitaine' THEN 3 WHEN 'Lieutenant' THEN 4 WHEN 'Adjudant' THEN 5 "
                "WHEN 'Sergent' THEN 6 WHEN 'Caporal' THEN 7 ELSE 8 END, p.nom";
    else if (tri == 2)
        ordre = "ORDER BY CASE p.disponibilite WHEN 'Disponible' THEN 1 WHEN 'En mission' THEN 2 "
                "ELSE 3 END, p.nom";
    else if (tri == 3)
        ordre = "ORDER BY LOWER(p.nom), LOWER(p.prenom)";

    QString sql =
        "SELECT p.id_personnel, p.nom, p.prenom, p.grade, p.poste, p.telephone, p.disponibilite "
        "FROM personnel p "
        "WHERE LOWER(p.nom) LIKE :r1 OR LOWER(p.prenom) LIKE :r2 OR LOWER(p.grade) LIKE :r3 "
        "OR TO_CHAR(p.id_personnel) LIKE :r4 "
        "OR LOWER('P' || LPAD(TO_CHAR(p.id_personnel), 3, '0')) LIKE :r5 "
        + ordre;

    QString motif = "%" + recherche.trimmed().toLower() + "%";
    QSqlQuery query(DatabaseManager::database());
    query.prepare(sql);
    query.bindValue(":r1", motif);
    query.bindValue(":r2", motif);
    query.bindValue(":r3", motif);
    query.bindValue(":r4", motif);
    query.bindValue(":r5", motif);
    if (!query.exec()) {
        s_erreur = query.lastError().text();
        qDebug() << "Erreur afficher :" << s_erreur;
    }

    PersonnelModel *model = new PersonnelModel();
    model->setQuery(std::move(query));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Grade"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Disponibilité"));
    return model;
}

// Lire un membre (le mot de passe et la réponse ne sont jamais relus)
bool Personnel::trouver(int id, Personnel &resultat)
{
    QSqlQuery query(DatabaseManager::database());
    query.prepare("SELECT nom, prenom, grade, poste, telephone, email, question_secrete, disponibilite "
                  "FROM personnel WHERE id_personnel = :id");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) {
        s_erreur = query.lastError().text();
        return false;
    }
    resultat = Personnel(id, query.value(0).toString(), query.value(1).toString(),
                         query.value(2).toString(), query.value(3).toString(),
                         query.value(4).toString(), query.value(5).toString(),
                         QString(), query.value(6).toString(), QString(),
                         query.value(7).toString());
    return true;
}

// ------------------------------------------------------------------
//  Authentification : e-mail + mot de passe (comparaison des empreintes SHA-256)
// ------------------------------------------------------------------
bool Personnel::authentifier(const QString &email, const QString &motDePasse, Personnel &connecte)
{
    QSqlQuery query(DatabaseManager::database());
    query.prepare("SELECT id_personnel, nom, prenom, grade, poste FROM personnel "
                  "WHERE LOWER(email) = :email AND mot_de_passe = :mdp");
    query.bindValue(":email", email.trimmed().toLower());
    query.bindValue(":mdp", hacher(motDePasse));
    if (!query.exec()) {
        s_erreur = query.lastError().text();
        qDebug() << "Erreur authentifier :" << s_erreur;
        return false;
    }
    if (!query.next())
        return false;
    connecte.setId(query.value(0).toInt());
    connecte.setNom(query.value(1).toString());
    connecte.setPrenom(query.value(2).toString());
    connecte.setGrade(query.value(3).toString());
    connecte.setPoste(query.value(4).toString());
    return true;
}

// ------------------------------------------------------------------
//  Mot de passe oublié : question secrète, puis réinitialisation
// ------------------------------------------------------------------
QString Personnel::questionDe(const QString &email)
{
    QSqlQuery query(DatabaseManager::database());
    query.prepare("SELECT question_secrete FROM personnel WHERE LOWER(email) = :email");
    query.bindValue(":email", email.trimmed().toLower());
    if (query.exec() && query.next())
        return query.value(0).toString();
    return QString();
}

bool Personnel::reinitialiserMotDePasse(const QString &email, const QString &reponse,
                                        const QString &nouveauMotDePasse)
{
    QSqlQuery query(DatabaseManager::database());
    query.prepare("UPDATE personnel SET mot_de_passe = :mdp "
                  "WHERE LOWER(email) = :email AND reponse_secrete = :reponse");
    query.bindValue(":mdp", hacher(nouveauMotDePasse));
    query.bindValue(":email", email.trimmed().toLower());
    query.bindValue(":reponse", hacher(normaliser(reponse)));
    if (!query.exec()) {
        s_erreur = query.lastError().text();
        qDebug() << "Erreur reinitialiser :" << s_erreur;
        return false;
    }
    return query.numRowsAffected() > 0;   // 0 ligne = mauvaise réponse
}

// ------------------------------------------------------------------
//  Statistiques : nombre de membres par grade (grades sans membre = 0)
// ------------------------------------------------------------------
QList<int> Personnel::statistiquesParGrade()
{
    const QStringList liste = grades();
    QList<int> resultat;
    for (int i = 0; i < liste.size(); i++)
        resultat << 0;

    QSqlQuery query(DatabaseManager::database());
    query.prepare("SELECT grade, COUNT(*) FROM personnel GROUP BY grade");
    if (!query.exec()) {
        s_erreur = query.lastError().text();
        qDebug() << "Erreur statistiques :" << s_erreur;
        return resultat;
    }
    while (query.next()) {
        int position = liste.indexOf(query.value(0).toString());
        if (position >= 0)
            resultat[position] = query.value(1).toInt();
    }
    return resultat;
}

// ------------------------------------------------------------------
//  Contrôle de saisie
// ------------------------------------------------------------------
bool Personnel::nomValide(const QString &texte)
{
    static const QRegularExpression re("^[\\p{L}][\\p{L} '\\-]*$",
                                       QRegularExpression::UseUnicodePropertiesOption);
    return re.match(texte.trimmed()).hasMatch();
}

bool Personnel::telephoneValide(const QString &texte)
{
    QString chiffres = texte;
    chiffres.remove(' ').remove('-');
    static const QRegularExpression re("^[0-9]{8}$");
    return re.match(chiffres).hasMatch();
}

bool Personnel::emailValide(const QString &texte)
{
    static const QRegularExpression re("^[^@\\s]+@[^@\\s]+\\.[^@\\s]+$");
    return re.match(texte.trimmed()).hasMatch();
}

bool Personnel::motDePasseValide(const QString &texte)
{
    if (texte.length() < 6)
        return false;
    bool lettre = false, chiffre = false;
    for (const QChar &c : texte) {
        if (c.isLetter())
            lettre = true;
        else if (c.isDigit())
            chiffre = true;
    }
    return lettre && chiffre;
}

// ------------------------------------------------------------------
//  Outils
// ------------------------------------------------------------------
QString Personnel::hacher(const QString &texte)
{
    return QString::fromLatin1(QCryptographicHash::hash(texte.toUtf8(), QCryptographicHash::Sha256).toHex());
}

QString Personnel::normaliser(const QString &reponse)
{
    return reponse.trimmed().toLower();
}

QString Personnel::derniereErreur()
{
    return s_erreur;
}

QStringList Personnel::grades()
{
    return QStringList() << "Colonel" << "Commandant" << "Capitaine" << "Lieutenant"
                         << "Adjudant" << "Sergent" << "Caporal" << "Sapeur";
}

QStringList Personnel::postes()
{
    return QStringList() << "Chef de garde" << "Intervention" << "Secours" << "Logistique" << "Administration";
}

QStringList Personnel::disponibilites()
{
    return QStringList() << "Disponible" << "En mission" << "En congé";
}

QStringList Personnel::questions()
{
    return QStringList() << "Quelle est votre ville de naissance ?"
                         << "Quel est le nom de votre premier animal ?"
                         << "Quel est le nom de votre premier professeur ?"
                         << "Quel est le nom de votre meilleur ami d'enfance ?";
}

// =====================================================================
//  3. PERSONNELMODEL (affichage du tableau)
//  Rôle Qt::UserRole : valeur brute de la cellule (sert à retrouver l'ID numérique).
// =====================================================================
QVariant PersonnelModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const int colonne = index.column();
    const QVariant brut = QSqlQueryModel::data(index, Qt::DisplayRole);

    if (role == Qt::UserRole)
        return brut;

    if (role == Qt::DisplayRole) {
        if (colonne == 0)                                   // 1 -> P001
            return QString("P%1").arg(brut.toInt(), 3, 10, QChar('0'));
        if (colonne == 5) {                                 // 22000111 -> 22 000 111
            QString tel = brut.toString();
            tel.remove(' ').remove('-');
            if (tel.length() == 8)
                return tel.left(2) + " " + tel.mid(2, 3) + " " + tel.mid(5);
        }
        return brut;
    }

    if (colonne == 6 && role == Qt::ForegroundRole) {       // disponibilité en couleur
        const QString dispo = brut.toString();
        if (dispo == "Disponible")
            return QColor("#2E7D32");
        if (dispo == "En mission")
            return QColor("#B45309");
        return QColor("#6B7280");
    }
    if (colonne == 6 && role == Qt::FontRole) {
        QFont police;
        police.setBold(true);
        return police;
    }
    return QSqlQueryModel::data(index, role);
}

// =====================================================================
//  4. PERSONNELPIECHART (diagramme circulaire avec légende)
// =====================================================================
PersonnelPieChart::PersonnelPieChart(QWidget *parent)
    : QWidget(parent)
{
    setMinimumHeight(235);
    setMinimumWidth(250);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

void PersonnelPieChart::setData(const QStringList &labels, const QList<int> &values)
{
    m_labels = labels;
    m_values = values;
    update();
}

void PersonnelPieChart::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    const QColor colors[] = {QColor("#1F4E79"), QColor("#DC3C2D"), QColor("#2E7D32"), QColor("#E6A23C"),
                             QColor("#7C3AED"), QColor("#0891B2"), QColor("#64748B"), QColor("#DB2777")};
    int total = 0;
    for (int v : m_values)
        total += qMax(0, v);

    // Disposition adaptative : zone de légende réservée, cercle toujours visible en entier
    const int legendWidth = qMin(190, qMax(112, width() * 46 / 100));
    const int availablePie = qMax(90, width() - legendWidth - 24);
    const int diameter = qMax(90, qMin(170, qMin(availablePie - 8, height() - 24)));
    const int px = 8;
    const int py = qMax(8, (height() - diameter) / 2);
    QRectF pie(px, py, diameter, diameter);

    if (total <= 0) {
        p.setPen(QPen(QColor("#E5E7EB"), 18));
        p.setBrush(Qt::NoBrush);
        p.drawEllipse(pie.adjusted(10, 10, -10, -10));
        p.setPen(QColor("#64748B"));
        p.drawText(pie, Qt::AlignCenter, "Aucune donnée");
        return;
    }

    // Secteurs
    int start = 90 * 16;
    for (int i = 0; i < m_values.size(); ++i) {
        int val = qMax(0, m_values[i]);
        if (!val)
            continue;
        int span = -qRound(360.0 * 16 * val / total);
        p.setPen(QPen(Qt::white, 1.5));
        p.setBrush(colors[i % 8]);
        p.drawPie(pie, start, span);
        start += span;
    }

    // Centre blanc avec le total
    int hole = diameter / 3;
    p.setPen(Qt::white);
    p.setBrush(Qt::white);
    p.drawEllipse(pie.adjusted(hole, hole, -hole, -hole));
    p.setPen(QColor("#1F2937"));
    QFont f = p.font();
    f.setBold(true);
    f.setPointSize(17);
    p.setFont(f);
    p.drawText(QRectF(pie.x() + diameter / 4, pie.y() + diameter / 2 - 18, diameter / 2, 24),
               Qt::AlignCenter, QString::number(total));
    f.setBold(false);
    f.setPointSize(8);
    p.setFont(f);
    p.setPen(QColor("#64748B"));
    p.drawText(QRectF(pie.x() + diameter / 4, pie.y() + diameter / 2 + 5, diameter / 2, 18),
               Qt::AlignCenter, QStringLiteral("Total"));

    // Légende : un grade par ligne avec effectif et pourcentage
    const int legendX = px + diameter + 12;
    const int lineHeight = qMin(28, qMax(20, (height() - 16) / qMax(1, m_labels.size())));
    f = p.font();
    f.setPointSize(8);
    p.setFont(f);
    for (int i = 0; i < m_labels.size() && i < m_values.size(); ++i) {
        int y = 8 + i * lineHeight;
        p.setPen(Qt::NoPen);
        p.setBrush(colors[i % 8]);
        p.drawRoundedRect(QRectF(legendX, y + 5, 9, 9), 2, 2);
        double pct = total ? (100.0 * m_values[i] / total) : 0;
        p.setPen(QColor("#334155"));
        QString line = QString("%1  %2 (%3%)").arg(m_labels[i]).arg(m_values[i]).arg(qRound(pct));
        QRectF textRect(legendX + 14, y, width() - legendX - 17, lineHeight);
        p.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, line);
    }
}

// =====================================================================
//  5. PERSONNELPAGE (vue : page intégrée à la fenêtre principale)
// =====================================================================
PersonnelPage::PersonnelPage(QWidget *parent)
    : QWidget(parent), m_model(nullptr), m_idEdition(0), m_tri(0)
{
    setObjectName("pagePersonnel");
    construireInterface();
    viderFormulaire();
    // Les donnees sont chargees par la fenetre principale apres la connexion
    // Oracle (appel de rafraichir() depuis GSmartFireStation::demarrer()).
}

PersonnelPage::~PersonnelPage()
{
    delete m_model;
}

// ------------------------------------------------------------------
//  Messages : relayés vers la barre d'état de la fenêtre principale
// ------------------------------------------------------------------
void PersonnelPage::showMessage(const QString &texte, int duree)
{
    if (QMainWindow *fenetre = qobject_cast<QMainWindow *>(window()))
        fenetre->statusBar()->showMessage(texte, duree);
}

void PersonnelPage::clearMessage()
{
    if (QMainWindow *fenetre = qobject_cast<QMainWindow *>(window()))
        fenetre->statusBar()->clearMessage();
}

// ------------------------------------------------------------------
//  Construction de l'interface : contenu de la page "Gestion du personnel"
//  (la barre latérale est celle, partagée, de la fenêtre principale)
// ------------------------------------------------------------------
void PersonnelPage::construireInterface()
{
    QVBoxLayout *vPage = new QVBoxLayout(this);
    vPage->setSpacing(14);
    vPage->setContentsMargins(30, 26, 30, 20);

    QLabel *titre = new QLabel("Gestion du personnel");
    titre->setProperty("class", "pageTitle");
    titre->setMinimumHeight(36);
    QHBoxLayout *entete = new QHBoxLayout();
    entete->addWidget(titre);
    entete->addStretch();
    vPage->addLayout(entete);

    QLabel *sousTitre = new QLabel("CRUD, recherche, tri, export et statistiques");
    sousTitre->setProperty("class", "pageSubtitle");
    vPage->addWidget(sousTitre);

    QFrame *separateur = new QFrame();
    separateur->setFrameShape(QFrame::HLine);
    separateur->setFrameShadow(QFrame::Plain);
    separateur->setProperty("class", "separator");
    vPage->addWidget(separateur);

    // ----- Barre d'outils : recherche, tri, export -----
    QFrame *barre = new QFrame();
    barre->setProperty("class", "card");
    barre->setFrameShape(QFrame::StyledPanel);
    barre->setFrameShadow(QFrame::Plain);
    QHBoxLayout *laBarreOutils = new QHBoxLayout(barre);
    laBarreOutils->setSpacing(12);
    laBarreOutils->setContentsMargins(18, 12, 18, 12);

    m_recherche = new QLineEdit();
    m_recherche->setPlaceholderText("Nom / ID / Grade");
    m_recherche->setClearButtonEnabled(true);
    m_recherche->setMinimumWidth(220);
    m_comboTri = new QComboBox();
    m_comboTri->setMinimumWidth(150);
    m_comboTri->addItems(QStringList() << "Grade" << "Disponibilité" << "Nom");

    QPushButton *btnRechercher = new QPushButton("Rechercher");
    btnRechercher->setProperty("class", "btnPrimary");
    QPushButton *btnTrier = new QPushButton("Trier");
    btnTrier->setProperty("class", "btnSecondary");
    QPushButton *btnExport = new QPushButton("Exporter PDF");
    btnExport->setProperty("class", "btnSecondary");
    for (QPushButton *b : {btnRechercher, btnTrier, btnExport})
        b->setCursor(Qt::PointingHandCursor);

    laBarreOutils->addWidget(new QLabel("Recherche :"));
    laBarreOutils->addWidget(m_recherche);
    laBarreOutils->addWidget(new QLabel("Trier par :"));
    laBarreOutils->addWidget(m_comboTri);
    laBarreOutils->addWidget(btnRechercher);
    laBarreOutils->addWidget(btnTrier);
    laBarreOutils->addWidget(btnExport);
    laBarreOutils->addStretch();
    vPage->addWidget(barre);

    // ----- Corps : colonne gauche (tableau, boutons, formulaire) + colonne droite (statistiques) -----
    QHBoxLayout *corps = new QHBoxLayout();
    corps->setSpacing(18);
    vPage->addLayout(corps, 1);

    QVBoxLayout *gauche = new QVBoxLayout();
    gauche->setSpacing(14);
    corps->addLayout(gauche, 1);

    // Tableau
    m_table = new QTableView();
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setAlternatingRowColors(true);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setShowGrid(false);
    m_table->verticalHeader()->setVisible(false);
    m_table->verticalHeader()->setDefaultSectionSize(30);
    m_table->horizontalHeader()->setHighlightSections(false);
    m_table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    gauche->addWidget(m_table);

    // Boutons Ajouter / Modifier / Supprimer
    QWidget *actions = new QWidget();
    QHBoxLayout *laActions = new QHBoxLayout(actions);
    laActions->setContentsMargins(0, 8, 0, 0);
    laActions->setSpacing(10);
    QPushButton *btnAjouter = new QPushButton("Ajouter");
    btnAjouter->setProperty("class", "btnSuccess");
    QPushButton *btnModifier = new QPushButton("Modifier");
    btnModifier->setProperty("class", "btnSecondary");
    QPushButton *btnSupprimer = new QPushButton("Supprimer");
    btnSupprimer->setProperty("class", "btnDanger");
    for (QPushButton *b : {btnAjouter, btnModifier, btnSupprimer}) {
        b->setCursor(Qt::PointingHandCursor);
        laActions->addWidget(b);
    }
    laActions->addStretch(1);
    gauche->addWidget(actions);

    // Formulaire permanent : l'ajout et la modification se font directement dans la page
    m_formulaire = new QGroupBox("Fiche du personnel — remplissez les champs puis validez");
    m_formulaire->setObjectName("formPersonnelInline");
    m_formulaire->setStyleSheet("QGroupBox { border: 1px solid #D7DEE8; border-radius: 8px; margin-top: 10px; padding: 10px; font-weight: 600; } "
                                "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px; color: #1F4E79; }");

    m_labelId = new QLabel();
    m_nom = new QLineEdit();
    m_nom->setPlaceholderText("Nom");
    m_prenom = new QLineEdit();
    m_prenom->setPlaceholderText("Prénom");
    m_grade = new QComboBox();
    m_grade->addItems(Personnel::grades());
    m_poste = new QComboBox();
    m_poste->addItems(Personnel::postes());
    m_telephone = new QLineEdit();
    m_telephone->setPlaceholderText("8 chiffres");
    m_email = new QLineEdit();
    m_email->setPlaceholderText("prenom.nom@firestation.tn");
    m_motDePasse = new QLineEdit();
    m_motDePasse->setEchoMode(QLineEdit::Password);
    m_motDePasse->setToolTip("6 caractères minimum, avec au moins une lettre et un chiffre");
    m_disponibilite = new QComboBox();
    m_disponibilite->addItems(Personnel::disponibilites());
    m_reponse = new QLineEdit();
    m_question = new QComboBox();
    m_question->addItems(Personnel::questions());

    QGridLayout *grille = new QGridLayout(m_formulaire);
    grille->setContentsMargins(8, 12, 8, 8);
    grille->setHorizontalSpacing(8);
    grille->setVerticalSpacing(5);
    auto ajouterChamp = [&](int ligne, int colonne, int largeur, const QString &nom, QWidget *champ) {
        QLabel *label = new QLabel(nom);
        label->setStyleSheet("font-weight: normal;");
        QVBoxLayout *cellule = new QVBoxLayout;
        cellule->setContentsMargins(0, 0, 0, 0);
        cellule->setSpacing(2);
        cellule->addWidget(label);
        cellule->addWidget(champ);
        QWidget *enveloppe = new QWidget;
        enveloppe->setLayout(cellule);
        grille->addWidget(enveloppe, ligne, colonne, 1, largeur);
    };
    // Deux lignes de champs, comme dans la maquette d'origine (6 colonnes)
    ajouterChamp(0, 0, 1, "ID", m_labelId);
    ajouterChamp(0, 1, 1, "Nom", m_nom);
    ajouterChamp(0, 2, 1, "Prénom", m_prenom);
    ajouterChamp(0, 3, 1, "Grade", m_grade);
    ajouterChamp(0, 4, 1, "Poste", m_poste);
    ajouterChamp(0, 5, 1, "Disponibilité", m_disponibilite);
    ajouterChamp(1, 0, 1, "Téléphone", m_telephone);
    ajouterChamp(1, 1, 1, "Email", m_email);
    ajouterChamp(1, 2, 1, "Mot de passe", m_motDePasse);
    ajouterChamp(1, 3, 2, "Question secrète", m_question);
    ajouterChamp(1, 5, 1, "Réponse secrète", m_reponse);
    for (int c = 0; c < 6; ++c)
        grille->setColumnStretch(c, 1);

    QPushButton *btnEnregistrer = new QPushButton("Enregistrer");
    btnEnregistrer->setObjectName("btnValiderPersonnelInline");
    btnEnregistrer->setStyleSheet("QPushButton { background:#1F4E79; color:white; border-radius:5px; padding:6px 10px; font-weight:600; }");
    QPushButton *btnEffacer = new QPushButton("Effacer");
    btnEffacer->setObjectName("btnAnnulerPersonnelInline");
    QHBoxLayout *boutonsForm = new QHBoxLayout;
    boutonsForm->addWidget(btnEnregistrer);
    boutonsForm->addWidget(btnEffacer);
    grille->addLayout(boutonsForm, 2, 0, 1, 6);
    gauche->addWidget(m_formulaire);

    // ----- Colonne droite : statistiques -----
    QVBoxLayout *droite = new QVBoxLayout();
    droite->setSpacing(16);
    corps->addLayout(droite);

    QFrame *cadreStats = new QFrame();
    cadreStats->setProperty("class", "card");
    cadreStats->setFrameShape(QFrame::StyledPanel);
    cadreStats->setFrameShadow(QFrame::Plain);
    cadreStats->setMinimumWidth(285);
    cadreStats->setMaximumWidth(340);
    cadreStats->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    QVBoxLayout *laStats = new QVBoxLayout(cadreStats);
    laStats->setSpacing(14);
    laStats->setContentsMargins(20, 18, 20, 18);

    QLabel *titreStats = new QLabel("Statistiques");
    titreStats->setProperty("class", "cardTitle");
    laStats->addWidget(titreStats);

    m_graphique = new PersonnelPieChart();
    m_graphique->setMinimumHeight(390);
    QScrollArea *defilement = new QScrollArea();
    defilement->setWidgetResizable(true);
    defilement->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    defilement->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    defilement->setFrameShape(QFrame::NoFrame);
    QWidget *contenuStats = new QWidget();
    QVBoxLayout *laContenu = new QVBoxLayout(contenuStats);
    laContenu->setContentsMargins(4, 4, 4, 4);
    laContenu->addWidget(m_graphique);
    defilement->setWidget(contenuStats);
    laStats->addWidget(defilement, 1);

    m_labelTotal = new QLabel("Total : 0 personnel(s)");
    m_labelTotal->setProperty("class", "cardDetail");
    laStats->addWidget(m_labelTotal);

    droite->addWidget(cadreStats);
    droite->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // ----- Connexions signaux / slots -----
    connect(btnAjouter, &QPushButton::clicked, this, &PersonnelPage::ajouterPersonnel);
    connect(btnModifier, &QPushButton::clicked, this, &PersonnelPage::modifierPersonnel);
    connect(btnSupprimer, &QPushButton::clicked, this, &PersonnelPage::supprimerPersonnel);
    connect(btnEnregistrer, &QPushButton::clicked, this, &PersonnelPage::enregistrer);
    connect(btnEffacer, &QPushButton::clicked, this, &PersonnelPage::viderFormulaire);
    connect(btnRechercher, &QPushButton::clicked, this, &PersonnelPage::rechercher);
    connect(m_recherche, &QLineEdit::textChanged, this, &PersonnelPage::rechercher);   // recherche pendant la frappe
    connect(btnTrier, &QPushButton::clicked, this, &PersonnelPage::trier);
    connect(btnExport, &QPushButton::clicked, this, &PersonnelPage::exporterPdf);
    connect(m_table, &QTableView::doubleClicked, this, &PersonnelPage::modifierPersonnel);   // double-clic = modifier
}

// ------------------------------------------------------------------
//  Authentification (métier avancé)
// ------------------------------------------------------------------
bool PersonnelPage::connexion()
{
    QDialog dlg;
    dlg.setWindowTitle("Authentification");
    dlg.setFixedWidth(380);

    QVBoxLayout *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 20, 24, 20);
    lay->setSpacing(8);
    QLabel *logo = new QLabel();
    logo->setPixmap(QPixmap(":/images/logo.png").scaled(110, 110, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logo->setAlignment(Qt::AlignCenter);
    QLabel *titre = new QLabel("Smart Fire Station");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("font-size: 20px; font-weight: bold; color: #1F4E79;");
    QLabel *sous = new QLabel("Connexion à votre compte");
    sous->setAlignment(Qt::AlignCenter);
    sous->setProperty("class", "pageSubtitle");

    QLineEdit *email = new QLineEdit();
    email->setPlaceholderText("Email");
    QLineEdit *mdp = new QLineEdit();
    mdp->setPlaceholderText("Mot de passe");
    mdp->setEchoMode(QLineEdit::Password);
    QLabel *erreur = new QLabel();
    erreur->setProperty("class", "textDanger");
    erreur->setAlignment(Qt::AlignCenter);

    QPushButton *btnConnexion = new QPushButton("Se connecter");
    btnConnexion->setProperty("class", "btnPrimary");
    btnConnexion->setDefault(true);
    QPushButton *btnOublie = new QPushButton("Mot de passe oublié ?");
    btnOublie->setFlat(true);
    btnOublie->setCursor(Qt::PointingHandCursor);
    btnOublie->setStyleSheet("QPushButton { background: transparent; border: none; color: #1F4E79; text-decoration: underline; }");
    QPushButton *btnAnnuler = new QPushButton("Quitter");
    btnAnnuler->setProperty("class", "btnDanger");

    lay->addWidget(logo);
    lay->addWidget(titre);
    lay->addWidget(sous);
    lay->addSpacing(8);
    lay->addWidget(email);
    lay->addWidget(mdp);
    lay->addWidget(erreur);
    lay->addWidget(btnConnexion);
    lay->addWidget(btnOublie);
    lay->addWidget(btnAnnuler);

    int tentatives = 0;
    connect(btnConnexion, &QPushButton::clicked, &dlg, [&]() {
        if (email->text().trimmed().isEmpty() || mdp->text().isEmpty()) {
            erreur->setText("Saisissez votre email et votre mot de passe.");
            return;
        }
        Personnel p;
        if (Personnel::authentifier(email->text(), mdp->text(), p)) {
            m_utilisateur = p;
            dlg.accept();
            return;
        }
        tentatives++;
        mdp->clear();
        if (tentatives >= 5) {
            QMessageBox::warning(&dlg, "Authentification", "Trop de tentatives échouées.");
            dlg.reject();
            return;
        }
        erreur->setText(QString("Email ou mot de passe incorrect (%1/5).").arg(tentatives));
    });
    connect(btnOublie, &QPushButton::clicked, &dlg, [&]() { motDePasseOublie(&dlg); });
    connect(btnAnnuler, &QPushButton::clicked, &dlg, &QDialog::reject);

    if (dlg.exec() != QDialog::Accepted)
        return false;

    return true;   // la fenêtre principale lit utilisateurConnecte() et affiche le rôle
}

// ------------------------------------------------------------------
//  Mot de passe oublié (métier avancé) : question secrète
// ------------------------------------------------------------------
void PersonnelPage::motDePasseOublie(QWidget *parent)
{
    QDialog dlg(parent);
    dlg.setWindowTitle("Mot de passe oublié");
    dlg.setFixedWidth(400);

    QVBoxLayout *lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 20, 24, 20);
    lay->setSpacing(8);
    QLineEdit *email = new QLineEdit();
    email->setPlaceholderText("Votre email");
    QPushButton *btnQuestion = new QPushButton("Afficher ma question secrète");
    btnQuestion->setProperty("class", "btnSecondary");
    QLabel *question = new QLabel();
    question->setWordWrap(true);
    question->setProperty("class", "textPrimaryBold");
    QLineEdit *reponse = new QLineEdit();
    reponse->setPlaceholderText("Votre réponse");
    QLineEdit *nouveau = new QLineEdit();
    nouveau->setPlaceholderText("Nouveau mot de passe");
    nouveau->setEchoMode(QLineEdit::Password);
    QLineEdit *confirmation = new QLineEdit();
    confirmation->setPlaceholderText("Confirmer le nouveau mot de passe");
    confirmation->setEchoMode(QLineEdit::Password);
    QPushButton *btnReinit = new QPushButton("Réinitialiser le mot de passe");
    btnReinit->setProperty("class", "btnPrimary");
    QLabel *message = new QLabel();
    message->setWordWrap(true);
    message->setProperty("class", "textDanger");

    reponse->setEnabled(false);
    nouveau->setEnabled(false);
    confirmation->setEnabled(false);
    btnReinit->setEnabled(false);

    lay->addWidget(new QLabel("Saisissez votre email pour retrouver votre question secrète."));
    lay->addWidget(email);
    lay->addWidget(btnQuestion);
    lay->addWidget(question);
    lay->addWidget(reponse);
    lay->addWidget(nouveau);
    lay->addWidget(confirmation);
    lay->addWidget(message);
    lay->addWidget(btnReinit);

    connect(btnQuestion, &QPushButton::clicked, &dlg, [&]() {
        QString q = Personnel::questionDe(email->text());
        if (q.isEmpty()) {
            message->setText("Aucun compte ne correspond à cet email.");
            return;
        }
        message->clear();
        question->setText(q);
        reponse->setEnabled(true);
        nouveau->setEnabled(true);
        confirmation->setEnabled(true);
        btnReinit->setEnabled(true);
    });
    connect(btnReinit, &QPushButton::clicked, &dlg, [&]() {
        if (reponse->text().trimmed().isEmpty()) {
            message->setText("Saisissez votre réponse secrète.");
            return;
        }
        if (!Personnel::motDePasseValide(nouveau->text())) {
            message->setText("Mot de passe : 6 caractères minimum, avec au moins une lettre et un chiffre.");
            return;
        }
        if (nouveau->text() != confirmation->text()) {
            message->setText("Les deux mots de passe sont différents.");
            return;
        }
        if (Personnel::reinitialiserMotDePasse(email->text(), reponse->text(), nouveau->text())) {
            QMessageBox::information(&dlg, "Mot de passe oublié",
                                     "Mot de passe réinitialisé. Vous pouvez vous connecter.");
            dlg.accept();
        } else {
            message->setText("Réponse incorrecte.");
        }
    });

    dlg.exec();
}

// ------------------------------------------------------------------
//  Contrôle de saisie : remplit un objet Personnel à partir du formulaire
// ------------------------------------------------------------------
bool PersonnelPage::lireFormulaire(Personnel &p, bool modification)
{
    QString erreur;
    if (!Personnel::nomValide(m_nom->text()))
        erreur = "Nom invalide (lettres uniquement).";
    else if (!Personnel::nomValide(m_prenom->text()))
        erreur = "Prénom invalide (lettres uniquement).";
    else if (!Personnel::telephoneValide(m_telephone->text()))
        erreur = "Le téléphone doit contenir exactement 8 chiffres.";
    else if (!Personnel::emailValide(m_email->text()))
        erreur = "L'adresse email n'est pas valide.";
    else if (!modification && !Personnel::motDePasseValide(m_motDePasse->text()))
        erreur = "Mot de passe : 6 caractères minimum, avec au moins une lettre et un chiffre.";
    else if (modification && !m_motDePasse->text().isEmpty() && !Personnel::motDePasseValide(m_motDePasse->text()))
        erreur = "Mot de passe : 6 caractères minimum, avec au moins une lettre et un chiffre.";
    else if (!modification && m_reponse->text().trimmed().length() < 2)
        erreur = "Réponse secrète obligatoire (2 caractères minimum).";

    if (!erreur.isEmpty()) {
        QMessageBox::warning(this, "Saisie incorrecte", erreur);
        return false;
    }

    QString tel = m_telephone->text();
    tel.remove(' ').remove('-');

    p.setNom(m_nom->text().trimmed());
    p.setPrenom(m_prenom->text().trimmed());
    p.setGrade(m_grade->currentText());
    p.setPoste(m_poste->currentText());
    p.setTelephone(tel);
    p.setEmail(m_email->text().trimmed());
    p.setMotDePasse(m_motDePasse->text());
    p.setQuestionSecrete(m_question->currentText());
    p.setReponseSecrete(m_reponse->text());
    p.setDisponibilite(m_disponibilite->currentText());
    return true;
}

// ------------------------------------------------------------------
//  CRUD : la vue appelle uniquement les méthodes de la classe Personnel
// ------------------------------------------------------------------

// Bouton "Ajouter" : le formulaire est vidé, puis "Enregistrer" crée le membre
void PersonnelPage::ajouterPersonnel()
{
    viderFormulaire();
    m_formulaire->setTitle("Ajouter un personnel — remplissez la fiche ci-dessous");
    m_nom->setFocus();
    showMessage("Remplissez le formulaire visible puis cliquez sur Enregistrer.", 5000);
}

// Bouton "Modifier" (ou double-clic) : on relit le membre en base et on remplit le formulaire
void PersonnelPage::modifierPersonnel()
{
    int id = idSelectionne();
    if (id == 0) {
        QMessageBox::information(this, "Modifier un personnel", "Sélectionnez d'abord un personnel dans la liste.");
        return;
    }
    Personnel p;
    if (!Personnel::trouver(id, p)) {
        QMessageBox::critical(this, "Base de données", "Impossible de lire ce membre du personnel.");
        return;
    }

    m_idEdition = id;
    m_labelId->setText(QString("P%1").arg(id, 3, 10, QChar('0')));
    m_nom->setText(p.nom());
    m_prenom->setText(p.prenom());
    m_telephone->setText(p.telephone());
    m_email->setText(p.email());
    m_grade->setCurrentText(p.grade());
    m_poste->setCurrentText(p.poste());
    m_question->setCurrentText(p.questionSecrete());
    m_disponibilite->setCurrentText(p.disponibilite());
    m_motDePasse->clear();
    m_motDePasse->setPlaceholderText("Laisser vide = inchangé");
    m_reponse->clear();
    m_reponse->setPlaceholderText("Laisser vide = inchangée");
    m_formulaire->setTitle(QString("Modifier P%1 — modifiez les champs puis enregistrez")
                               .arg(id, 3, 10, QChar('0')));
    m_nom->setFocus();
}

// Bouton "Enregistrer" : INSERT (nouveau membre) ou UPDATE (membre en modification)
void PersonnelPage::enregistrer()
{
    bool modification = (m_idEdition != 0);
    Personnel p;
    if (!lireFormulaire(p, modification))
        return;

    if (modification) {
        p.setId(m_idEdition);
        if (!p.modifier()) {
            QMessageBox::critical(this, "Base de données",
                                  "La modification a échoué (cet email est peut-être déjà utilisé).");
            return;
        }
        showMessage("Personnel modifié avec succès.", 4000);
    } else {
        if (!p.ajouter()) {
            QMessageBox::critical(this, "Base de données",
                                  "L'ajout a échoué (cet email est peut-être déjà utilisé).");
            return;
        }
        showMessage("Personnel ajouté avec succès.", 4000);
    }
    viderFormulaire();
    rafraichir();
}

void PersonnelPage::supprimerPersonnel()
{
    int id = idSelectionne();
    if (id == 0) {
        QMessageBox::information(this, "Supprimer un personnel", "Sélectionnez d'abord un personnel dans la liste.");
        return;
    }
    if (id == m_utilisateur.id()) {
        QMessageBox::warning(this, "Supprimer un personnel", "Vous ne pouvez pas supprimer le compte connecté.");
        return;
    }
    Personnel p;
    Personnel::trouver(id, p);
    if (QMessageBox::question(this, "Supprimer un personnel",
                              "Voulez-vous vraiment supprimer " + p.nomComplet() + " ?") != QMessageBox::Yes)
        return;
    if (!Personnel::supprimer(id)) {
        QMessageBox::critical(this, "Base de données", "La suppression a échoué.");
        return;
    }
    showMessage("Personnel supprimé.", 5000);
    viderFormulaire();
    rafraichir();
}

// Bouton "Effacer" : le formulaire revient à l'état "nouveau membre"
void PersonnelPage::viderFormulaire()
{
    m_idEdition = 0;
    m_labelId->setText("(automatique)");
    m_nom->clear();
    m_prenom->clear();
    m_telephone->clear();
    m_email->clear();
    m_motDePasse->clear();
    m_motDePasse->setPlaceholderText("6 caractères min.");
    m_reponse->clear();
    m_reponse->setPlaceholderText("Réponse");
    m_grade->setCurrentIndex(0);
    m_poste->setCurrentIndex(0);
    m_question->setCurrentIndex(0);
    m_disponibilite->setCurrentText("Disponible");
    m_formulaire->setTitle("Fiche du personnel — remplissez les champs puis validez");
    m_table->clearSelection();
}

// ------------------------------------------------------------------
//  Recherche, tri, affichage : exécutés par la classe Personnel (SQL)
// ------------------------------------------------------------------
void PersonnelPage::rechercher()
{
    rafraichir();
    QString texte = m_recherche->text().trimmed();
    if (texte.isEmpty())
        clearMessage();
    else
        showMessage(QString("%1 résultat(s)").arg(m_model->rowCount()), 4000);
}

void PersonnelPage::trier()
{
    m_tri = m_comboTri->currentIndex() + 1;   // 0 Grade -> 1, 1 Disponibilité -> 2, 2 Nom -> 3
    rafraichir();
    showMessage("Liste triée.", 4000);
}

void PersonnelPage::rafraichir()
{
    QSqlQueryModel *nouveau = Personnel::afficher(m_recherche->text(), m_tri);
    while (nouveau->canFetchMore())
        nouveau->fetchMore();
    m_table->setModel(nouveau);
    delete m_model;
    m_model = nouveau;

    // Colonnes : ID étroite, les autres se partagent la place
    QHeaderView *entete = m_table->horizontalHeader();
    entete->setSectionResizeMode(QHeaderView::Stretch);
    entete->setSectionResizeMode(0, QHeaderView::Fixed);
    entete->resizeSection(0, 70);

    mettreAJourStatistiques();
}

// ID du membre sélectionné dans le tableau (0 si aucune ligne n'est sélectionnée)
int PersonnelPage::idSelectionne() const
{
    QModelIndex ligne = m_table->currentIndex();
    if (!ligne.isValid() || !m_table->selectionModel()->isRowSelected(ligne.row(), QModelIndex()))
        return 0;
    return m_model->data(m_model->index(ligne.row(), 0), Qt::UserRole).toInt();
}

// Panneau "Statistiques" : diagramme par grade + total
void PersonnelPage::mettreAJourStatistiques()
{
    QList<int> valeurs = Personnel::statistiquesParGrade();
    int total = 0;
    for (int v : valeurs)
        total += v;
    m_graphique->setData(Personnel::grades(), valeurs);
    m_labelTotal->setText(QString("Total : %1 personnel(s)").arg(total));
}

// ------------------------------------------------------------------
//  Export PDF : les lignes affichées (donc le résultat d'une recherche / d'un tri)
// ------------------------------------------------------------------
void PersonnelPage::exporterPdf()
{
    const int colonnes = m_model->columnCount();
    const int lignes = m_model->rowCount();
    if (lignes == 0) {
        QMessageBox::information(this, "Export PDF", "Aucune donnée à exporter.");
        return;
    }

    QString dossier = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString chemin = QFileDialog::getSaveFileName(this, "Exporter en PDF",
                                                  dossier + "/personnel.pdf", "Fichiers PDF (*.pdf)");
    if (chemin.isEmpty())
        return;   // l'utilisateur a annulé
    if (!chemin.endsWith(".pdf"))
        chemin += ".pdf";

    // Le contenu du PDF est écrit en HTML (titre + tableau), puis "imprimé" dans le fichier
    QString html = "<h2 style='color:#1F4E79;'>Smart Fire Station Management</h2>"
                   "<h3>Liste du personnel</h3>"
                   "<p>Exporté le " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm") + "</p>"
                   "<table border='1' cellspacing='0' cellpadding='5' width='100%'><tr>";
    for (int c = 0; c < colonnes; c++)
        html += "<th bgcolor='#1F4E79' style='color:white;'>"
                + m_model->headerData(c, Qt::Horizontal).toString().toHtmlEscaped() + "</th>";
    html += "</tr>";
    for (int l = 0; l < lignes; l++) {
        html += "<tr>";
        for (int c = 0; c < colonnes; c++)
            html += "<td>" + m_model->data(m_model->index(l, c)).toString().toHtmlEscaped() + "</td>";
        html += "</tr>";
    }
    html += "</table>";

    QPdfWriter writer(chemin);
    QTextDocument document;
    document.setHtml(html);
    document.print(&writer);

    showMessage("PDF exporté : " + chemin, 6000);
    if (QMessageBox::question(this, "Export PDF",
                              "Le PDF a été créé.\nVoulez-vous l'ouvrir maintenant ?") == QMessageBox::Yes)
        QDesktopServices::openUrl(QUrl::fromLocalFile(chemin));
}

