#ifndef TRANSACTIONS_MODEL_H
#define TRANSACTIONS_MODEL_H

#include <QSqlRelationalTableModel>
#include <QSqlDatabase>

class TransactionsModel : public QSqlRelationalTableModel
{
public:
    TransactionsModel(QSqlDatabase *db);
    ~TransactionsModel();
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
                                          int role) const override;

private:
    void CreateTestData();
};

#endif // TRANSACTIONS_MODEL_H
