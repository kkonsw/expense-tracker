#include "transactions_window.h"
#include "newtransaction_dialog.h"
#include "db/db_manager.h"

#include <QApplication>
#include <QDateTime>

void CreateUsers(Database *db)
{
    db->insert<User>({-1, "Kuznetsov Konstantin"});
}

void AddCategories(Database *db)
{
    db->insert<Category>({-1, "Bills"});
    db->insert<Category>({-1, "Food"});
    db->insert<Category>({-1, "Leisure"});
    db->insert<Category>({-1, "Homeneeds"});
    db->insert<Category>({-1, "Transport"});
    db->insert<Category>({-1, "Healthcare"});
    db->insert<Category>({-1, "Miscellaneous"});
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NewTransactionDialog dialog;
    dialog.show();

    return a.exec();
}
