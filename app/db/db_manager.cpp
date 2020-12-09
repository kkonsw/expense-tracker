#include "db_manager.h"


DBManager::DBManager():
    db(std::make_unique<Database>(init_storage()))
{
    db->sync_schema();
}

Database * DBManager::getDatabase()
{
    static DBManager manager;
    return manager.getDB();
}

Database *DBManager::getDB()
{
    return db.get();
}
