#include "transactions_window.h"
#include "ui_transactions_window.h"
#include "message_dialog.h"
#include "db/db_manager.h"
#include "style.h"

#include <QDebug>

TransactionsWindow::TransactionsWindow(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionsWindow),
    model(new TransactionsModel(db)),
    transactions(std::make_unique<TransactionTable>(DBManager::getDatabase())),
    categories(std::make_unique<CategoryTable>(DBManager::getDatabase()))
{
    ui->setupUi(this);
    this->setWindowTitle("All Transactions");
    this->setFixedSize(600, 800);

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
    auto total =  transactions->getTotalAmount();
    auto max = transactions->getMaxAmount();
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
    setCategoryFilter();
    update();
}

void TransactionsWindow::addCategoriesToUI()
{
    auto cat_names = categories->getAll();
    for (const auto& cat : cat_names) {
        ui->comboBox_category->addItem(QString::fromUtf8(cat.cat_name.c_str()));
    }
}

void TransactionsWindow::setCategoryFilter()
{
    QString cat_name = ui->comboBox_category->currentText();
    if (cat_name == "All Categories") {
        model->setFilter("");
        return;
    }
    auto cat_id = categories->getIdFromName(cat_name.toStdString());
    QString filter = QString("cat_id='%1'").arg(QString::number(cat_id));
    model->setFilter(filter);
}
