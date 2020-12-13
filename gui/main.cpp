#include "transactions_window.h"
#include "newtransaction_dialog.h"
#include "db/db_manager.h"
#include "db/category_table.h"

#include <QApplication>
#include <QDateTime>
#include <vector>
#include <string>
#include <unordered_map>

void AddUsers(Database *db)
{
    db->insert<User>({-1, "Kuznetsov Konstantin"});
}

void AddCategories(Database *db)
{
    std::vector<std::string> categories = {"Bills", "Food", "Leisure", "Homeneeds",
                                           "Transport", "Healthcare", "Miscellaneous"};
    for (const auto& cat : categories) {
        db->insert<Category>({-1, cat});
    }
}

void AddSubcategories(Database *db)
{
    db->remove_all<SubCategory>();

    using SubcatNames = std::vector<std::string>;
    SubcatNames bills = {"Other", "Phone", "Electricity", "Internet", "Apartment", "Water"};
    SubcatNames food = {"Other", "Groceries"};
    SubcatNames leisure = {"Other", "Dining Out", "Movies"};
    SubcatNames homeneeds = {"Other", "Clothing", "Furnishing"};
    SubcatNames transport = {"Other", "Public", "Taxi"};
    SubcatNames healthcare = {"Other", "Pharmacy", "Dental"};
    SubcatNames miscellaneous = {"Miscellaneous"};

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
            db->insert<SubCategory>({-1, std::make_unique<int>(
                     categories.getIdFromName(subcat.first)), name});
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NewTransactionDialog dialog;
    dialog.show();

    return a.exec();
}
