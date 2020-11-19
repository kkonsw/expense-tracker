#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite_orm.h"

struct User
{
    int id;
    std::string first_name;
    std::string last_name;
};

using namespace sqlite_orm;

inline auto init_storage(const std::string &path = "db.sqlite")
{
    return make_storage(path,
                    make_table("users",
                           make_column("id", &User::id, autoincrement(),
                                       primary_key()),
                           make_column("first_name", &User::first_name),
                           make_column("last_name", &User::last_name)));
}

using Database = decltype(init_storage());

#endif // DATABASE_H
