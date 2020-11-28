#ifndef USERSMODEL_H
#define USERSMODEL_H

#include <QSqlRelationalTableModel>
#include <QSqlDatabase>

class UsersModel : public QSqlRelationalTableModel
{
public:
    UsersModel(QSqlDatabase *db);
};

#endif // USERSMODEL_H
