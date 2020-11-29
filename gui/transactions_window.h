#ifndef TRANSACTIONS_WINDOW_H
#define TRANSACTIONS_WINDOW_H

#include <QWidget>
#include <QtSql/QSqlDatabase>

#include "transactions_model.h"

namespace Ui {
class TransactionsWindow;
}

class TransactionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionsWindow(QSqlDatabase db, QWidget *parent = nullptr);
    ~TransactionsWindow();

    void updateModel();

private:
    Ui::TransactionsWindow *ui;
    std::unique_ptr<TransactionsModel> model;
};

#endif // TRANSACTIONS_WINDOW_H
