#include "subcategory_table.h"
#include "category_table.h"

SubcategoryTable::SubcategoryTable(Database *db):
    Table(db)
{

}

SubcategoryTable::~SubcategoryTable()
{

}

std::vector<Subcategory> SubcategoryTable::getSubcategoriesFromCategory(
        const std::string &cat_name) const
{
    std::vector<Subcategory> subcategories;
    CategoryTable categories(db);
    auto id = categories.getIdFromName(cat_name);
    if (id != Table::invalidID) {
        subcategories = db->get_all<Subcategory>(where(c(&Subcategory::cat_id)
                                == id));
    }
    return subcategories;
}
