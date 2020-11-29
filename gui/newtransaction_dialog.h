#ifndef NEWTRANSACTION_DIALOG_H
#define NEWTRANSACTION_DIALOG_H

#include <QDialog>
#include <QString>

#include "db/database.h"
#include "transactions_window.h"

namespace Ui {
class NewTransactionDialog;
}

class NewTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTransactionDialog(Database *db, QWidget *parent = nullptr);
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

    /** Removes all Transactions from Database.
     *
     */
    void clearTransactions();

private:
    Ui::NewTransactionDialog *ui;
    Database *db;
    TransactionsWindow* w;

    /** User Id for new Transactions.
     *
     */
    int userId = 1;

    /** Creates new Transaction with data provided by user.
     *
     */
    bool createNewTransaction(Transaction &transaction);

    /** Validates Transaction amount from user input.
     *
     */
    bool checkTransactionAmount(QString& amount) const;

    /** Returns date in seconds for Database.
     *
     */
    int getDateInSeconds() const;
};

#endif // NEWTRANSACTION_DIALOG_H
