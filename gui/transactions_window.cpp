#include "transactions_window.h"
#include "ui_transactions_window.h"
#include "message_dialog.h"
#include "db/db_manager.h"
#include "style.h"

#include <QDebug>
#include <algorithm>

TransactionsWindow::TransactionsWindow(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionsWindow),
    model(new TransactionsModel(db)),
    db(DBManager::getDatabase())
{
    if (this->db == nullptr)
    {
        throw std::runtime_error("Database is not initialized!");
    }

    ui->setupUi(this);
    this->setWindowTitle("All Transactions");
    this->setFixedSize(600, 600);

    // set up table
    ui->tableView->setModel(model.get());
    ui->tableView->horizontalHeader()->setSectionResizeMode(
                QHeaderView::Stretch);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(5);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSortingEnabled(true);

    addCategoriesToUI();
    Style::changeQDateEditStyleSheet(ui->dateEdit_start);
    Style::changeQDateEditStyleSheet(ui->dateEdit_end);
    ui->dateEdit_end->setDate(QDate::currentDate());

    connect(ui->button_clearTransactions, SIGNAL(clicked()), this,
            SLOT(clearTransactions()));
    connect(ui->button_applyFilters, SIGNAL(clicked()), this,
            SLOT(applyFilters()));
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
}

void TransactionsWindow::update()
{
    model->select();
    updateExpenseLabels();
}

void TransactionsWindow::updateExpenseLabels()
{
    auto query = db->prepare(select(&Transaction::amount));
    auto expenses = db->execute(query);
    auto total =  std::accumulate(expenses.begin(), expenses.end(), 0.0);
    auto max = *std::max_element(expenses.begin(), expenses.end());
    ui->label_totalExpensesVal->setText(QString::number(total, 'f', 2));
    ui->label_biggestExpenseVal->setText(QString::number(max, 'f', 2));
}

void TransactionsWindow::clearTransactions()
{
    MessageDialog::information(this, "All Transactions were removed!");
    db->remove_all<Transaction>();
    update();
}

void TransactionsWindow::applyFilters()
{
    qDebug("Apply filter");
}

void TransactionsWindow::addCategoriesToUI()
{
    auto categories = db->get_all<Category>();
    for (const auto& cat : categories) {
        ui->comboBox_category->addItem(QString::fromUtf8(cat.cat_name.c_str()));
    }
}
