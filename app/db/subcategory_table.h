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

    /** Returns id for subcategory.
     *
     * @param name - name for subcategory.
     * @param cat_id - id for category that includes subcategory.
     * @return
     */
    int getId(const std::string &name, int cat_id) const;
};

#endif // SUBCATEGORYTABLE_H
