#include "transactions_window.h"
#include "ui_transactions_window.h"

TransactionsWindow::TransactionsWindow(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionsWindow),
    model(new TransactionsModel(db))
{
    ui->setupUi(this);
    this->setWindowTitle("All Transactions");
    this->setFixedSize(600, 300);

    // set up table
    ui->tableView->setModel(model.get());
    ui->tableView->horizontalHeader()->setSectionResizeMode(
                QHeaderView::Stretch);
    ui->tableView->hideColumn(0);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
}
