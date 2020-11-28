#ifndef NEWTRANSACTION_DIALOG_H
#define NEWTRANSACTION_DIALOG_H

#include <QDialog>

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
    void viewAllTransactions();

private:
    Ui::NewTransactionDialog *ui;
    Database *db;
    TransactionsWindow* w;
};

#endif // NEWTRANSACTION_DIALOG_H
