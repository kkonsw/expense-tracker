#include "transactions_window.h"
#include "ui_transactions_window.h"

TransactionsWindow::TransactionsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionsWindow)
{
    ui->setupUi(this);

    this->setFixedSize(400, 200);
    ui->tableView->setModel(&model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
}
