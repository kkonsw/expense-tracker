#ifndef TRANSACTIONS_WINDOW_H
#define TRANSACTIONS_WINDOW_H

#include <QWidget>
#include "transaction_model.h"

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
    TransactionModel model;
};

#endif // TRANSACTIONS_WINDOW_H
