#include "users_model.h"

#include <QSqlRecord>

UsersModel::UsersModel(QSqlDatabase *db):
    QSqlRelationalTableModel(nullptr, *db)
{
    setTable("users");
    select();
}
