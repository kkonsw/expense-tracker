#include "transactions_window.h"
#include "ui_transactions_window.h"
#include "message_dialog.h"
#include "db/db_manager.h"

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
    this->setFixedSize(600, 300);

    connect(ui->button_clearTransactions, SIGNAL(clicked()), this,
            SLOT(clearTransactions()));

    // set up table
    ui->tableView->setModel(model.get());
    ui->tableView->horizontalHeader()->setSectionResizeMode(
                QHeaderView::Stretch);
    ui->tableView->hideColumn(0);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSortingEnabled(true);
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
}

void TransactionsWindow::update()
{
    model->select();

    auto total_expenses = getTotalExpenses();
    ui->label_totalExpenses->setText("Total Expenses: "
                                     + QString::number(total_expenses, 'f', 2));
}

double TransactionsWindow::getTotalExpenses() const
{
    auto query = db->prepare(select(&Transaction::amount));
    auto expenses = db->execute(query);
    return std::accumulate(expenses.begin(), expenses.end(), 0.0);
}

void TransactionsWindow::clearTransactions()
{
    MessageDialog::information(this, "All Transactions were removed!");
    db->remove_all<Transaction>();
    update();
}
