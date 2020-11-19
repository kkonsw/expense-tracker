TEMPLATE = app
QT += gui

CONFIG += c++14

isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR=$$(CATCH_INCLUDE_DIR)

# set by Qt Creator wizard
isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR="/home/kkon/projects/unn/databases/xclicker/tests/catch.hpp"
!isEmpty(CATCH_INCLUDE_DIR): INCLUDEPATH *= $${CATCH_INCLUDE_DIR}

isEmpty(CATCH_INCLUDE_DIR): {
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
}

SOURCES += \
    main.cpp \
    test_dbmanager.cpp \
    test_usertable.cpp

LIBS += -lsqlite3

# sqlite_orm
INCLUDEPATH += ../3rd-party/sqlite_orm/

# app
unix:!macx: LIBS += -L$$OUT_PWD/../app/ -lapp

INCLUDEPATH += $$PWD/../app
DEPENDPATH += $$PWD/../app

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../app/libapp.a
