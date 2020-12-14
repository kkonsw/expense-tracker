#ifndef SUBCATEGORYTABLE_H
#define SUBCATEGORYTABLE_H

#include "database.h"
#include "table.h"

#include <vector>

class SubcategoryTable : public Table<Subcategory>
{
public:
    SubcategoryTable() = delete;
    SubcategoryTable(Database *db);
    ~SubcategoryTable();

    std::vector<Subcategory> getSubcategoriesFromCategory(
            const std::string &cat_name) const;
};

#endif // SUBCATEGORYTABLE_H
