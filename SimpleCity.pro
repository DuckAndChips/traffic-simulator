QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    City.cpp \
    buildings/Apartment.cpp \
    buildings/Avenue.cpp \
    buildings/Clinic.cpp \
    buildings/GoldMine.cpp \
    buildings/Health.cpp \
    buildings/Hospital.cpp \
    buildings/House.cpp \
    buildings/Node.cpp \
    buildings/Residential.cpp \
    buildings/Revenue.cpp \
    buildings/Road.cpp \
    buildings/SilverMine.cpp \
    buildings/Street.cpp \
    graphics.cpp \
    main_gui.cpp \
    mainwindow.cpp \
    menuwindow.cpp \
    Trip_distribution.cpp \
    Traffic_Model.cpp

HEADERS += \
    City.h \
    buildings/Apartment.h \
    buildings/Avenue.h \
    buildings/BuildingInformationFormatString.h \
    buildings/Clinic.h \
    buildings/GoldMine.h \
    buildings/Health.h \
    buildings/Hospital.h \
    buildings/House.h \
    buildings/Node.h \
    buildings/Residential.h \
    buildings/Revenue.h \
    buildings/Road.h \
    buildings/SilverMine.h \
    buildings/Street.h \
    graphics.h \
    mainwindow.h \
    menuwindow.h \
    Trip_distribution.h \
    Traffic_Model.h

FORMS += \
    mainwindow.ui \
    menuwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
