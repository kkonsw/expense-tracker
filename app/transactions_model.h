#ifndef TRANSACTIONS_MODEL_H
#define TRANSACTIONS_MODEL_H

#include <QSqlRelationalTableModel>
#include <QSqlDatabase>

class TransactionsModel : public QSqlRelationalTableModel
{
public:
    TransactionsModel(QSqlDatabase *db);
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

private:
    void CreateTestData();
};

#endif // TRANSACTIONS_MODEL_H
