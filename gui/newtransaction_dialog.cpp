#include "newtransaction_dialog.h"
#include "ui_newtransaction_dialog.h"
#include "transactions_window.h"
#include "message_dialog.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QDoubleValidator>
#include <QDate>

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
    this->setFixedSize(300, 350);
    this->setWindowTitle("New Transaction");

    connect(ui->button_allTransactions, SIGNAL(clicked()), this,
            SLOT(viewAllTransactions()));
    connect(ui->button_addTransaction, SIGNAL(clicked()), this,
            SLOT(addTransaction()));
    ui->dateEdit->setDate(QDate::currentDate());
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

void NewTransactionDialog::addTransaction()
{
    Transaction transaction;
    if (createNewTransaction(transaction))
    {
    }
}

bool NewTransactionDialog::createNewTransaction(const Transaction &transaction)
{
    auto date = ui->dateEdit->date();
    auto amount = ui->lineEdit_amount->text();
    if (!checkTransactionAmount(amount))
    {
        MessageDialog::information(this, "Incorrect amount!");
    }

    return false;
}

bool NewTransactionDialog::checkTransactionAmount(const QString &amount)
{
    return false;
}
