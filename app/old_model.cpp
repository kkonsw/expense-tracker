#include "old_model.h"
#include "database.h"

#include <QDebug>

OldModel::OldModel(Database *db, QObject *parent)
    : QAbstractTableModel(parent),
      transactions(db)
{

}

QVariant OldModel::headerData(int section, Qt::Orientation orientation,
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

bool OldModel::setHeaderData(int section, Qt::Orientation orientation,
                                     const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int OldModel::rowCount(const QModelIndex &parent) const
{
    return transactions.size();
}

int OldModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant OldModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
           return QString("Row%1, Column%2")
                       .arg(index.row() + 1)
                       .arg(index.column() +1);

    return QVariant();
}

bool OldModel::setData(const QModelIndex &index, const QVariant &value,
                               int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags OldModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool OldModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool OldModel::insertColumns(int column, int count,
                                     const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
}

bool OldModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

bool OldModel::removeColumns(int column, int count,
                                     const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
}

void OldModel::createTestingData()
{
    qDebug() << "Removing all transactions from database";
    transactions.removeAll();

    qDebug() << "Creating transactions";
    Transaction transaction1({-1, 1, 664416000, 1.11, "test1"});
    Transaction transaction2({-1, 2, 664416000, 1.12, "test2"});
    Transaction transaction3({-1, 3, 664416000, 1.13, "test3"});
    transactions.add(transaction1);
    transactions.add(transaction2);
}