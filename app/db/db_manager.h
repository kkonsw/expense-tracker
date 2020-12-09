#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <memory>
#include "database.h"

class DBManager
{
public:
    static Database* getDatabase();

private:
    Database* getDB();
    DBManager();
    std::unique_ptr<Database> db;
};

#endif // DBMANAGER_H
