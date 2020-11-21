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

    /** Adds user to users table. Returns user id from database.
     *
     */
    int add_user(const User& user);

    /** Removes user from users table.
     *
     */
    void remove_user(int id);

    /** Returns user with requested id from users table.
     *  Returns nullptr is user with requested id is not found.
     */
    std::unique_ptr<User> get_user(int id) const;

    /** Removes all users from users table.
     *
     */
    void remove_all_users();

    /** Returns all users from users table.
     *
     */
    std::vector<User> get_all_users() const;
};

#endif // USER_H
