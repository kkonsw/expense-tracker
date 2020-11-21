#include "user_table.h"

UserTable::UserTable(Database *database):
    Table(database)
{

}

UserTable::~UserTable()
{

}

int UserTable::add_user(const User &user)
{
    int id = db->insert(user);
    return id;
}

void UserTable::remove_user(int id)
{
    db->remove<User>(id);
}

std::unique_ptr<User> UserTable::get_user(int id) const
{
    return db->get_pointer<User>(id);
}

void UserTable::remove_all_users()
{
    db->remove_all<User>();
}

std::vector<User> UserTable::get_all_users() const
{
    return db->get_all<User>();
}
