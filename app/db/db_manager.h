#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <memory>
#include "database.h"

class DBManager
{
public:
    static Database* getDatabase();
    Database* getDB();

private:
    DBManager();
    std::unique_ptr<Database> db;
};

#endif // DBMANAGER_H
