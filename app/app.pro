QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++14

SOURCES += \
    dbmanager.cpp

HEADERS += \
    dbmanager.h

# default rules for deployment
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

# sqlite_orm
INCLUDEPATH += ../3rd-party/sqlite_orm/
