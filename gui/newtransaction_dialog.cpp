#include "newtransaction_dialog.h"
#include "ui_newtransaction_dialog.h"
#include "transactions_window.h"
#include "message_dialog.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QDoubleValidator>
#include <QDateTime>
#include <QDate>
#include <QString>

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
    connect(ui->button_clearTransactions, SIGNAL(clicked()), this,
            SLOT(clearTransactions()));
    ui->dateEdit->setDate(QDate::currentDate());
    addCategoriesToUI();
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
    w->updateModel();
    w->show();
}

void NewTransactionDialog::addTransaction()
{
    Transaction transaction;
    if (createNewTransaction(transaction))
    {
        db->insert<Transaction>(transaction);
    }
}

bool NewTransactionDialog::createNewTransaction(Transaction &transaction)
{
    auto amount = ui->lineEdit_amount->text();
    if (!checkTransactionAmount(amount))
    {
        MessageDialog::information(this, "Incorrect amount!");
        return false;
    }
    if (ui->comboBox->currentIndex() == 0)
    {
        MessageDialog::information(this, "Select category!");
        return false;
    }

    transaction.user_id = std::make_unique<int>(userId);
    transaction.date = getDateInSeconds();
    transaction.amount = amount.toDouble();
    transaction.cat_id = std::make_unique<int>(getSelectedCategoryId());
    transaction.note = ui->lineEdit_note->text().toStdString();

    return true;
}

bool NewTransactionDialog::checkTransactionAmount(QString &amount) const
{
    QDoubleValidator validator;
    validator.setBottom(0.0);
    validator.setTop(1000000);

    int pos = 0;
    if (validator.validate(amount, pos) == QValidator::Acceptable)
    {
        return true;
    }

    return false;
}

int NewTransactionDialog::getDateInSeconds() const
{
    auto date = ui->dateEdit->date();
    int seconds = QDate(date).startOfDay().toSecsSinceEpoch();
    return seconds;
}

std::vector<Category> NewTransactionDialog::getCategoriesFromDatabase() const
{
    return db->get_all<Category>();
}

void NewTransactionDialog::addCategoriesToUI() const
{
    auto categories = getCategoriesFromDatabase();
    for (const auto& cat : categories) {
        ui->comboBox->addItem(QString::fromUtf8(cat.cat_name.c_str()));
    }
}

int NewTransactionDialog::getSelectedCategoryId() const
{
    auto cat_name = ui->comboBox->currentText().toStdString();
    auto categories = db->get_all<Category>(where(c(&Category::cat_name)
                                                  == cat_name));

    if (categories.empty()) {
        throw::std::runtime_error("Category not found in database!");
    }

    return categories.begin()->id;
}

void NewTransactionDialog::clearTransactions()
{

    MessageDialog::information(this, "All Transactions were removed!");
    db->remove_all<Transaction>();
}
