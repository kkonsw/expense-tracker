#include "db_manager.h"


DBManager::DBManager():
    db(std::make_unique<Database>(init_storage()))
{
    db->sync_schema();
}

Database *DBManager::get_database()
{
    return db.get();
}
