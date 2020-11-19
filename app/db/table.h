#ifndef TABLE_H
#define TABLE_H

#include "database.h"

class Table
{
public:
    Table() = delete;
    Table(Database *database);
    virtual ~Table();

protected:
    Database* db;
};

#endif // TABLE_H
