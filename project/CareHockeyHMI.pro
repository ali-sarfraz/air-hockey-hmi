#-------------------------------------------------
#
# Project created by QtCreator 2020-11-05T21:35:52
#
#-------------------------------------------------

QT       += core gui widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CareHockeyHMImatchSettingsObjPtr
TEMPLATE = app

# Add the ld library to account for the SQLite database.
LIBS += -ldl

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
        mainmenuwindow.cpp \
    usermatchsettings.cpp \
    usermatchsettingswindow.cpp \
    tableconfigurationsettingswindow.cpp \
    tableconfigurationsettings.cpp \
#    player.cpp \
#    playersettings.cpp
    player.cpp \
    playersettingswindow.cpp \
    gamedisplay.cpp\
    goal.cpp\
    game.cpp \
    matchdisplay.cpp\
    MessageHandler.cpp\
    MessagePacket.cpp \
    sqlite3.c \
    databasewindow.cpp



HEADERS += \
        mainmenuwindow.h \
    usermatchsettings.h \
    usermatchsettingswindow.h \
    tableconfigurationsettingswindow.h \
    tableconfigurationsettings.h \
#    player.h \
#    playersettings.h
    player.h \
    playersettingswindow.h \
    gamedisplay.h\
    goal.h\
    game.h\
    matchdisplay.h\
    MessageHandler.h\
    MessageLibrary.h\
    MessagePacket.h \
    gameoutcome.h \
    sqlite3.h \
    sqlite3ext.h \
    databasewindow.h

FORMS += \
        mainmenuwindow.ui \
    usermatchsettingswindow.ui \
    tableconfigurationsettingswindow.ui \
#    playersettings.ui
    playersettingswindow.ui \
    gamedisplay.ui \
    matchdisplay.ui \
    databasewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
