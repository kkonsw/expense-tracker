#include "transaction_table.h"

#include <numeric>

TransactionTable::TransactionTable(Database *database):
    Table(database)
{

}

TransactionTable::~TransactionTable()
{

}

double TransactionTable::getTotalAmount() const
{
    auto query = db->prepare(select(&Transaction::amount));
    auto expenses = db->execute(query);
    if (!expenses.empty())
    {
        return std::accumulate(expenses.begin(), expenses.end(), 0.0);
    }
    return 0.0;
}

double TransactionTable::getMaxAmount() const
{
    auto query = db->prepare(select(&Transaction::amount));
    auto expenses = db->execute(query);
    if (!expenses.empty())
    {
        return *std::max_element(expenses.begin(), expenses.end());
    }
    return 0.0;
}
