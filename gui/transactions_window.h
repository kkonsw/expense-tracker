#ifndef TRANSACTIONS_WINDOW_H
#define TRANSACTIONS_WINDOW_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRelationalTableModel>
#include "db/db_manager.h"

namespace Ui {
class TransactionsWindow;
}

class TransactionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionsWindow(QWidget *parent = nullptr);
    ~TransactionsWindow();

private:
    Ui::TransactionsWindow *ui;
    DBManager db_manager;
    QSqlDatabase db;
    std::unique_ptr<QSqlRelationalTableModel> model;

    void connectToDatabase();
    void createTestData();
};

#endif // TRANSACTIONS_WINDOW_H
