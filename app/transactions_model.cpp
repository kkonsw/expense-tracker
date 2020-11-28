#include "transactions_model.h"

#include <QSqlRecord>
#include <QDateTime>
#include <QDebug>


TransactionsModel::TransactionsModel(QSqlDatabase *db):
    QSqlRelationalTableModel(nullptr, *db)
{
    setTable("transactions");
    setRelation(1, QSqlRelation("users", "id", "first_name"));
    select();
}

TransactionsModel::~TransactionsModel()
{

}

QVariant TransactionsModel::data(const QModelIndex &index, int role) const
{
    if ((role == Qt::DisplayRole) && (index.column() == 2))
    {
        QVariant data = QSqlRelationalTableModel::data(index, role);
        int seconds = data.toInt();
        QDateTime dateTime;
        dateTime.setSecsSinceEpoch(seconds);
        return QVariant(dateTime.toString("d MMM yyyy, h:mm"));
    }

    return QSqlRelationalTableModel::data(index, role);
}

QVariant TransactionsModel::headerData(int section,
                                       Qt::Orientation orientation,
                                       int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Id");
        case 1:
            return QString("Person");
        case 2:
            return QString("Date");
        case 3:
            return QString("Amount");
        case 4:
            return QString("Note");
        }
    }

    return QSqlRelationalTableModel::headerData(section, orientation, role);
}
