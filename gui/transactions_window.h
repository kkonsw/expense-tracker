#ifndef TRANSACTIONS_WINDOW_H
#define TRANSACTIONS_WINDOW_H

#include <QWidget>
#include <QtSql/QSqlDatabase>

#include "transactions_model.h"
#include "db/database.h"
#include "db/transaction_table.h"
#include "db/category_table.h"

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
    std::unique_ptr<TransactionTable> transactions;
    std::unique_ptr<CategoryTable> categories;

    void updateExpenseLabels();

    /** Updates combo box with categories from database.
     *
     */
    void addCategoriesToUI();

    /** Returns model filter for selected category.
     *
     */
    QString getCategoryFilter() const;

    /** Returns model filter for selected dates.
     *
     */
    QString getDatesFilter() const;

    /** Returns total expenses from model with current filters.
     *
     */
    double getTotalExpenses() const;

    /** Returns max expense from model with current filters.
     *
     */
    double getMaxExpense() const;

private slots:

    /** Removes all Transactions from Database.
     *
     */
    void removeTransactions();

    /** Removes selected Transactions from Database.
     *
     */
    void removeSelectedTransactions();

    /** Show Transactions with current filters.
     *
     */
    void applyFilters();

};

#endif // TRANSACTIONS_WINDOW_H
