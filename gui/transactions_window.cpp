#include "transactions_window.h"
#include "ui_transactions_window.h"

TransactionsWindow::TransactionsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionsWindow)
{
    ui->setupUi(this);
    this->setFixedSize(400, 200);
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
}
