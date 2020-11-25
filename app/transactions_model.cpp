#include "transactions_model.h"

#include <QSqlRecord>
#include <QDateTime>
#include <QDebug>


TransactionsModel::TransactionsModel(QSqlDatabase *db):
    QSqlRelationalTableModel(nullptr, *db)
{
    setTable("transactions");
    select();
}

QVariant TransactionsModel::data(const QModelIndex &index, int role) const
{
    return QSqlRelationalTableModel::data(index, role);
}

void TransactionsModel::CreateTestData()
{
    int rows = 2;
    QSqlRecord record = this->record();

    for (int i = 0; i < rows; ++i)
    {
        record.setValue("user_id", i);
        QDateTime timestamp = QDateTime::currentDateTime();
        int seconds = timestamp.toSecsSinceEpoch();
        record.setValue("date", seconds);
        record.setValue("amount", double(i));
        record.setValue("note", "test");
        insertRecord(-1, record);
    }
    submitAll();
    select();
}
