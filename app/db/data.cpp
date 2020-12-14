#include "data.h"
#include "category_table.h"

#include <vector>
#include <string>
#include <unordered_map>

void AddUsers(Database *db)
{
    db->remove_all<User>();
    db->insert<User>({-1, "Kuznetsov Konstantin"});
}

void AddCategories(Database *db)
{
    db->remove_all<Category>();
    std::vector<std::string> categories = {"Bills", "Food", "Leisure", "Homeneeds",
                                           "Transport", "Healthcare", "Miscellaneous"};
    for (const auto& cat : categories) {
        db->insert<Category>({-1, cat});
    }
}

void AddSubcategories(Database *db)
{
    db->remove_all<Subcategory>();

    using SubcatNames = std::vector<std::string>;
    SubcatNames bills = {"Phone", "Electricity", "Internet", "Apartment", "Water", "Other"};
    SubcatNames food = {"Groceries", "Other"};
    SubcatNames leisure = {"Dining Out", "Movies", "Other"};
    SubcatNames homeneeds = {"Clothing", "Furnishing", "Other"};
    SubcatNames transport = {"Public", "Taxi", "Other"};
    SubcatNames healthcare = {"Pharmacy", "Dental", "Other"};
    SubcatNames miscellaneous = {"Other"};

    std::map<std::string, SubcatNames> subcategories = {
        {"Bills", bills},
        {"Food", food},
        {"Leisure", leisure},
        {"Homeneeds", homeneeds},
        {"Transport", transport},
        {"Healthcare", healthcare},
        {"Miscellaneous", miscellaneous},
    };

    CategoryTable categories(db);
    for (const auto& subcat : subcategories) {
        for (const auto& name : subcat.second) {
            db->insert<Subcategory>({-1, std::make_unique<int>(
                     categories.getIdFromName(subcat.first)), name});
        }
    }
}
