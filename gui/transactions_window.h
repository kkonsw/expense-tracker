#ifndef TRANSACTIONS_WINDOW_H
#define TRANSACTIONS_WINDOW_H

#include <QWidget>
#include <QtSql/QSqlDatabase>

#include "transactions_model.h"
#include "db/database.h"

namespace Ui {
class TransactionsWindow;
}

class TransactionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionsWindow(QSqlDatabase db, QWidget *parent = nullptr);
    ~TransactionsWindow();

    /** Updates table with Transactions from Database.
     *
     */
    void update();

private:
    Ui::TransactionsWindow *ui;
    std::unique_ptr<TransactionsModel> model;
    Database *db;

    /** Returns total expenses from Database.
     *
     */
    double getTotalExpenses() const;

private slots:

    /** Removes all Transactions from Database.
     *
     */
    void clearTransactions();
};

#endif // TRANSACTIONS_WINDOW_H
