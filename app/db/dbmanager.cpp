#include "dbmanager.h"


DBManager::DBManager():
    db(std::make_unique<Database>(initStorage()))
{
    db->sync_schema();
}

Database *DBManager::GetDatabase()
{
    return db.get();
}
