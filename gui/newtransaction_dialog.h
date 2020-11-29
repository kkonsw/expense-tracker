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
    /** Opens new window with all transacions.
     *
     */
    void viewAllTransactions();

    /** Adds new Transaction to Database.
     *
     */
    void addTransaction();

private:
    Ui::NewTransactionDialog *ui;
    Database *db;
    TransactionsWindow* w;

    /** Creates new Transaction with data provided by user.
     *
     */
    bool createNewTransaction(const Transaction &transaction);

    /** Validates Transaction amount from user input.
     *
     */
    bool checkTransactionAmount(const QString& amount);
};

#endif // NEWTRANSACTION_DIALOG_H
