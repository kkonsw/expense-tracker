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

int SubcategoryTable::getId(const std::string &name, int cat_id) const
{
    auto subcategories = db->get_all<Subcategory>(where(c(&Subcategory::subcat_name)
                                                 == name));
    for (const auto& subcat : subcategories) {
        if (*subcat.cat_id == cat_id) {
            return subcat.id;
        }
    }
    return invalidID;
}
