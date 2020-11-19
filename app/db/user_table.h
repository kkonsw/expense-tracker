#ifndef USER_H
#define USER_H

#include "database.h"
#include "table.h"
#include <memory>


class UserTable : public Table
{
public:
    UserTable() = delete;
    UserTable(Database* database);
    ~UserTable();

    /** Add user to users table. Returns user id from database.
     *
     */
    int add_user(const User& user);

    /** Remove user from users table.
     *
     */
    void remove_user(int id);

//	std::unique_ptr<User>
};

#endif // USER_H
