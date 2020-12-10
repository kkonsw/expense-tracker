#ifndef NEWTRANSACTION_DIALOG_H
#define NEWTRANSACTION_DIALOG_H

#include <QDialog>
#include <QString>
#include <vector>

#include "db/database.h"
#include "db/user_table.h"
#include "db/transaction_table.h"
#include "db/category_table.h"
#include "transactions_window.h"

namespace Ui {
class NewTransactionDialog;
}

class NewTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTransactionDialog(QWidget *parent = nullptr);
    ~NewTransactionDialog();

private slots:
    /** Opens new window with all transactions.
     *
     */
    void viewAllTransactions();

    /** Adds new Transaction to Database.
     *
     */
    void addTransaction();

private:
    Ui::NewTransactionDialog *ui;
    TransactionsWindow* w;
    std::unique_ptr<UserTable> users;
    std::unique_ptr<TransactionTable> transactions;
    std::unique_ptr<CategoryTable> categories;

    /** User Name.
     *
     */
    std::string userName;

    /** Returns user id from name.
     *
     */
    int getUserIdFromDatabase();

    /** Creates new Transaction with data provided by user.
     *
     */
    bool createNewTransaction(Transaction &transaction);

    /** Validates Transaction amount from user input.
     *
     */
    bool checkTransactionAmount(QString& amount) const;

    /** Returns date in seconds.
     *
     */
    int getDateInSeconds() const;

    /** Updates combo box with categories from database.
     *
     */
    void addCategoriesToUI() const;

    /** Returns category id from Database.
     *
     */
    int getSelectedCategoryId() const;
};

#endif // NEWTRANSACTION_DIALOG_H
