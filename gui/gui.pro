QT += core gui
QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

# default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# app
unix:!macx: LIBS += -L$$OUT_PWD/../app/ -lapp

INCLUDEPATH += $$PWD/../app
DEPENDPATH += $$PWD/../app

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../app/libapp.a
