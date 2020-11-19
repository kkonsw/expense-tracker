#ifndef USER_H
#define USER_H

#include "database.h"
#include "table.h"


class UserTable : public Table
{
public:
    UserTable() = delete;
    UserTable(Database* database);
    ~UserTable();

    /** Add user to users table. Returns user id from database.
     *
     */
    int AddUser(const User& user);

    /** Remove user from users table.
     *
     */
    void RemoveUser(int id);
};

#endif // USER_H
