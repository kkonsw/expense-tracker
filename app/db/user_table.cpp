#include "user_table.h"

UserTable::UserTable(Database *database):
    Table(database)
{

}

UserTable::~UserTable()
{

}

int UserTable::getIdFromName(const std::string &name) const
{
    auto users = db->get_all<User>(where(c(&User::name) == name));
    if (users.empty()) {
        return invalidID;
    }

    return users.begin()->id;
}
