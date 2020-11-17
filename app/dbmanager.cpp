#include "dbmanager.h"


DBManager::DBManager()
{
    Storage storage = initStorage();
    storage.sync_schema();
}
