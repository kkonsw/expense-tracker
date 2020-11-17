QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++14

SOURCES += \
    dbmanager.cpp \
    user.cpp

HEADERS += \
    database.h \
    dbmanager.h \
    user.h

LIBS += -lsqlite3

# default rules for deployment
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

# sqlite_orm
INCLUDEPATH += ../3rd-party/sqlite_orm/
