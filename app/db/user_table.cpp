#include "user_table.h"

UserTable::UserTable(Database *database):
    Table(database)
{

}

UserTable::~UserTable()
{

}

int UserTable::AddUser(const User &user)
{
    int id = db->insert(user);
    return id;
}

void UserTable::RemoveUser(int id)
{
    db->remove<User>(id);
}
