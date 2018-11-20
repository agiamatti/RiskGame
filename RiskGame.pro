#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T13:30:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RiskGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        RiskGUI.cpp \
    Card.cpp \
    Continent.cpp \
    Country.cpp \
    Deck.cpp \
    Dice.cpp \
    Hand.cpp \
    Info.cpp \
    Map.cpp \
    MapLoader.cpp \
    Player.cpp \
    SettingsDialog.cpp \
    Subject.cpp \
    ObserverView.cpp \
    Observer.cpp \
    StrategyAggressive.cpp \
    StrategyBenevolent.cpp \
    StrategyHuman.cpp

HEADERS += \
        RiskGUI.h \
    Card.h \
    Continent.h \
    Country.h \
    Deck.h \
    Dice.h \
    Hand.h \
    Info.h \
    Map.h \
    MapLoader.h \
    Player.h \
    SettingsDialog.h \
    Subject.h \
    ObserverView.h \
    Observer.h \
    Strategy.h \
    StrategyAggressive.h \
    StrategyBenevolent.h \
    StrategyHuman.h

FORMS += \
        riskgui.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


ICON = myapp.icns
#RC_ICONS = myapp.ico
#from https://www.iconfinder.com/icons/2216341/earth_globe_location_map_world_world_globe_icon
