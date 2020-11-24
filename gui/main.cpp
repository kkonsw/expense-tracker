#include "transactions_window.h"

#include <QApplication>
#include <QSqlDatabase>

void connectToDatabase(QSqlDatabase &db)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    db.open();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db;
    connectToDatabase(db);

    TransactionsWindow w(nullptr, &db);
    w.show();

    return a.exec();
}
