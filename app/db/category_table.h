#ifndef CATEGORYTABLE_H
#define CATEGORYTABLE_H

#include "database.h"
#include "table.h"

class CategoryTable : public Table<Category>
{
public:
    CategoryTable() = delete;
    CategoryTable(Database *db);
    ~CategoryTable();

    int getIdFromName(const std::string& name) const;
};

#endif // CATEGORYTABLE_H
