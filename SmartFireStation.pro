QT       += core gui widgets

TARGET = SmartFireStation
TEMPLATE = app

SOURCES += \
    main.cpp \
    gsmartfirestation.cpp \
    gsmartfirestation_personnel.cpp \
    gsmartfirestation_vehicules.cpp \
    personnel.cpp \
    vehicule.cpp \
    personneldialog.cpp \
    vehiculedialog.cpp \
    statsdialog.cpp \
    pdfexport.cpp \
    piechartwidget.cpp

HEADERS += \
    gsmartfirestation.h \
    personnel.h \
    vehicule.h \
    personneldialog.h \
    vehiculedialog.h \
    statsdialog.h \
    pdfexport.h \
    styleutils.h \
    piechartwidget.h

# Un seul fichier .ui
FORMS += \
    gsmartfirestation.ui

RESOURCES += \
    resources.qrc
