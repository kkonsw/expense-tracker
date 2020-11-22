#ifndef TRANSACTIONTABLE_H
#define TRANSACTIONTABLE_H

#include "database.h"
#include "table.h"


class TransactionTable : public Table<Transaction>
{
public:
    TransactionTable() = delete;
    TransactionTable(Database* database);
    ~TransactionTable();
};

#endif // TRANSACTIONTABLE_H
