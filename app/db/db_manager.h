#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <memory>
#include "database.h"

class DBManager
{
public:
    DBManager();
    Database *getDatabase();

private:

    std::unique_ptr<Database> db;
};

#endif // DBMANAGER_H
