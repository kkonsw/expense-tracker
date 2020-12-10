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

    int getIdFromName(const std::string& name) const;
};

#endif // USER_H
