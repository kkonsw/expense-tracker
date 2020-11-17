#include "dbmanager.h"
#include "user.h"

using namespace sqlite_orm;

DBManager::DBManager()
{
    auto storage = make_storage("db.sqlite",
                                make_table("users",
                                           make_column("id", &User::id, autoincrement(), primary_key()),
                                           make_column("first_name", &User::firstName),
                                           make_column("last_name", &User::lastName)));
    storage.sync_schema();
}
