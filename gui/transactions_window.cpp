#include "transactions_window.h"
#include "ui_transactions_window.h"

TransactionsWindow::TransactionsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionsWindow),
    db_manager(DBManager()),
    model(db_manager.get_database())
{
    ui->setupUi(this);

    this->setFixedSize(400, 200);

    model.CreateTestingData();
    ui->tableView->setModel(&model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
}
