#include "transaction_model.h"
#include "database.h"

#include <QDebug>

TransactionModel::TransactionModel(Database *db, QObject *parent)
    : QAbstractTableModel(parent),
      transactions(db)
{

}

QVariant TransactionModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Person");
        case 1:
            return QString("Date");
        case 2:
            return QString("Amount");
        }
    }
    return QVariant();
}

bool TransactionModel::setHeaderData(int section, Qt::Orientation orientation,
                                     const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int TransactionModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 2;
}

int TransactionModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 3;
}

QVariant TransactionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
           return QString("Row%1, Column%2")
                       .arg(index.row() + 1)
                       .arg(index.column() +1);

    return QVariant();
}

bool TransactionModel::setData(const QModelIndex &index, const QVariant &value,
                               int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags TransactionModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool TransactionModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool TransactionModel::insertColumns(int column, int count,
                                     const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
}

bool TransactionModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

bool TransactionModel::removeColumns(int column, int count,
                                     const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
}

void TransactionModel::CreateTestingData()
{
    qDebug() << "Removing all transactions from database";
    transactions.remove_all();

    Transaction transaction1({-1, 1, 664416000, 1.11, "test1"});
    Transaction transaction2({-1, 1, 664416000, 1.12, "test2"});
    Transaction transaction3({-1, 1, 664416000, 1.13, "test3"});
    transactions.add(transaction1);
    transactions.add(transaction2);
    transactions.add(transaction3);
}
