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
