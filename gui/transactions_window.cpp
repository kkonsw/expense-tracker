#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>
#include "transactions_window.h"
#include "ui_transactions_window.h"

TransactionsWindow::TransactionsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionsWindow)
{
    ui->setupUi(this);
    this->setFixedSize(400, 200);

    connectToDatabase();
    model = std::make_unique<QSqlRelationalTableModel>(
                new QSqlRelationalTableModel(nullptr, db));
    model->setTable("transactions");
    createTestData();

    ui->tableView->setModel(model.get());
    ui->tableView->horizontalHeader()->setSectionResizeMode(
                QHeaderView::Stretch);
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
    db.close();
}

void TransactionsWindow::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    db.open();
}

void TransactionsWindow::createTestData()
{
//    model->removeRows(0, model->rowCount());

    int rows = 2;
    QSqlRecord record = model->record();
    for (int i = 0; i < rows; ++i)
    {
        record.setValue("user_id", i);
        record.setValue("date", 664416000);
        record.setValue("amount", double(i));
        record.setValue("note", "test");
        model->insertRecord(-1, record);
    }
    model->submitAll();
    model->select();
}
