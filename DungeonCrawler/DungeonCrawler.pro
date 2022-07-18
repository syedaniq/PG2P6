TEMPLATE = app
CONFIG -= app_bundle
QT += core gui
QT += testlib
    greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

SOURCES += \
        abstractui.cpp \
        active.cpp \
        attackcontroller.cpp \
        character.cpp \
        controller.cpp \
        door.cpp \
        dungeoncrawler.cpp \
        floor.cpp \
        graph.cpp \
        graphicalui.cpp \
        guardcontroller.cpp \
        level.cpp \
        levelchanger.cpp \
        levelverwaltung.cpp \
        list.cpp \
        lootchest.cpp \
        losescreen.cpp \
        main.cpp \
        mainwindow.cpp \
        passive.cpp \
        pit.cpp \
        portal.cpp \
        ramp.cpp \
        startscreen.cpp \
        stationarycontroller.cpp \
        switch.cpp \
        terminalui.cpp \
        tile.cpp \
        victoryscreen.cpp \
        wall.cpp

HEADERS += \
    abstractui.h \
    active.h \
    attackcontroller.h \
    character.h \
    controller.h \
    door.h \
    dungeoncrawler.h \
    floor.h \
    graph.h \
    graphicalui.h \
    guardcontroller.h \
    json.hpp \
    level.h \
    levelchanger.h \
    levelverwaltung.h \
    list.h \
    lootchest.h \
    losescreen.h \
    mainwindow.h \
    passive.h \
    pit.h \
    portal.h \
    ramp.h \
    startscreen.h \
    stationarycontroller.h \
    switch.h \
    terminalui.h \
    tile.h \
    victoryscreen.h \
    wall.h

FORMS += \
    losescreen.ui \
    mainwindow.ui \
    startscreen.ui \
    victoryscreen.ui

RESOURCES += \
    scam.qrc

DISTFILES += \
    level1.json
