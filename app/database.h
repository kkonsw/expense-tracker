#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite_orm.h"
#include "user.h"

using namespace sqlite_orm;

inline auto initStorage(const std::string &path = "db.sqlite")
{
    return make_storage(path,
                    make_table("users",
                           make_column("id", &User::id, autoincrement(),
                                       primary_key()),
                           make_column("first_name", &User::firstName),
                           make_column("last_name", &User::lastName)));
}

using Database = decltype(initStorage());

#endif // DATABASE_H
