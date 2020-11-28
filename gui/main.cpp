#include "transactions_window.h"
#include "db/db_manager.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QDateTime>


void connectToDatabase(QSqlDatabase &db)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    db.open();
}

void CreateTestData(Database *db)
{
    // clear database
    db->remove_all<Transaction>();
    db->remove_all<User>();

    User user({-1, "John", "Doe"});
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

    // Qt Sql connection
    QSqlDatabase db;
    connectToDatabase(db);

    TransactionsWindow w(nullptr, &db);
    w.show();

    return a.exec();
}
