QT += core gui
QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    main_window.cpp \
    transactions_window.cpp

HEADERS += \
    main_window.h \
    transactions_window.h

# default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# app
unix:!macx: LIBS += -L$$OUT_PWD/../app/ -lapp

INCLUDEPATH += $$PWD/../app
DEPENDPATH += $$PWD/../app

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../app/libapp.a

FORMS += \
    transactions_window.ui
