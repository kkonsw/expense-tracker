#include "transactions_window.h"
#include "newtransaction_dialog.h"
#include "db/db_manager.h"

#include <QApplication>
#include <QDateTime>

void CreateTestData(Database *db)
{
    // clear database
    db->remove_all<Transaction>();
    db->remove_all<User>();

    User user({-1, "John Doe"});
    int seconds = QDateTime::currentSecsSinceEpoch();
    Transaction transaction({-1, nullptr, seconds, 1.11, "Testing"});

    int user_id = db->insert(user);
    transaction.user_id = std::make_unique<int>(user_id);
    db->insert(transaction);
    db->insert(transaction);
    db->insert(transaction);
    db->insert(transaction);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // add data to database
    DBManager db_manager;
    CreateTestData(db_manager.getDatabase());

    NewTransactionDialog dialog(db_manager.getDatabase());
    dialog.show();

    return a.exec();
}
