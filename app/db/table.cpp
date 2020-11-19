#include "table.h"

Table::Table(Database *database):
    db(database)
{
    if (db == nullptr)
    {
        throw std::runtime_error("Database is not initialized!");
    }
}

Table::~Table()
{

}
