#include "transactions_window.h"
#include "ui_transactions_window.h"
#include "message_dialog.h"
#include "db/db_manager.h"
#include "style.h"

#include <QDebug>
#include <QSqlQuery>

TransactionsWindow::TransactionsWindow(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionsWindow),
    model(new TransactionsModel(db)),
    transactions(std::make_unique<TransactionTable>(DBManager::getDatabase())),
    categories(std::make_unique<CategoryTable>(DBManager::getDatabase()))
{
    ui->setupUi(this);
    this->setWindowTitle("All Transactions");
    this->setFixedSize(900, 800);

    // set up table
    ui->tableView->setModel(model.get());
    ui->tableView->horizontalHeader()->setSectionResizeMode(
                QHeaderView::Stretch);
    ui->tableView->hideColumn(0);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSortingEnabled(true);

    addCategoriesToUI();
    Style::changeQDateEditStyleSheet(ui->dateEdit_start);
    Style::changeQDateEditStyleSheet(ui->dateEdit_end);
    ui->dateEdit_end->setDate(QDate::currentDate());

    connect(ui->button_clearTransactions, SIGNAL(clicked()), this,
            SLOT(removeTransactions()));
    connect(ui->button_applyFilters, SIGNAL(clicked()), this,
            SLOT(applyFilters()));
    connect(ui->button_removeSelected, SIGNAL(clicked()), this,
            SLOT(removeSelectedTransactions()));
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
    auto max = getMaxExpense();
    auto total = getTotalExpenses();
    ui->label_totalExpensesVal->setText(QString::number(total, 'f', 2));
    ui->label_biggestExpenseVal->setText(QString::number(max, 'f', 2));
}

void TransactionsWindow::removeTransactions()
{
    transactions->removeAll();
    MessageDialog::information(this, "All Transactions were removed!");
    update();
}

void TransactionsWindow::removeSelectedTransactions()
{
    auto selection = ui->tableView->selectionModel();
    auto selected = selection->selectedRows();
    for (const auto& index : selected) {
        model->removeRow(index.row());
    }
    model->submitAll();
    update();
}

void TransactionsWindow::applyFilters()
{
    auto category = getCategoryFilter();
    auto dates = getDatesFilter();
    auto filter = QString("%1 AND %2").arg(category).arg(dates);
    model->setFilter(filter);
    update();
}

void TransactionsWindow::addCategoriesToUI()
{
    auto cat_names = categories->getAll();
    for (const auto& cat : cat_names) {
        ui->comboBox_category->addItem(QString::fromUtf8(cat.cat_name.c_str()));
    }
}

QString TransactionsWindow::getCategoryFilter() const
{
    QString filter;
    QString cat_name = ui->comboBox_category->currentText();
    if (cat_name == "All Categories") {
        filter = "transactions.cat_id > 0";
        return filter;
    }
    auto cat_id = categories->getIdFromName(cat_name.toStdString());
    filter = QString("transactions.cat_id = %1").arg(QString::number(cat_id));
    return filter;
}

QString TransactionsWindow::getDatesFilter() const
{
    QString filter;
    auto start = ui->dateEdit_start->date();
    auto start_secs = start.startOfDay().toSecsSinceEpoch();
    auto end = ui->dateEdit_end->date();
    auto end_secs = end.endOfDay().toSecsSinceEpoch();

    filter = QString("transactions.date BETWEEN %1 AND %2").arg(start_secs).arg(end_secs);
    return filter;
}

double TransactionsWindow::getTotalExpenses() const
{
    double total = 0.0;
    auto column = TransactionHeaders::Amount;
    for (int row = 0; row < model->rowCount(); ++row) {
        auto index = model->index(row, static_cast<int>(column));
        total += model->data(index).toDouble();
    }
    return total;
}

double TransactionsWindow::getMaxExpense() const
{
    double max = 0.0;
    auto column = TransactionHeaders::Amount;
    for (int row = 0; row < model->rowCount(); ++row) {
        auto index = model->index(row, static_cast<int>(column));
        double expense = model->data(index).toDouble();
        if (expense > max) {
            max = expense;
        }
    }
    return max;
}
