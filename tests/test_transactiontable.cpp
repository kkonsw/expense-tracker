#include <catch2/catch.hpp>
#include "db/db_manager.h"
#include "db/database.h"
#include "db/transaction_table.h"

class TransactionTableFixture
{
public:
    TransactionTableFixture():
        db_manager(DBManager()),
        db(db_manager.getDatabase()),
        transactions(std::make_unique<TransactionTable>(TransactionTable(db))),
        transaction({-1, 1, 664416000, 1.11, "test"})
    {
        transactions->removeAll();
    }

protected:
    DBManager db_manager;
    Database* db;
    std::unique_ptr<TransactionTable> transactions;
    Transaction transaction;
};

TEST_CASE_METHOD(TransactionTableFixture, "Get existing transaction",
                 "[Transaction Table]")
{
    auto id = transactions->add(transaction);
    auto transaction_ptr = transactions->get(id);
    REQUIRE(transaction_ptr != nullptr);
    REQUIRE(transaction_ptr->id == id);
    REQUIRE(transaction_ptr->user_id == 1);
    REQUIRE(transaction_ptr->date == 664416000);
    REQUIRE(transaction_ptr->amount == 1.11);
    REQUIRE(transaction_ptr->note == "test");
}
TEST_CASE_METHOD(TransactionTableFixture, "Initial table size is zero",
                 "[Transaction Table]")
{
    REQUIRE(transactions->size() == 0);
}

TEST_CASE_METHOD(TransactionTableFixture, "Get table size",
                 "[Transaction Table]")
{
    transactions->add(transaction);
    transactions->add(transaction);
    transactions->add(transaction);
    REQUIRE(transactions->size() == 3);
}
