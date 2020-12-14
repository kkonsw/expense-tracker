#include <catch2/catch.hpp>
#include "db/db_manager.h"
#include "db/database.h"
#include "db/subcategory_table.h"
#include "db/data.h"

class SubcategoryTableFixture
{
public:
    SubcategoryTableFixture():
        db(DBManager::getDatabase()),
        subcategories(std::make_unique<SubcategoryTable>(SubcategoryTable(db)))
    {
        // clear database
        db->remove_all<Subcategory>();
        db->remove_all<Category>();
        AddCategories(db);
        AddSubcategories(db);
    }

protected:
    Database* db;
    std::unique_ptr<SubcategoryTable> subcategories;
};

TEST_CASE_METHOD(SubcategoryTableFixture, "Get subcategories from category name",
                 "[Subcategory Table]")
{
    std::vector<std::string> bills = {"Phone", "Electricity", "Internet",
                         "Apartment", "Water", "Other"};
    auto subcats = subcategories->getSubcategoriesFromCategory("Bills");
    REQUIRE(subcats.size() == 6);
    REQUIRE(subcats[0].subcat_name == bills[0]);
}

TEST_CASE_METHOD(SubcategoryTableFixture,
                 "Get subcategories with invalid category name",
                 "[Subcategory Table]")
{
    auto subcats = subcategories->getSubcategoriesFromCategory("abc");
    REQUIRE(subcats.size() == 0);
}
