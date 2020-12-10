QT += core gui sql
QT += widgets

CONFIG += c++14

SOURCES += \
    main.cpp \
    message_dialog.cpp \
    newtransaction_dialog.cpp \
    style/style.cpp \
    transactions_window.cpp

HEADERS += \
    message_dialog.h \
    newtransaction_dialog.h \
    style/style.h \
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
    message_dialog.ui \
    newtransaction_dialog.ui \
    transactions_window.ui

INCLUDEPATH += style/

# sqlite_orm
INCLUDEPATH += ../3rd-party/sqlite_orm/
LIBS += -lsqlite3
