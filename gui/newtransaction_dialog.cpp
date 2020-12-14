#include "newtransaction_dialog.h"
#include "ui_newtransaction_dialog.h"
#include "transactions_window.h"
#include "message_dialog.h"
#include "db/db_manager.h"
#include "style.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QDoubleValidator>
#include <QCalendarWidget>
#include <QDateTime>
#include <QDate>
#include <QString>

NewTransactionDialog::NewTransactionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTransactionDialog),
    w(nullptr),
    users(std::make_unique<UserTable>(DBManager::getDatabase())),
    transactions(std::make_unique<TransactionTable>(DBManager::getDatabase())),
    categories(std::make_unique<CategoryTable>(DBManager::getDatabase())),
    userName("Kuznetsov Konstantin")
{
    ui->setupUi(this);
    this->setFixedSize(300, 350);
    this->setWindowTitle("New Transaction");
    Style::changeQDateEditStyleSheet(ui->dateEdit);
    ui->dateEdit->setDate(QDate::currentDate());
    addCategoriesToUI();

    connect(ui->button_allTransactions, SIGNAL(clicked()), this,
            SLOT(viewAllTransactions()));
    connect(ui->button_addTransaction, SIGNAL(clicked()), this,
            SLOT(addTransaction()));
    connect(ui->comboBox_category, SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(updateSubcategories(const QString&)));
}

NewTransactionDialog::~NewTransactionDialog()
{
    delete ui;
    if (w != nullptr)
    {
        delete w;
    }
}

void NewTransactionDialog::viewAllTransactions()
{
    if (w == nullptr)
    {
        QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("db.sqlite");
        database.open();
        w = new TransactionsWindow(database);
    }
    w->update();
    w->show();
}

void NewTransactionDialog::addTransaction()
{
    Transaction transaction;
    if (createNewTransaction(transaction))
    {
        transactions->add(transaction);
    }
}

void NewTransactionDialog::updateSubcategories(const QString& category)
{
    ui->comboBox_subcategory->clear();
    ui->comboBox_subcategory->addItem("Select subcategory");

//    auto cat_names = categories->getAll();
//    for (const auto& cat : cat_names) {
//        ui->comboBox_category->addItem(QString::fromUtf8(cat.cat_name.c_str()));
//    }
}

int NewTransactionDialog::getUserIdFromDatabase()
{
    auto id = users->getIdFromName(userName);
    if (id == users->invalidID) {
        throw::std::runtime_error("User not found in database!");
    }

    return id;
}

bool NewTransactionDialog::createNewTransaction(Transaction &transaction)
{
    auto amount = ui->lineEdit_amount->text();
    if (!checkTransactionAmount(amount))
    {
        MessageDialog::information(this, "Incorrect amount!");
        return false;
    }
    if (ui->comboBox_category->currentIndex() == 0)
    {
        MessageDialog::information(this, "Select category!");
        return false;
    }

    transaction.user_id = std::make_unique<int>(getUserIdFromDatabase());
    transaction.date = getDateInSeconds();
    transaction.amount = amount.toDouble();
    transaction.cat_id = std::make_unique<int>(getSelectedCategoryId());
    transaction.subcat_id = nullptr;
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
    int seconds = date.startOfDay().toSecsSinceEpoch();
    return seconds;
}

void NewTransactionDialog::addCategoriesToUI() const
{
    auto cat_names = categories->getAll();
    for (const auto& cat : cat_names) {
        ui->comboBox_category->addItem(QString::fromUtf8(cat.cat_name.c_str()));
    }
}

int NewTransactionDialog::getSelectedCategoryId() const
{
    auto cat_name = ui->comboBox_category->currentText().toStdString();
    auto id = categories->getIdFromName(cat_name);

    if (id == categories->invalidID) {
        throw::std::runtime_error("Category not found in database!");
    }

    return id;
}
