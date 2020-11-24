#ifndef TRANSACTIONS_WINDOW_H
#define TRANSACTIONS_WINDOW_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRelationalTableModel>

namespace Ui {
class TransactionsWindow;
}

class TransactionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionsWindow(QWidget *parent = nullptr,
                                QSqlDatabase *db = nullptr);
    ~TransactionsWindow();

private:
    Ui::TransactionsWindow *ui;
    std::unique_ptr<QSqlRelationalTableModel> model;

    void createTestData();
};

#endif // TRANSACTIONS_WINDOW_H
