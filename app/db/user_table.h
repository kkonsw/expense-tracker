#ifndef USER_H
#define USER_H

#include "database.h"
#include "table.h"


class UserTable : public Table<User>
{
public:
    UserTable() = delete;
    UserTable(Database* database);
    ~UserTable();
};

#endif // USER_H
