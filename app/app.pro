QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++14

SOURCES += \
    db/db_manager.cpp \
    db/table.cpp \
    db/user_table.cpp

HEADERS += \
    db/database.h \
    db/db_manager.h \
    db/table.h \
    db/user_table.h

LIBS += -lsqlite3

# default rules for deployment
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

# sqlite_orm
INCLUDEPATH += ../3rd-party/sqlite_orm/
INCLUDEPATH += db/
