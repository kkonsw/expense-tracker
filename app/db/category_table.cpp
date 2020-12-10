#include "category_table.h"

CategoryTable::CategoryTable(Database *db):
    Table(db)
{

}

CategoryTable::~CategoryTable()
{

}

int CategoryTable::getIdFromName(const std::string &name) const
{
    auto categories = db->get_all<Category>(where(c(&Category::cat_name)
                                                  == name));
    if (categories.empty()) {
        return invalidID;
    }

    return categories.begin()->id;
}
