QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    caritem.cpp \
    game.cpp \
    gamescene.cpp \
    main.cpp \
    view.cpp

HEADERS += \
    caritem.h \
    game.h \
    gamescene.h \
    line.h \
    quad.h \
    view.h

RESOURCES += \
    resource.qrc
