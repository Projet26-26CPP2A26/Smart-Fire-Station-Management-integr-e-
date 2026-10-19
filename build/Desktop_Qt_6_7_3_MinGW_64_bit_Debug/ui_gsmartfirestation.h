/********************************************************************************
** Form generated from reading UI file 'gsmartfirestation.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSMARTFIRESTATION_H
#define UI_GSMARTFIRESTATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GSmartFireStation
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayoutMain;
    QFrame *sidebar;
    QVBoxLayout *verticalLayoutSidebar;
    QLabel *labelLogo;
    QSpacerItem *spacerSidebarTop;
    QPushButton *btnNavDashboard;
    QPushButton *btnNavPersonnel;
    QPushButton *btnNavVehicules;
    QSpacerItem *spacerSidebarBottom;
    QPushButton *btnQuitter;
    QSpacerItem *spacerSidebarRole;
    QLabel *labelRole;
    QStackedWidget *stackedWidget;
    QWidget *pageDashboard;
    QVBoxLayout *verticalLayoutDashboard;
    QLabel *labelDashTitle;
    QLabel *labelDashSubtitle;
    QFrame *lineDash;
    QHBoxLayout *horizontalLayoutCards;
    QFrame *cardPersonnel;
    QVBoxLayout *verticalLayoutcardPersonnel;
    QLabel *labelcardPersonnelTitle;
    QHBoxLayout *horizontalLayoutcardPersonnel;
    QLabel *labelNbPersonnel;
    QLabel *labelPersonnelDispoDetail;
    QSpacerItem *spacercardPersonnel;
    QFrame *cardVehicules;
    QVBoxLayout *verticalLayoutcardVehicules;
    QLabel *labelcardVehiculesTitle;
    QHBoxLayout *horizontalLayoutcardVehicules;
    QLabel *labelNbVehicules;
    QLabel *labelVehiculesDispoDetail;
    QSpacerItem *spacercardVehicules;
    QFrame *cardAlertes;
    QVBoxLayout *verticalLayoutcardAlertes;
    QLabel *labelcardAlertesTitle;
    QHBoxLayout *horizontalLayoutcardAlertes;
    QLabel *labelNbAlertes;
    QLabel *labelAlertesDetail;
    QSpacerItem *spacercardAlertes;
    QHBoxLayout *horizontalLayoutLower;
    QFrame *frameDisponibilite;
    QVBoxLayout *verticalLayoutDispo;
    QLabel *labelDispoTitle;
    QGridLayout *gridLayoutDispo;
    QLabel *labelDispoRow0;
    QProgressBar *progressPersonnelDispo;
    QLabel *labelPersonnelDispoCount;
    QLabel *labelDispoRow1;
    QProgressBar *progressPersonnelMission;
    QLabel *labelPersonnelMissionCount;
    QLabel *labelDispoRow2;
    QProgressBar *progressVehiculesDispo;
    QLabel *labelVehiculesDispoCount;
    QLabel *labelDispoRow3;
    QProgressBar *progressVehiculesMaint;
    QLabel *labelVehiculesMaintCount;
    QSpacerItem *spacerDispo;
    QFrame *frameAlertes;
    QVBoxLayout *verticalLayoutAlertes;
    QLabel *labelAlertesTitle;
    QListWidget *listAlertes;
    QHBoxLayout *horizontalLayoutQuick;
    QPushButton *btnGererPersonnel;
    QPushButton *btnGererVehicules;
    QPushButton *btnVoirStats;
    QSpacerItem *spacerDash;
    QWidget *pagePersonnel;
    QVBoxLayout *verticalLayoutPersonnel;
    QHBoxLayout *horizontalLayoutHeaderPersonnel;
    QLabel *labelPersonnelTitle;
    QSpacerItem *spacerHeaderPersonnel;
    QPushButton *btnRetourPersonnel;
    QLabel *labelPersonnelSubtitle;
    QFrame *linePersonnel;
    QFrame *frameToolbarPersonnel;
    QHBoxLayout *horizontalLayoutToolbarPersonnel;
    QLabel *labelRecherchePersonnel;
    QLineEdit *lineEditRecherchePersonnel;
    QLabel *labelTriPersonnel;
    QComboBox *comboTriPersonnel;
    QPushButton *btnRechercherPersonnel;
    QPushButton *btnTrierPersonnel;
    QPushButton *btnExportPersonnel;
    QPushButton *btnStatsPersonnel;
    QSpacerItem *spacerToolbarPersonnel;
    QHBoxLayout *horizontalLayoutPersonnelBody;
    QVBoxLayout *verticalLayoutPersonnelLeft;
    QHBoxLayout *horizontalLayoutCrudPersonnel;
    QPushButton *btnAjouterPersonnel;
    QPushButton *btnModifierPersonnel;
    QPushButton *btnSupprimerPersonnel;
    QSpacerItem *spacerCrudPersonnel;
    QTableWidget *tableWidgetPersonnel;
    QVBoxLayout *verticalLayoutPersonnelRight;
    QFrame *frameSurcharge;
    QVBoxLayout *verticalLayoutSurcharge;
    QLabel *labelSurchargeTitle;
    QHBoxLayout *horizontalLayoutSeuil;
    QLabel *labelSeuil;
    QSpinBox *spinSeuil;
    QSpacerItem *spacerSeuil;
    QLabel *labelSurchargeNom;
    QLabel *labelSurchargeCharge;
    QLabel *labelSurchargeEtat;
    QPushButton *btnDetailsSurcharge;
    QFrame *frameStatsPersonnel;
    QVBoxLayout *verticalLayoutStatsPersonnel;
    QLabel *labelStatsPersonnelTitle;
    QHBoxLayout *horizontalLayoutStatDispo;
    QLabel *labelStatDispo;
    QProgressBar *progressStatDispo;
    QHBoxLayout *horizontalLayoutStatMission;
    QLabel *labelStatMission;
    QProgressBar *progressStatMission;
    QLabel *labelTotalPersonnel;
    QSpacerItem *spacerPersonnelRight;
    QWidget *pageVehicules;
    QVBoxLayout *verticalLayoutVehicules;
    QHBoxLayout *horizontalLayoutHeaderVehicules;
    QLabel *labelVehiculesTitle;
    QSpacerItem *spacerHeaderVehicules;
    QPushButton *btnRetourVehicule;
    QLabel *labelVehiculesSubtitle;
    QFrame *lineVehicules;
    QFrame *frameToolbarVehicule;
    QHBoxLayout *horizontalLayoutToolbarVehicule;
    QLabel *labelRechercheVehicule;
    QLineEdit *lineEditRechercheVehicule;
    QLabel *labelTriVehicule;
    QComboBox *comboTriVehicule;
    QPushButton *btnRechercherVehicule;
    QPushButton *btnTrierVehicule;
    QPushButton *btnExportVehicule;
    QPushButton *btnStatsVehicule;
    QSpacerItem *spacerToolbarVehicule;
    QHBoxLayout *horizontalLayoutVehiculesBody;
    QVBoxLayout *verticalLayoutVehiculesLeft;
    QHBoxLayout *horizontalLayoutCrudVehicule;
    QPushButton *btnAjouterVehicule;
    QPushButton *btnModifierVehicule;
    QPushButton *btnSupprimerVehicule;
    QSpacerItem *spacerCrudVehicule;
    QTableWidget *tableWidgetVehicules;
    QVBoxLayout *verticalLayoutVehiculesRight;
    QFrame *frameMission;
    QVBoxLayout *verticalLayoutMission;
    QLabel *labelMissionTitle;
    QLabel *labelTypeIntervention;
    QComboBox *comboIntervention;
    QLabel *labelVehiculeProposeTxt;
    QLabel *labelVehiculePropose;
    QLabel *labelVehiculeInfo;
    QPushButton *btnUtiliserVehicule;
    QFrame *frameStatsVehicules;
    QVBoxLayout *verticalLayoutStatsVehicules;
    QLabel *labelStatsVehiculesTitle;
    QLabel *labelStatVehDispo;
    QProgressBar *progressStatVehDispo;
    QLabel *labelStatVehMaint;
    QSpacerItem *spacerVehiculesRight;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GSmartFireStation)
    {
        if (GSmartFireStation->objectName().isEmpty())
            GSmartFireStation->setObjectName("GSmartFireStation");
        GSmartFireStation->resize(1280, 780);
        GSmartFireStation->setMinimumSize(QSize(1180, 700));
        centralwidget = new QWidget(GSmartFireStation);
        centralwidget->setObjectName("centralwidget");
        horizontalLayoutMain = new QHBoxLayout(centralwidget);
        horizontalLayoutMain->setSpacing(0);
        horizontalLayoutMain->setObjectName("horizontalLayoutMain");
        horizontalLayoutMain->setContentsMargins(0, 0, 0, 0);
        sidebar = new QFrame(centralwidget);
        sidebar->setObjectName("sidebar");
        sidebar->setMinimumSize(QSize(220, 0));
        sidebar->setMaximumSize(QSize(220, 16777215));
        sidebar->setFrameShape(QFrame::NoFrame);
        verticalLayoutSidebar = new QVBoxLayout(sidebar);
        verticalLayoutSidebar->setSpacing(8);
        verticalLayoutSidebar->setObjectName("verticalLayoutSidebar");
        verticalLayoutSidebar->setContentsMargins(14, 22, 14, 20);
        labelLogo = new QLabel(sidebar);
        labelLogo->setObjectName("labelLogo");
        labelLogo->setAlignment(Qt::AlignCenter);

        verticalLayoutSidebar->addWidget(labelLogo);

        spacerSidebarTop = new QSpacerItem(20, 22, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayoutSidebar->addItem(spacerSidebarTop);

        btnNavDashboard = new QPushButton(sidebar);
        btnNavDashboard->setObjectName("btnNavDashboard");
        btnNavDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnNavDashboard->setCheckable(true);
        btnNavDashboard->setChecked(true);
        btnNavDashboard->setAutoExclusive(true);

        verticalLayoutSidebar->addWidget(btnNavDashboard);

        btnNavPersonnel = new QPushButton(sidebar);
        btnNavPersonnel->setObjectName("btnNavPersonnel");
        btnNavPersonnel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnNavPersonnel->setCheckable(true);
        btnNavPersonnel->setAutoExclusive(true);

        verticalLayoutSidebar->addWidget(btnNavPersonnel);

        btnNavVehicules = new QPushButton(sidebar);
        btnNavVehicules->setObjectName("btnNavVehicules");
        btnNavVehicules->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnNavVehicules->setCheckable(true);
        btnNavVehicules->setAutoExclusive(true);

        verticalLayoutSidebar->addWidget(btnNavVehicules);

        spacerSidebarBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutSidebar->addItem(spacerSidebarBottom);

        btnQuitter = new QPushButton(sidebar);
        btnQuitter->setObjectName("btnQuitter");
        btnQuitter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayoutSidebar->addWidget(btnQuitter);

        spacerSidebarRole = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayoutSidebar->addItem(spacerSidebarRole);

        labelRole = new QLabel(sidebar);
        labelRole->setObjectName("labelRole");
        labelRole->setWordWrap(true);

        verticalLayoutSidebar->addWidget(labelRole);


        horizontalLayoutMain->addWidget(sidebar);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        pageDashboard = new QWidget();
        pageDashboard->setObjectName("pageDashboard");
        verticalLayoutDashboard = new QVBoxLayout(pageDashboard);
        verticalLayoutDashboard->setSpacing(16);
        verticalLayoutDashboard->setObjectName("verticalLayoutDashboard");
        verticalLayoutDashboard->setContentsMargins(30, 26, 30, 20);
        labelDashTitle = new QLabel(pageDashboard);
        labelDashTitle->setObjectName("labelDashTitle");

        verticalLayoutDashboard->addWidget(labelDashTitle);

        labelDashSubtitle = new QLabel(pageDashboard);
        labelDashSubtitle->setObjectName("labelDashSubtitle");

        verticalLayoutDashboard->addWidget(labelDashSubtitle);

        lineDash = new QFrame(pageDashboard);
        lineDash->setObjectName("lineDash");
        lineDash->setFrameShape(QFrame::HLine);
        lineDash->setFrameShadow(QFrame::Plain);

        verticalLayoutDashboard->addWidget(lineDash);

        horizontalLayoutCards = new QHBoxLayout();
        horizontalLayoutCards->setSpacing(22);
        horizontalLayoutCards->setObjectName("horizontalLayoutCards");
        cardPersonnel = new QFrame(pageDashboard);
        cardPersonnel->setObjectName("cardPersonnel");
        cardPersonnel->setFrameShape(QFrame::StyledPanel);
        cardPersonnel->setFrameShadow(QFrame::Plain);
        cardPersonnel->setMinimumSize(QSize(0, 100));
        verticalLayoutcardPersonnel = new QVBoxLayout(cardPersonnel);
        verticalLayoutcardPersonnel->setSpacing(6);
        verticalLayoutcardPersonnel->setObjectName("verticalLayoutcardPersonnel");
        verticalLayoutcardPersonnel->setContentsMargins(20, 16, 20, 16);
        labelcardPersonnelTitle = new QLabel(cardPersonnel);
        labelcardPersonnelTitle->setObjectName("labelcardPersonnelTitle");

        verticalLayoutcardPersonnel->addWidget(labelcardPersonnelTitle);

        horizontalLayoutcardPersonnel = new QHBoxLayout();
        horizontalLayoutcardPersonnel->setSpacing(18);
        horizontalLayoutcardPersonnel->setObjectName("horizontalLayoutcardPersonnel");
        labelNbPersonnel = new QLabel(cardPersonnel);
        labelNbPersonnel->setObjectName("labelNbPersonnel");

        horizontalLayoutcardPersonnel->addWidget(labelNbPersonnel);

        labelPersonnelDispoDetail = new QLabel(cardPersonnel);
        labelPersonnelDispoDetail->setObjectName("labelPersonnelDispoDetail");

        horizontalLayoutcardPersonnel->addWidget(labelPersonnelDispoDetail);

        spacercardPersonnel = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutcardPersonnel->addItem(spacercardPersonnel);


        verticalLayoutcardPersonnel->addLayout(horizontalLayoutcardPersonnel);


        horizontalLayoutCards->addWidget(cardPersonnel);

        cardVehicules = new QFrame(pageDashboard);
        cardVehicules->setObjectName("cardVehicules");
        cardVehicules->setFrameShape(QFrame::StyledPanel);
        cardVehicules->setFrameShadow(QFrame::Plain);
        cardVehicules->setMinimumSize(QSize(0, 100));
        verticalLayoutcardVehicules = new QVBoxLayout(cardVehicules);
        verticalLayoutcardVehicules->setSpacing(6);
        verticalLayoutcardVehicules->setObjectName("verticalLayoutcardVehicules");
        verticalLayoutcardVehicules->setContentsMargins(20, 16, 20, 16);
        labelcardVehiculesTitle = new QLabel(cardVehicules);
        labelcardVehiculesTitle->setObjectName("labelcardVehiculesTitle");

        verticalLayoutcardVehicules->addWidget(labelcardVehiculesTitle);

        horizontalLayoutcardVehicules = new QHBoxLayout();
        horizontalLayoutcardVehicules->setSpacing(18);
        horizontalLayoutcardVehicules->setObjectName("horizontalLayoutcardVehicules");
        labelNbVehicules = new QLabel(cardVehicules);
        labelNbVehicules->setObjectName("labelNbVehicules");

        horizontalLayoutcardVehicules->addWidget(labelNbVehicules);

        labelVehiculesDispoDetail = new QLabel(cardVehicules);
        labelVehiculesDispoDetail->setObjectName("labelVehiculesDispoDetail");

        horizontalLayoutcardVehicules->addWidget(labelVehiculesDispoDetail);

        spacercardVehicules = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutcardVehicules->addItem(spacercardVehicules);


        verticalLayoutcardVehicules->addLayout(horizontalLayoutcardVehicules);


        horizontalLayoutCards->addWidget(cardVehicules);

        cardAlertes = new QFrame(pageDashboard);
        cardAlertes->setObjectName("cardAlertes");
        cardAlertes->setFrameShape(QFrame::StyledPanel);
        cardAlertes->setFrameShadow(QFrame::Plain);
        cardAlertes->setMinimumSize(QSize(0, 100));
        verticalLayoutcardAlertes = new QVBoxLayout(cardAlertes);
        verticalLayoutcardAlertes->setSpacing(6);
        verticalLayoutcardAlertes->setObjectName("verticalLayoutcardAlertes");
        verticalLayoutcardAlertes->setContentsMargins(20, 16, 20, 16);
        labelcardAlertesTitle = new QLabel(cardAlertes);
        labelcardAlertesTitle->setObjectName("labelcardAlertesTitle");

        verticalLayoutcardAlertes->addWidget(labelcardAlertesTitle);

        horizontalLayoutcardAlertes = new QHBoxLayout();
        horizontalLayoutcardAlertes->setSpacing(18);
        horizontalLayoutcardAlertes->setObjectName("horizontalLayoutcardAlertes");
        labelNbAlertes = new QLabel(cardAlertes);
        labelNbAlertes->setObjectName("labelNbAlertes");

        horizontalLayoutcardAlertes->addWidget(labelNbAlertes);

        labelAlertesDetail = new QLabel(cardAlertes);
        labelAlertesDetail->setObjectName("labelAlertesDetail");

        horizontalLayoutcardAlertes->addWidget(labelAlertesDetail);

        spacercardAlertes = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutcardAlertes->addItem(spacercardAlertes);


        verticalLayoutcardAlertes->addLayout(horizontalLayoutcardAlertes);


        horizontalLayoutCards->addWidget(cardAlertes);


        verticalLayoutDashboard->addLayout(horizontalLayoutCards);

        horizontalLayoutLower = new QHBoxLayout();
        horizontalLayoutLower->setSpacing(22);
        horizontalLayoutLower->setObjectName("horizontalLayoutLower");
        frameDisponibilite = new QFrame(pageDashboard);
        frameDisponibilite->setObjectName("frameDisponibilite");
        frameDisponibilite->setFrameShape(QFrame::StyledPanel);
        frameDisponibilite->setFrameShadow(QFrame::Plain);
        verticalLayoutDispo = new QVBoxLayout(frameDisponibilite);
        verticalLayoutDispo->setSpacing(16);
        verticalLayoutDispo->setObjectName("verticalLayoutDispo");
        verticalLayoutDispo->setContentsMargins(20, 18, 20, 18);
        labelDispoTitle = new QLabel(frameDisponibilite);
        labelDispoTitle->setObjectName("labelDispoTitle");

        verticalLayoutDispo->addWidget(labelDispoTitle);

        gridLayoutDispo = new QGridLayout();
        gridLayoutDispo->setSpacing(18);
        gridLayoutDispo->setObjectName("gridLayoutDispo");
        labelDispoRow0 = new QLabel(frameDisponibilite);
        labelDispoRow0->setObjectName("labelDispoRow0");

        gridLayoutDispo->addWidget(labelDispoRow0, 0, 0, 1, 1);

        progressPersonnelDispo = new QProgressBar(frameDisponibilite);
        progressPersonnelDispo->setObjectName("progressPersonnelDispo");
        progressPersonnelDispo->setMaximum(100);
        progressPersonnelDispo->setValue(0);
        progressPersonnelDispo->setTextVisible(false);

        gridLayoutDispo->addWidget(progressPersonnelDispo, 0, 1, 1, 1);

        labelPersonnelDispoCount = new QLabel(frameDisponibilite);
        labelPersonnelDispoCount->setObjectName("labelPersonnelDispoCount");

        gridLayoutDispo->addWidget(labelPersonnelDispoCount, 0, 2, 1, 1);

        labelDispoRow1 = new QLabel(frameDisponibilite);
        labelDispoRow1->setObjectName("labelDispoRow1");

        gridLayoutDispo->addWidget(labelDispoRow1, 1, 0, 1, 1);

        progressPersonnelMission = new QProgressBar(frameDisponibilite);
        progressPersonnelMission->setObjectName("progressPersonnelMission");
        progressPersonnelMission->setMaximum(100);
        progressPersonnelMission->setValue(0);
        progressPersonnelMission->setTextVisible(false);

        gridLayoutDispo->addWidget(progressPersonnelMission, 1, 1, 1, 1);

        labelPersonnelMissionCount = new QLabel(frameDisponibilite);
        labelPersonnelMissionCount->setObjectName("labelPersonnelMissionCount");

        gridLayoutDispo->addWidget(labelPersonnelMissionCount, 1, 2, 1, 1);

        labelDispoRow2 = new QLabel(frameDisponibilite);
        labelDispoRow2->setObjectName("labelDispoRow2");

        gridLayoutDispo->addWidget(labelDispoRow2, 2, 0, 1, 1);

        progressVehiculesDispo = new QProgressBar(frameDisponibilite);
        progressVehiculesDispo->setObjectName("progressVehiculesDispo");
        progressVehiculesDispo->setMaximum(100);
        progressVehiculesDispo->setValue(0);
        progressVehiculesDispo->setTextVisible(false);

        gridLayoutDispo->addWidget(progressVehiculesDispo, 2, 1, 1, 1);

        labelVehiculesDispoCount = new QLabel(frameDisponibilite);
        labelVehiculesDispoCount->setObjectName("labelVehiculesDispoCount");

        gridLayoutDispo->addWidget(labelVehiculesDispoCount, 2, 2, 1, 1);

        labelDispoRow3 = new QLabel(frameDisponibilite);
        labelDispoRow3->setObjectName("labelDispoRow3");

        gridLayoutDispo->addWidget(labelDispoRow3, 3, 0, 1, 1);

        progressVehiculesMaint = new QProgressBar(frameDisponibilite);
        progressVehiculesMaint->setObjectName("progressVehiculesMaint");
        progressVehiculesMaint->setMaximum(100);
        progressVehiculesMaint->setValue(0);
        progressVehiculesMaint->setTextVisible(false);

        gridLayoutDispo->addWidget(progressVehiculesMaint, 3, 1, 1, 1);

        labelVehiculesMaintCount = new QLabel(frameDisponibilite);
        labelVehiculesMaintCount->setObjectName("labelVehiculesMaintCount");

        gridLayoutDispo->addWidget(labelVehiculesMaintCount, 3, 2, 1, 1);


        verticalLayoutDispo->addLayout(gridLayoutDispo);

        spacerDispo = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutDispo->addItem(spacerDispo);


        horizontalLayoutLower->addWidget(frameDisponibilite);

        frameAlertes = new QFrame(pageDashboard);
        frameAlertes->setObjectName("frameAlertes");
        frameAlertes->setFrameShape(QFrame::StyledPanel);
        frameAlertes->setFrameShadow(QFrame::Plain);
        verticalLayoutAlertes = new QVBoxLayout(frameAlertes);
        verticalLayoutAlertes->setSpacing(14);
        verticalLayoutAlertes->setObjectName("verticalLayoutAlertes");
        verticalLayoutAlertes->setContentsMargins(20, 18, 20, 18);
        labelAlertesTitle = new QLabel(frameAlertes);
        labelAlertesTitle->setObjectName("labelAlertesTitle");

        verticalLayoutAlertes->addWidget(labelAlertesTitle);

        listAlertes = new QListWidget(frameAlertes);
        listAlertes->setObjectName("listAlertes");
        listAlertes->setFrameShape(QFrame::NoFrame);
        listAlertes->setSelectionMode(QAbstractItemView::NoSelection);
        listAlertes->setFocusPolicy(Qt::NoFocus);

        verticalLayoutAlertes->addWidget(listAlertes);

        horizontalLayoutQuick = new QHBoxLayout();
        horizontalLayoutQuick->setSpacing(10);
        horizontalLayoutQuick->setObjectName("horizontalLayoutQuick");
        btnGererPersonnel = new QPushButton(frameAlertes);
        btnGererPersonnel->setObjectName("btnGererPersonnel");
        btnGererPersonnel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutQuick->addWidget(btnGererPersonnel);

        btnGererVehicules = new QPushButton(frameAlertes);
        btnGererVehicules->setObjectName("btnGererVehicules");
        btnGererVehicules->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutQuick->addWidget(btnGererVehicules);

        btnVoirStats = new QPushButton(frameAlertes);
        btnVoirStats->setObjectName("btnVoirStats");
        btnVoirStats->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutQuick->addWidget(btnVoirStats);


        verticalLayoutAlertes->addLayout(horizontalLayoutQuick);


        horizontalLayoutLower->addWidget(frameAlertes);

        horizontalLayoutLower->setStretch(0, 1);
        horizontalLayoutLower->setStretch(1, 1);

        verticalLayoutDashboard->addLayout(horizontalLayoutLower);

        spacerDash = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutDashboard->addItem(spacerDash);

        stackedWidget->addWidget(pageDashboard);
        pagePersonnel = new QWidget();
        pagePersonnel->setObjectName("pagePersonnel");
        verticalLayoutPersonnel = new QVBoxLayout(pagePersonnel);
        verticalLayoutPersonnel->setSpacing(14);
        verticalLayoutPersonnel->setObjectName("verticalLayoutPersonnel");
        verticalLayoutPersonnel->setContentsMargins(30, 26, 30, 20);
        horizontalLayoutHeaderPersonnel = new QHBoxLayout();
        horizontalLayoutHeaderPersonnel->setObjectName("horizontalLayoutHeaderPersonnel");
        labelPersonnelTitle = new QLabel(pagePersonnel);
        labelPersonnelTitle->setObjectName("labelPersonnelTitle");

        horizontalLayoutHeaderPersonnel->addWidget(labelPersonnelTitle);

        spacerHeaderPersonnel = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutHeaderPersonnel->addItem(spacerHeaderPersonnel);

        btnRetourPersonnel = new QPushButton(pagePersonnel);
        btnRetourPersonnel->setObjectName("btnRetourPersonnel");
        btnRetourPersonnel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutHeaderPersonnel->addWidget(btnRetourPersonnel);


        verticalLayoutPersonnel->addLayout(horizontalLayoutHeaderPersonnel);

        labelPersonnelSubtitle = new QLabel(pagePersonnel);
        labelPersonnelSubtitle->setObjectName("labelPersonnelSubtitle");

        verticalLayoutPersonnel->addWidget(labelPersonnelSubtitle);

        linePersonnel = new QFrame(pagePersonnel);
        linePersonnel->setObjectName("linePersonnel");
        linePersonnel->setFrameShape(QFrame::HLine);
        linePersonnel->setFrameShadow(QFrame::Plain);

        verticalLayoutPersonnel->addWidget(linePersonnel);

        frameToolbarPersonnel = new QFrame(pagePersonnel);
        frameToolbarPersonnel->setObjectName("frameToolbarPersonnel");
        frameToolbarPersonnel->setFrameShape(QFrame::StyledPanel);
        frameToolbarPersonnel->setFrameShadow(QFrame::Plain);
        horizontalLayoutToolbarPersonnel = new QHBoxLayout(frameToolbarPersonnel);
        horizontalLayoutToolbarPersonnel->setSpacing(12);
        horizontalLayoutToolbarPersonnel->setObjectName("horizontalLayoutToolbarPersonnel");
        horizontalLayoutToolbarPersonnel->setContentsMargins(18, 12, 18, 12);
        labelRecherchePersonnel = new QLabel(frameToolbarPersonnel);
        labelRecherchePersonnel->setObjectName("labelRecherchePersonnel");

        horizontalLayoutToolbarPersonnel->addWidget(labelRecherchePersonnel);

        lineEditRecherchePersonnel = new QLineEdit(frameToolbarPersonnel);
        lineEditRecherchePersonnel->setObjectName("lineEditRecherchePersonnel");
        lineEditRecherchePersonnel->setClearButtonEnabled(true);
        lineEditRecherchePersonnel->setMinimumSize(QSize(220, 0));

        horizontalLayoutToolbarPersonnel->addWidget(lineEditRecherchePersonnel);

        labelTriPersonnel = new QLabel(frameToolbarPersonnel);
        labelTriPersonnel->setObjectName("labelTriPersonnel");

        horizontalLayoutToolbarPersonnel->addWidget(labelTriPersonnel);

        comboTriPersonnel = new QComboBox(frameToolbarPersonnel);
        comboTriPersonnel->addItem(QString());
        comboTriPersonnel->addItem(QString());
        comboTriPersonnel->addItem(QString());
        comboTriPersonnel->setObjectName("comboTriPersonnel");
        comboTriPersonnel->setMinimumSize(QSize(150, 0));

        horizontalLayoutToolbarPersonnel->addWidget(comboTriPersonnel);

        btnRechercherPersonnel = new QPushButton(frameToolbarPersonnel);
        btnRechercherPersonnel->setObjectName("btnRechercherPersonnel");
        btnRechercherPersonnel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutToolbarPersonnel->addWidget(btnRechercherPersonnel);

        btnTrierPersonnel = new QPushButton(frameToolbarPersonnel);
        btnTrierPersonnel->setObjectName("btnTrierPersonnel");
        btnTrierPersonnel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutToolbarPersonnel->addWidget(btnTrierPersonnel);

        btnExportPersonnel = new QPushButton(frameToolbarPersonnel);
        btnExportPersonnel->setObjectName("btnExportPersonnel");
        btnExportPersonnel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutToolbarPersonnel->addWidget(btnExportPersonnel);

        btnStatsPersonnel = new QPushButton(frameToolbarPersonnel);
        btnStatsPersonnel->setObjectName("btnStatsPersonnel");
        btnStatsPersonnel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutToolbarPersonnel->addWidget(btnStatsPersonnel);

        spacerToolbarPersonnel = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutToolbarPersonnel->addItem(spacerToolbarPersonnel);


        verticalLayoutPersonnel->addWidget(frameToolbarPersonnel);

        horizontalLayoutPersonnelBody = new QHBoxLayout();
        horizontalLayoutPersonnelBody->setSpacing(18);
        horizontalLayoutPersonnelBody->setObjectName("horizontalLayoutPersonnelBody");
        verticalLayoutPersonnelLeft = new QVBoxLayout();
        verticalLayoutPersonnelLeft->setSpacing(14);
        verticalLayoutPersonnelLeft->setObjectName("verticalLayoutPersonnelLeft");
        horizontalLayoutCrudPersonnel = new QHBoxLayout();
        horizontalLayoutCrudPersonnel->setSpacing(12);
        horizontalLayoutCrudPersonnel->setObjectName("horizontalLayoutCrudPersonnel");
        btnAjouterPersonnel = new QPushButton(pagePersonnel);
        btnAjouterPersonnel->setObjectName("btnAjouterPersonnel");
        btnAjouterPersonnel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutCrudPersonnel->addWidget(btnAjouterPersonnel);

        btnModifierPersonnel = new QPushButton(pagePersonnel);
        btnModifierPersonnel->setObjectName("btnModifierPersonnel");
        btnModifierPersonnel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutCrudPersonnel->addWidget(btnModifierPersonnel);

        btnSupprimerPersonnel = new QPushButton(pagePersonnel);
        btnSupprimerPersonnel->setObjectName("btnSupprimerPersonnel");
        btnSupprimerPersonnel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutCrudPersonnel->addWidget(btnSupprimerPersonnel);

        spacerCrudPersonnel = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutCrudPersonnel->addItem(spacerCrudPersonnel);


        verticalLayoutPersonnelLeft->addLayout(horizontalLayoutCrudPersonnel);

        tableWidgetPersonnel = new QTableWidget(pagePersonnel);
        if (tableWidgetPersonnel->columnCount() < 7)
            tableWidgetPersonnel->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetPersonnel->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetPersonnel->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetPersonnel->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetPersonnel->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetPersonnel->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetPersonnel->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetPersonnel->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidgetPersonnel->setObjectName("tableWidgetPersonnel");
        tableWidgetPersonnel->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetPersonnel->setAlternatingRowColors(true);
        tableWidgetPersonnel->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPersonnel->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetPersonnel->setShowGrid(false);
        tableWidgetPersonnel->setColumnCount(7);
        tableWidgetPersonnel->horizontalHeader()->setHighlightSections(false);
        tableWidgetPersonnel->horizontalHeader()->setStretchLastSection(true);
        tableWidgetPersonnel->verticalHeader()->setVisible(false);

        verticalLayoutPersonnelLeft->addWidget(tableWidgetPersonnel);


        horizontalLayoutPersonnelBody->addLayout(verticalLayoutPersonnelLeft);

        verticalLayoutPersonnelRight = new QVBoxLayout();
        verticalLayoutPersonnelRight->setSpacing(16);
        verticalLayoutPersonnelRight->setObjectName("verticalLayoutPersonnelRight");
        frameSurcharge = new QFrame(pagePersonnel);
        frameSurcharge->setObjectName("frameSurcharge");
        frameSurcharge->setFrameShape(QFrame::StyledPanel);
        frameSurcharge->setFrameShadow(QFrame::Plain);
        frameSurcharge->setMinimumSize(QSize(300, 0));
        frameSurcharge->setMaximumSize(QSize(340, 16777215));
        verticalLayoutSurcharge = new QVBoxLayout(frameSurcharge);
        verticalLayoutSurcharge->setSpacing(10);
        verticalLayoutSurcharge->setObjectName("verticalLayoutSurcharge");
        verticalLayoutSurcharge->setContentsMargins(20, 18, 20, 18);
        labelSurchargeTitle = new QLabel(frameSurcharge);
        labelSurchargeTitle->setObjectName("labelSurchargeTitle");

        verticalLayoutSurcharge->addWidget(labelSurchargeTitle);

        horizontalLayoutSeuil = new QHBoxLayout();
        horizontalLayoutSeuil->setSpacing(12);
        horizontalLayoutSeuil->setObjectName("horizontalLayoutSeuil");
        labelSeuil = new QLabel(frameSurcharge);
        labelSeuil->setObjectName("labelSeuil");

        horizontalLayoutSeuil->addWidget(labelSeuil);

        spinSeuil = new QSpinBox(frameSurcharge);
        spinSeuil->setObjectName("spinSeuil");
        spinSeuil->setMinimum(10);
        spinSeuil->setMaximum(100);
        spinSeuil->setSingleStep(5);
        spinSeuil->setValue(80);

        horizontalLayoutSeuil->addWidget(spinSeuil);

        spacerSeuil = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutSeuil->addItem(spacerSeuil);


        verticalLayoutSurcharge->addLayout(horizontalLayoutSeuil);

        labelSurchargeNom = new QLabel(frameSurcharge);
        labelSurchargeNom->setObjectName("labelSurchargeNom");

        verticalLayoutSurcharge->addWidget(labelSurchargeNom);

        labelSurchargeCharge = new QLabel(frameSurcharge);
        labelSurchargeCharge->setObjectName("labelSurchargeCharge");

        verticalLayoutSurcharge->addWidget(labelSurchargeCharge);

        labelSurchargeEtat = new QLabel(frameSurcharge);
        labelSurchargeEtat->setObjectName("labelSurchargeEtat");

        verticalLayoutSurcharge->addWidget(labelSurchargeEtat);

        btnDetailsSurcharge = new QPushButton(frameSurcharge);
        btnDetailsSurcharge->setObjectName("btnDetailsSurcharge");
        btnDetailsSurcharge->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayoutSurcharge->addWidget(btnDetailsSurcharge);


        verticalLayoutPersonnelRight->addWidget(frameSurcharge);

        frameStatsPersonnel = new QFrame(pagePersonnel);
        frameStatsPersonnel->setObjectName("frameStatsPersonnel");
        frameStatsPersonnel->setFrameShape(QFrame::StyledPanel);
        frameStatsPersonnel->setFrameShadow(QFrame::Plain);
        frameStatsPersonnel->setMinimumSize(QSize(300, 0));
        frameStatsPersonnel->setMaximumSize(QSize(340, 16777215));
        verticalLayoutStatsPersonnel = new QVBoxLayout(frameStatsPersonnel);
        verticalLayoutStatsPersonnel->setSpacing(14);
        verticalLayoutStatsPersonnel->setObjectName("verticalLayoutStatsPersonnel");
        verticalLayoutStatsPersonnel->setContentsMargins(20, 18, 20, 18);
        labelStatsPersonnelTitle = new QLabel(frameStatsPersonnel);
        labelStatsPersonnelTitle->setObjectName("labelStatsPersonnelTitle");

        verticalLayoutStatsPersonnel->addWidget(labelStatsPersonnelTitle);

        horizontalLayoutStatDispo = new QHBoxLayout();
        horizontalLayoutStatDispo->setSpacing(14);
        horizontalLayoutStatDispo->setObjectName("horizontalLayoutStatDispo");
        labelStatDispo = new QLabel(frameStatsPersonnel);
        labelStatDispo->setObjectName("labelStatDispo");
        labelStatDispo->setMinimumSize(QSize(90, 0));
        labelStatDispo->setMaximumSize(QSize(90, 16777215));

        horizontalLayoutStatDispo->addWidget(labelStatDispo);

        progressStatDispo = new QProgressBar(frameStatsPersonnel);
        progressStatDispo->setObjectName("progressStatDispo");
        progressStatDispo->setMaximum(100);
        progressStatDispo->setValue(0);
        progressStatDispo->setTextVisible(false);

        horizontalLayoutStatDispo->addWidget(progressStatDispo);


        verticalLayoutStatsPersonnel->addLayout(horizontalLayoutStatDispo);

        horizontalLayoutStatMission = new QHBoxLayout();
        horizontalLayoutStatMission->setSpacing(14);
        horizontalLayoutStatMission->setObjectName("horizontalLayoutStatMission");
        labelStatMission = new QLabel(frameStatsPersonnel);
        labelStatMission->setObjectName("labelStatMission");
        labelStatMission->setMinimumSize(QSize(90, 0));
        labelStatMission->setMaximumSize(QSize(90, 16777215));

        horizontalLayoutStatMission->addWidget(labelStatMission);

        progressStatMission = new QProgressBar(frameStatsPersonnel);
        progressStatMission->setObjectName("progressStatMission");
        progressStatMission->setMaximum(100);
        progressStatMission->setValue(0);
        progressStatMission->setTextVisible(false);

        horizontalLayoutStatMission->addWidget(progressStatMission);


        verticalLayoutStatsPersonnel->addLayout(horizontalLayoutStatMission);

        labelTotalPersonnel = new QLabel(frameStatsPersonnel);
        labelTotalPersonnel->setObjectName("labelTotalPersonnel");

        verticalLayoutStatsPersonnel->addWidget(labelTotalPersonnel);


        verticalLayoutPersonnelRight->addWidget(frameStatsPersonnel);

        spacerPersonnelRight = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutPersonnelRight->addItem(spacerPersonnelRight);


        horizontalLayoutPersonnelBody->addLayout(verticalLayoutPersonnelRight);

        horizontalLayoutPersonnelBody->setStretch(0, 1);

        verticalLayoutPersonnel->addLayout(horizontalLayoutPersonnelBody);

        stackedWidget->addWidget(pagePersonnel);
        pageVehicules = new QWidget();
        pageVehicules->setObjectName("pageVehicules");
        verticalLayoutVehicules = new QVBoxLayout(pageVehicules);
        verticalLayoutVehicules->setSpacing(14);
        verticalLayoutVehicules->setObjectName("verticalLayoutVehicules");
        verticalLayoutVehicules->setContentsMargins(30, 26, 30, 20);
        horizontalLayoutHeaderVehicules = new QHBoxLayout();
        horizontalLayoutHeaderVehicules->setObjectName("horizontalLayoutHeaderVehicules");
        labelVehiculesTitle = new QLabel(pageVehicules);
        labelVehiculesTitle->setObjectName("labelVehiculesTitle");

        horizontalLayoutHeaderVehicules->addWidget(labelVehiculesTitle);

        spacerHeaderVehicules = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutHeaderVehicules->addItem(spacerHeaderVehicules);

        btnRetourVehicule = new QPushButton(pageVehicules);
        btnRetourVehicule->setObjectName("btnRetourVehicule");
        btnRetourVehicule->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutHeaderVehicules->addWidget(btnRetourVehicule);


        verticalLayoutVehicules->addLayout(horizontalLayoutHeaderVehicules);

        labelVehiculesSubtitle = new QLabel(pageVehicules);
        labelVehiculesSubtitle->setObjectName("labelVehiculesSubtitle");

        verticalLayoutVehicules->addWidget(labelVehiculesSubtitle);

        lineVehicules = new QFrame(pageVehicules);
        lineVehicules->setObjectName("lineVehicules");
        lineVehicules->setFrameShape(QFrame::HLine);
        lineVehicules->setFrameShadow(QFrame::Plain);

        verticalLayoutVehicules->addWidget(lineVehicules);

        frameToolbarVehicule = new QFrame(pageVehicules);
        frameToolbarVehicule->setObjectName("frameToolbarVehicule");
        frameToolbarVehicule->setFrameShape(QFrame::StyledPanel);
        frameToolbarVehicule->setFrameShadow(QFrame::Plain);
        horizontalLayoutToolbarVehicule = new QHBoxLayout(frameToolbarVehicule);
        horizontalLayoutToolbarVehicule->setSpacing(12);
        horizontalLayoutToolbarVehicule->setObjectName("horizontalLayoutToolbarVehicule");
        horizontalLayoutToolbarVehicule->setContentsMargins(18, 12, 18, 12);
        labelRechercheVehicule = new QLabel(frameToolbarVehicule);
        labelRechercheVehicule->setObjectName("labelRechercheVehicule");

        horizontalLayoutToolbarVehicule->addWidget(labelRechercheVehicule);

        lineEditRechercheVehicule = new QLineEdit(frameToolbarVehicule);
        lineEditRechercheVehicule->setObjectName("lineEditRechercheVehicule");
        lineEditRechercheVehicule->setClearButtonEnabled(true);
        lineEditRechercheVehicule->setMinimumSize(QSize(220, 0));

        horizontalLayoutToolbarVehicule->addWidget(lineEditRechercheVehicule);

        labelTriVehicule = new QLabel(frameToolbarVehicule);
        labelTriVehicule->setObjectName("labelTriVehicule");

        horizontalLayoutToolbarVehicule->addWidget(labelTriVehicule);

        comboTriVehicule = new QComboBox(frameToolbarVehicule);
        comboTriVehicule->addItem(QString());
        comboTriVehicule->addItem(QString());
        comboTriVehicule->setObjectName("comboTriVehicule");
        comboTriVehicule->setMinimumSize(QSize(150, 0));

        horizontalLayoutToolbarVehicule->addWidget(comboTriVehicule);

        btnRechercherVehicule = new QPushButton(frameToolbarVehicule);
        btnRechercherVehicule->setObjectName("btnRechercherVehicule");
        btnRechercherVehicule->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutToolbarVehicule->addWidget(btnRechercherVehicule);

        btnTrierVehicule = new QPushButton(frameToolbarVehicule);
        btnTrierVehicule->setObjectName("btnTrierVehicule");
        btnTrierVehicule->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutToolbarVehicule->addWidget(btnTrierVehicule);

        btnExportVehicule = new QPushButton(frameToolbarVehicule);
        btnExportVehicule->setObjectName("btnExportVehicule");
        btnExportVehicule->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutToolbarVehicule->addWidget(btnExportVehicule);

        btnStatsVehicule = new QPushButton(frameToolbarVehicule);
        btnStatsVehicule->setObjectName("btnStatsVehicule");
        btnStatsVehicule->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutToolbarVehicule->addWidget(btnStatsVehicule);

        spacerToolbarVehicule = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutToolbarVehicule->addItem(spacerToolbarVehicule);


        verticalLayoutVehicules->addWidget(frameToolbarVehicule);

        horizontalLayoutVehiculesBody = new QHBoxLayout();
        horizontalLayoutVehiculesBody->setSpacing(18);
        horizontalLayoutVehiculesBody->setObjectName("horizontalLayoutVehiculesBody");
        verticalLayoutVehiculesLeft = new QVBoxLayout();
        verticalLayoutVehiculesLeft->setSpacing(14);
        verticalLayoutVehiculesLeft->setObjectName("verticalLayoutVehiculesLeft");
        horizontalLayoutCrudVehicule = new QHBoxLayout();
        horizontalLayoutCrudVehicule->setSpacing(12);
        horizontalLayoutCrudVehicule->setObjectName("horizontalLayoutCrudVehicule");
        btnAjouterVehicule = new QPushButton(pageVehicules);
        btnAjouterVehicule->setObjectName("btnAjouterVehicule");
        btnAjouterVehicule->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutCrudVehicule->addWidget(btnAjouterVehicule);

        btnModifierVehicule = new QPushButton(pageVehicules);
        btnModifierVehicule->setObjectName("btnModifierVehicule");
        btnModifierVehicule->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutCrudVehicule->addWidget(btnModifierVehicule);

        btnSupprimerVehicule = new QPushButton(pageVehicules);
        btnSupprimerVehicule->setObjectName("btnSupprimerVehicule");
        btnSupprimerVehicule->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayoutCrudVehicule->addWidget(btnSupprimerVehicule);

        spacerCrudVehicule = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutCrudVehicule->addItem(spacerCrudVehicule);


        verticalLayoutVehiculesLeft->addLayout(horizontalLayoutCrudVehicule);

        tableWidgetVehicules = new QTableWidget(pageVehicules);
        if (tableWidgetVehicules->columnCount() < 7)
            tableWidgetVehicules->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetVehicules->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetVehicules->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetVehicules->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetVehicules->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetVehicules->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetVehicules->setHorizontalHeaderItem(5, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetVehicules->setHorizontalHeaderItem(6, __qtablewidgetitem13);
        tableWidgetVehicules->setObjectName("tableWidgetVehicules");
        tableWidgetVehicules->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetVehicules->setAlternatingRowColors(true);
        tableWidgetVehicules->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetVehicules->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetVehicules->setShowGrid(false);
        tableWidgetVehicules->setColumnCount(7);
        tableWidgetVehicules->horizontalHeader()->setHighlightSections(false);
        tableWidgetVehicules->horizontalHeader()->setStretchLastSection(true);
        tableWidgetVehicules->verticalHeader()->setVisible(false);

        verticalLayoutVehiculesLeft->addWidget(tableWidgetVehicules);


        horizontalLayoutVehiculesBody->addLayout(verticalLayoutVehiculesLeft);

        verticalLayoutVehiculesRight = new QVBoxLayout();
        verticalLayoutVehiculesRight->setSpacing(16);
        verticalLayoutVehiculesRight->setObjectName("verticalLayoutVehiculesRight");
        frameMission = new QFrame(pageVehicules);
        frameMission->setObjectName("frameMission");
        frameMission->setFrameShape(QFrame::StyledPanel);
        frameMission->setFrameShadow(QFrame::Plain);
        frameMission->setMinimumSize(QSize(300, 0));
        frameMission->setMaximumSize(QSize(340, 16777215));
        verticalLayoutMission = new QVBoxLayout(frameMission);
        verticalLayoutMission->setSpacing(10);
        verticalLayoutMission->setObjectName("verticalLayoutMission");
        verticalLayoutMission->setContentsMargins(20, 18, 20, 18);
        labelMissionTitle = new QLabel(frameMission);
        labelMissionTitle->setObjectName("labelMissionTitle");

        verticalLayoutMission->addWidget(labelMissionTitle);

        labelTypeIntervention = new QLabel(frameMission);
        labelTypeIntervention->setObjectName("labelTypeIntervention");

        verticalLayoutMission->addWidget(labelTypeIntervention);

        comboIntervention = new QComboBox(frameMission);
        comboIntervention->addItem(QString());
        comboIntervention->addItem(QString());
        comboIntervention->addItem(QString());
        comboIntervention->addItem(QString());
        comboIntervention->setObjectName("comboIntervention");
        comboIntervention->setMinimumSize(QSize(150, 0));

        verticalLayoutMission->addWidget(comboIntervention);

        labelVehiculeProposeTxt = new QLabel(frameMission);
        labelVehiculeProposeTxt->setObjectName("labelVehiculeProposeTxt");

        verticalLayoutMission->addWidget(labelVehiculeProposeTxt);

        labelVehiculePropose = new QLabel(frameMission);
        labelVehiculePropose->setObjectName("labelVehiculePropose");

        verticalLayoutMission->addWidget(labelVehiculePropose);

        labelVehiculeInfo = new QLabel(frameMission);
        labelVehiculeInfo->setObjectName("labelVehiculeInfo");

        verticalLayoutMission->addWidget(labelVehiculeInfo);

        btnUtiliserVehicule = new QPushButton(frameMission);
        btnUtiliserVehicule->setObjectName("btnUtiliserVehicule");
        btnUtiliserVehicule->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayoutMission->addWidget(btnUtiliserVehicule);


        verticalLayoutVehiculesRight->addWidget(frameMission);

        frameStatsVehicules = new QFrame(pageVehicules);
        frameStatsVehicules->setObjectName("frameStatsVehicules");
        frameStatsVehicules->setFrameShape(QFrame::StyledPanel);
        frameStatsVehicules->setFrameShadow(QFrame::Plain);
        frameStatsVehicules->setMinimumSize(QSize(300, 0));
        frameStatsVehicules->setMaximumSize(QSize(340, 16777215));
        verticalLayoutStatsVehicules = new QVBoxLayout(frameStatsVehicules);
        verticalLayoutStatsVehicules->setSpacing(12);
        verticalLayoutStatsVehicules->setObjectName("verticalLayoutStatsVehicules");
        verticalLayoutStatsVehicules->setContentsMargins(20, 18, 20, 18);
        labelStatsVehiculesTitle = new QLabel(frameStatsVehicules);
        labelStatsVehiculesTitle->setObjectName("labelStatsVehiculesTitle");

        verticalLayoutStatsVehicules->addWidget(labelStatsVehiculesTitle);

        labelStatVehDispo = new QLabel(frameStatsVehicules);
        labelStatVehDispo->setObjectName("labelStatVehDispo");

        verticalLayoutStatsVehicules->addWidget(labelStatVehDispo);

        progressStatVehDispo = new QProgressBar(frameStatsVehicules);
        progressStatVehDispo->setObjectName("progressStatVehDispo");
        progressStatVehDispo->setMaximum(100);
        progressStatVehDispo->setValue(0);
        progressStatVehDispo->setTextVisible(false);

        verticalLayoutStatsVehicules->addWidget(progressStatVehDispo);

        labelStatVehMaint = new QLabel(frameStatsVehicules);
        labelStatVehMaint->setObjectName("labelStatVehMaint");

        verticalLayoutStatsVehicules->addWidget(labelStatVehMaint);


        verticalLayoutVehiculesRight->addWidget(frameStatsVehicules);

        spacerVehiculesRight = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutVehiculesRight->addItem(spacerVehiculesRight);


        horizontalLayoutVehiculesBody->addLayout(verticalLayoutVehiculesRight);

        horizontalLayoutVehiculesBody->setStretch(0, 1);

        verticalLayoutVehicules->addLayout(horizontalLayoutVehiculesBody);

        stackedWidget->addWidget(pageVehicules);

        horizontalLayoutMain->addWidget(stackedWidget);

        horizontalLayoutMain->setStretch(1, 1);
        GSmartFireStation->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(GSmartFireStation);
        statusbar->setObjectName("statusbar");
        GSmartFireStation->setStatusBar(statusbar);

        retranslateUi(GSmartFireStation);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GSmartFireStation);
    } // setupUi

    void retranslateUi(QMainWindow *GSmartFireStation)
    {
        GSmartFireStation->setWindowTitle(QCoreApplication::translate("GSmartFireStation", "Smart Fire Station Management", nullptr));
        btnNavDashboard->setText(QCoreApplication::translate("GSmartFireStation", "\342\214\202   Dashboard", nullptr));
        btnNavDashboard->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "navButton", nullptr)));
        btnNavPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "\342\231\237   Personnel", nullptr));
        btnNavPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "navButton", nullptr)));
        btnNavVehicules->setText(QCoreApplication::translate("GSmartFireStation", "\342\226\243   V\303\251hicules", nullptr));
        btnNavVehicules->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "navButton", nullptr)));
        btnQuitter->setText(QCoreApplication::translate("GSmartFireStation", "\342\217\273   Quitter", nullptr));
        btnQuitter->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "navQuit", nullptr)));
        labelRole->setText(QCoreApplication::translate("GSmartFireStation", "Responsable du bureau op\303\251rationnel", nullptr));
        labelDashTitle->setText(QCoreApplication::translate("GSmartFireStation", "Dashboard", nullptr));
        labelDashTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "pageTitle", nullptr)));
        labelDashSubtitle->setText(QCoreApplication::translate("GSmartFireStation", "Vue g\303\251n\303\251rale de la station et \303\251tat des ressources", nullptr));
        labelDashSubtitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "pageSubtitle", nullptr)));
        lineDash->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "separator", nullptr)));
        cardPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "card", nullptr)));
        labelcardPersonnelTitle->setText(QCoreApplication::translate("GSmartFireStation", "Personnel", nullptr));
        labelcardPersonnelTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardSubtitle", nullptr)));
        labelNbPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "0", nullptr));
        labelNbPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "bigGreen", nullptr)));
        labelPersonnelDispoDetail->setText(QCoreApplication::translate("GSmartFireStation", "Disponibles : 0", nullptr));
        labelPersonnelDispoDetail->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardDetail", nullptr)));
        cardVehicules->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "card", nullptr)));
        labelcardVehiculesTitle->setText(QCoreApplication::translate("GSmartFireStation", "V\303\251hicules", nullptr));
        labelcardVehiculesTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardSubtitle", nullptr)));
        labelNbVehicules->setText(QCoreApplication::translate("GSmartFireStation", "0", nullptr));
        labelNbVehicules->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "bigGreen", nullptr)));
        labelVehiculesDispoDetail->setText(QCoreApplication::translate("GSmartFireStation", "Disponibles : 0", nullptr));
        labelVehiculesDispoDetail->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardDetail", nullptr)));
        cardAlertes->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "card", nullptr)));
        labelcardAlertesTitle->setText(QCoreApplication::translate("GSmartFireStation", "Alertes", nullptr));
        labelcardAlertesTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardSubtitle", nullptr)));
        labelNbAlertes->setText(QCoreApplication::translate("GSmartFireStation", "0", nullptr));
        labelNbAlertes->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "bigRed", nullptr)));
        labelAlertesDetail->setText(QCoreApplication::translate("GSmartFireStation", "Surcharge / maintenance", nullptr));
        labelAlertesDetail->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardDetail", nullptr)));
        frameDisponibilite->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "card", nullptr)));
        labelDispoTitle->setText(QCoreApplication::translate("GSmartFireStation", "Disponibilit\303\251 des ressources", nullptr));
        labelDispoTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardTitle", nullptr)));
        labelDispoRow0->setText(QCoreApplication::translate("GSmartFireStation", "Personnel disponibles", nullptr));
        labelPersonnelDispoCount->setText(QCoreApplication::translate("GSmartFireStation", "0/0", nullptr));
        labelPersonnelDispoCount->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardDetail", nullptr)));
        labelDispoRow1->setText(QCoreApplication::translate("GSmartFireStation", "Personnel en mission", nullptr));
        labelPersonnelMissionCount->setText(QCoreApplication::translate("GSmartFireStation", "0/0", nullptr));
        labelPersonnelMissionCount->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardDetail", nullptr)));
        labelDispoRow2->setText(QCoreApplication::translate("GSmartFireStation", "V\303\251hicules disponibles", nullptr));
        labelVehiculesDispoCount->setText(QCoreApplication::translate("GSmartFireStation", "0/0", nullptr));
        labelVehiculesDispoCount->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardDetail", nullptr)));
        labelDispoRow3->setText(QCoreApplication::translate("GSmartFireStation", "V\303\251hicules en maintenance", nullptr));
        labelVehiculesMaintCount->setText(QCoreApplication::translate("GSmartFireStation", "0/0", nullptr));
        labelVehiculesMaintCount->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardDetail", nullptr)));
        frameAlertes->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "card", nullptr)));
        labelAlertesTitle->setText(QCoreApplication::translate("GSmartFireStation", "Alertes et actions rapides", nullptr));
        labelAlertesTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardTitle", nullptr)));
        btnGererPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "G\303\251rer le personnel", nullptr));
        btnGererPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnPrimary", nullptr)));
        btnGererVehicules->setText(QCoreApplication::translate("GSmartFireStation", "G\303\251rer les v\303\251hicules", nullptr));
        btnGererVehicules->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnPrimary", nullptr)));
        btnVoirStats->setText(QCoreApplication::translate("GSmartFireStation", "Voir les statistiques", nullptr));
        btnVoirStats->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSecondary", nullptr)));
        labelPersonnelTitle->setText(QCoreApplication::translate("GSmartFireStation", "Gestion du personnel", nullptr));
        labelPersonnelTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "pageTitle", nullptr)));
        btnRetourPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "\342\206\220 Retour au Dashboard", nullptr));
        btnRetourPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSecondary", nullptr)));
        labelPersonnelSubtitle->setText(QCoreApplication::translate("GSmartFireStation", "CRUD, recherche, tri, export, statistiques et gestion de la charge", nullptr));
        labelPersonnelSubtitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "pageSubtitle", nullptr)));
        linePersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "separator", nullptr)));
        frameToolbarPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "card", nullptr)));
        labelRecherchePersonnel->setText(QCoreApplication::translate("GSmartFireStation", "Recherche :", nullptr));
        lineEditRecherchePersonnel->setPlaceholderText(QCoreApplication::translate("GSmartFireStation", "Nom / ID / Grade", nullptr));
        labelTriPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "Trier par :", nullptr));
        comboTriPersonnel->setItemText(0, QCoreApplication::translate("GSmartFireStation", "Grade", nullptr));
        comboTriPersonnel->setItemText(1, QCoreApplication::translate("GSmartFireStation", "Disponibilit\303\251", nullptr));
        comboTriPersonnel->setItemText(2, QCoreApplication::translate("GSmartFireStation", "Nom", nullptr));

        btnRechercherPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "Rechercher", nullptr));
        btnRechercherPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnPrimary", nullptr)));
        btnTrierPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "Trier", nullptr));
        btnTrierPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSecondary", nullptr)));
        btnExportPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "Exporter PDF", nullptr));
        btnExportPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSecondary", nullptr)));
        btnStatsPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "Statistiques", nullptr));
        btnStatsPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSecondary", nullptr)));
        btnAjouterPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "Ajouter", nullptr));
        btnAjouterPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSuccess", nullptr)));
        btnModifierPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "Modifier", nullptr));
        btnModifierPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSecondary", nullptr)));
        btnSupprimerPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "Supprimer", nullptr));
        btnSupprimerPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnDanger", nullptr)));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetPersonnel->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GSmartFireStation", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetPersonnel->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GSmartFireStation", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetPersonnel->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("GSmartFireStation", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetPersonnel->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("GSmartFireStation", "Grade", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetPersonnel->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("GSmartFireStation", "Poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetPersonnel->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("GSmartFireStation", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetPersonnel->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("GSmartFireStation", "Disponibilit\303\251", nullptr));
        frameSurcharge->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "card", nullptr)));
        labelSurchargeTitle->setText(QCoreApplication::translate("GSmartFireStation", "D\303\251tection de surcharge", nullptr));
        labelSurchargeTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardTitle", nullptr)));
        labelSeuil->setText(QCoreApplication::translate("GSmartFireStation", "Seuil de charge :", nullptr));
        spinSeuil->setSuffix(QCoreApplication::translate("GSmartFireStation", " %", nullptr));
        labelSurchargeNom->setText(QCoreApplication::translate("GSmartFireStation", "\342\200\224", nullptr));
        labelSurchargeCharge->setText(QString());
        labelSurchargeCharge->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "textDanger", nullptr)));
        labelSurchargeEtat->setText(QString());
        labelSurchargeEtat->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "textDangerBold", nullptr)));
        btnDetailsSurcharge->setText(QCoreApplication::translate("GSmartFireStation", "Voir les d\303\251tails", nullptr));
        btnDetailsSurcharge->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnDanger", nullptr)));
        frameStatsPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "card", nullptr)));
        labelStatsPersonnelTitle->setText(QCoreApplication::translate("GSmartFireStation", "Statistiques", nullptr));
        labelStatsPersonnelTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardTitle", nullptr)));
        labelStatDispo->setText(QCoreApplication::translate("GSmartFireStation", "Disponibles", nullptr));
        progressStatDispo->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "barGreen", nullptr)));
        labelStatMission->setText(QCoreApplication::translate("GSmartFireStation", "En mission", nullptr));
        progressStatMission->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "barOrange", nullptr)));
        labelTotalPersonnel->setText(QCoreApplication::translate("GSmartFireStation", "Total : 0 personnel", nullptr));
        labelTotalPersonnel->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardDetail", nullptr)));
        labelVehiculesTitle->setText(QCoreApplication::translate("GSmartFireStation", "Gestion des v\303\251hicules", nullptr));
        labelVehiculesTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "pageTitle", nullptr)));
        btnRetourVehicule->setText(QCoreApplication::translate("GSmartFireStation", "\342\206\220 Retour au Dashboard", nullptr));
        btnRetourVehicule->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSecondary", nullptr)));
        labelVehiculesSubtitle->setText(QCoreApplication::translate("GSmartFireStation", "CRUD, recherche, tri, export, statistiques et choix adapt\303\251 \303\240 la mission", nullptr));
        labelVehiculesSubtitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "pageSubtitle", nullptr)));
        lineVehicules->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "separator", nullptr)));
        frameToolbarVehicule->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "card", nullptr)));
        labelRechercheVehicule->setText(QCoreApplication::translate("GSmartFireStation", "Recherche :", nullptr));
        lineEditRechercheVehicule->setPlaceholderText(QCoreApplication::translate("GSmartFireStation", "Immatriculation / Type", nullptr));
        labelTriVehicule->setText(QCoreApplication::translate("GSmartFireStation", "Trier par :", nullptr));
        comboTriVehicule->setItemText(0, QCoreApplication::translate("GSmartFireStation", "\303\211tat", nullptr));
        comboTriVehicule->setItemText(1, QCoreApplication::translate("GSmartFireStation", "Type", nullptr));

        btnRechercherVehicule->setText(QCoreApplication::translate("GSmartFireStation", "Rechercher", nullptr));
        btnRechercherVehicule->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnPrimary", nullptr)));
        btnTrierVehicule->setText(QCoreApplication::translate("GSmartFireStation", "Trier", nullptr));
        btnTrierVehicule->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSecondary", nullptr)));
        btnExportVehicule->setText(QCoreApplication::translate("GSmartFireStation", "Exporter PDF", nullptr));
        btnExportVehicule->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSecondary", nullptr)));
        btnStatsVehicule->setText(QCoreApplication::translate("GSmartFireStation", "Statistiques", nullptr));
        btnStatsVehicule->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSecondary", nullptr)));
        btnAjouterVehicule->setText(QCoreApplication::translate("GSmartFireStation", "Ajouter", nullptr));
        btnAjouterVehicule->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSuccess", nullptr)));
        btnModifierVehicule->setText(QCoreApplication::translate("GSmartFireStation", "Modifier", nullptr));
        btnModifierVehicule->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnSecondary", nullptr)));
        btnSupprimerVehicule->setText(QCoreApplication::translate("GSmartFireStation", "Supprimer", nullptr));
        btnSupprimerVehicule->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnDanger", nullptr)));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetVehicules->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("GSmartFireStation", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetVehicules->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("GSmartFireStation", "Immat.", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetVehicules->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("GSmartFireStation", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetVehicules->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("GSmartFireStation", "Mod\303\250le", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetVehicules->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("GSmartFireStation", "\303\211tat", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetVehicules->horizontalHeaderItem(5);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("GSmartFireStation", "Disponibilit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetVehicules->horizontalHeaderItem(6);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("GSmartFireStation", "Maintenance", nullptr));
        frameMission->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "card", nullptr)));
        labelMissionTitle->setText(QCoreApplication::translate("GSmartFireStation", "Choix adapt\303\251 \303\240 la mission", nullptr));
        labelMissionTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardTitle", nullptr)));
        labelTypeIntervention->setText(QCoreApplication::translate("GSmartFireStation", "Type d\342\200\231intervention :", nullptr));
        comboIntervention->setItemText(0, QCoreApplication::translate("GSmartFireStation", "Incendie", nullptr));
        comboIntervention->setItemText(1, QCoreApplication::translate("GSmartFireStation", "Secours \303\240 personne", nullptr));
        comboIntervention->setItemText(2, QCoreApplication::translate("GSmartFireStation", "Accident de la route", nullptr));
        comboIntervention->setItemText(3, QCoreApplication::translate("GSmartFireStation", "Inondation", nullptr));

        labelVehiculeProposeTxt->setText(QCoreApplication::translate("GSmartFireStation", "V\303\251hicule propos\303\251 :", nullptr));
        labelVehiculePropose->setText(QCoreApplication::translate("GSmartFireStation", "\342\200\224", nullptr));
        labelVehiculePropose->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "textPrimaryBold", nullptr)));
        labelVehiculeInfo->setText(QString());
        labelVehiculeInfo->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "textSuccess", nullptr)));
        btnUtiliserVehicule->setText(QCoreApplication::translate("GSmartFireStation", "Utiliser ce v\303\251hicule", nullptr));
        btnUtiliserVehicule->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "btnPrimary", nullptr)));
        frameStatsVehicules->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "card", nullptr)));
        labelStatsVehiculesTitle->setText(QCoreApplication::translate("GSmartFireStation", "Statistiques v\303\251hicules", nullptr));
        labelStatsVehiculesTitle->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "cardTitle", nullptr)));
        labelStatVehDispo->setText(QCoreApplication::translate("GSmartFireStation", "Disponibles : 0 / 0", nullptr));
        progressStatVehDispo->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "barGreen", nullptr)));
        labelStatVehMaint->setText(QCoreApplication::translate("GSmartFireStation", "En maintenance : 0", nullptr));
        labelStatVehMaint->setProperty("class", QVariant(QCoreApplication::translate("GSmartFireStation", "textWarning", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class GSmartFireStation: public Ui_GSmartFireStation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSMARTFIRESTATION_H
