#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "sqlite_orm.h"
#include "user.h"

using namespace sqlite_orm;

inline auto initStorage(const std::string &path = "db.sqlite") {
    return make_storage(path,
                    make_table("users",
                           make_column("id", &User::id, autoincrement(), primary_key()),
                           make_column("first_name", &User::firstName),
                           make_column("last_name", &User::lastName)));
}

using Storage = decltype(initStorage());

class DBManager
{
public:
    DBManager();
};

#endif // DBMANAGER_H
