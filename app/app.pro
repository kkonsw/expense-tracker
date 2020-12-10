QT -= gui
QT += sql core

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++14

SOURCES += \
    db/category_table.cpp \
    db/db_manager.cpp \
    db/transaction_table.cpp \
    db/user_table.cpp \
    transactions_model.cpp

HEADERS += \
    db/category_table.h \
    db/database.h \
    db/db_manager.h \
    db/table.h \
    db/transaction_table.h \
    db/user_table.h \
    transactions_model.h

LIBS += -lsqlite3

# default rules for deployment
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

# sqlite_orm
INCLUDEPATH += ../3rd-party/sqlite_orm/
INCLUDEPATH += db/
