QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    adresse.cpp \
    myort.cpp \
    ort.cpp \
    poi.cpp \
    test_navi.cpp

HEADERS += \
    graph.h \
    mainwindow.h \
    adresse.h \
    myort.h \
    ort.h \
    poi.h \
    test_navi.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    german_map.qrc
