#include "newtransaction_dialog.h"
#include "ui_newtransaction_dialog.h"
#include "transactions_window.h"

#include <QDebug>
#include <QSqlDatabase>

NewTransactionDialog::NewTransactionDialog(Database *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTransactionDialog),
    db(db),
    w(nullptr)
{
    if (db == nullptr)
    {
        throw std::runtime_error("Database is not initialized!");
    }

    ui->setupUi(this);
    connect(ui->button_allTransactions, SIGNAL(clicked()), this,
            SLOT(viewAllTransactions()));
    this->setFixedSize(400, 200);
}

NewTransactionDialog::~NewTransactionDialog()
{
    delete ui;
    if (w == nullptr)
    {
        delete w;
    }
}

void NewTransactionDialog::viewAllTransactions()
{
    if (w == nullptr)
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("db.sqlite");
        db.open();
        w = new TransactionsWindow(db);
    }
    w->show();
}
