#include "transactions_window.h"
#include "newtransaction_dialog.h"
#include "db/db_manager.h"

#include <QApplication>
#include <QDateTime>

void CreateTestData(Database *db)
{
    db->remove_all<Transaction>();
    db->remove_all<User>();

    User user({-1, "John Doe"});
    db->insert(user);
}

void AddCategories(Database *db)
{
    db->remove_all<Category>();

    db->insert<Category>({-1, "Bills"});
    db->insert<Category>({-1, "Food"});
    db->insert<Category>({-1, "Leisure"});
    db->insert<Category>({-1, "Homeneeds"});
    db->insert<Category>({-1, "Transport"});
    db->insert<Category>({-1, "Healthcare"});
    db->insert<Category>({-1, "Income"});
    db->insert<Category>({-1, "Miscellaneous"});
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // add data to database
    DBManager db_manager;

    NewTransactionDialog dialog(db_manager.getDatabase());
    dialog.show();

    return a.exec();
}
