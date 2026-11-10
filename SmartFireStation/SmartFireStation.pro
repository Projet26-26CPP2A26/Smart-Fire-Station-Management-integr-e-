QT       += core gui widgets sql

TARGET = SmartFireStation
TEMPLATE = app

SOURCES += main.cpp gsmartfirestation.cpp personnel.cpp
HEADERS += gsmartfirestation.h personnel.h
FORMS   += gsmartfirestation.ui
RESOURCES += resources.qrc