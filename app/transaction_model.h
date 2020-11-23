#ifndef TRANSACTIONMODEL_H
#define TRANSACTIONMODEL_H

#include <QAbstractTableModel>
#include "db/transaction_table.h"
#include "db/database.h"

class TransactionModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TransactionModel(Database *db = nullptr,
                              QObject *parent = nullptr);

    // Header
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    // Editable
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data
    bool insertRows(int row, int count,
                    const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count,
                       const QModelIndex &parent = QModelIndex()) override;

    // Remove data
    bool removeRows(int row, int count,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count,
                       const QModelIndex &parent = QModelIndex()) override;

    // Create Data For Testing
    void createTestingData();

private:
    TransactionTable transactions;
};

#endif // TRANSACTIONMODEL_H
