#include "users_model.h"

#include <QSqlRecord>

UsersModel::UsersModel(QSqlDatabase *db):
    QSqlRelationalTableModel(nullptr, *db)
{
    setTable("users");
    select();
}

void UsersModel::CreateTestData()
{
    int rows = 1;
    QSqlRecord record = this->record();
    for (int i = 0; i < rows; ++i)
    {
        record.setValue("name", "John Doe");
        insertRecord(-1, record);
    }
    submitAll();
    select();
}


