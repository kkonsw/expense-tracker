#include <catch2/catch.hpp>
#include "db/db_manager.h"
#include "db/database.h"

TEST_CASE("Create db manager", "[DBManager]")
{
    REQUIRE_NOTHROW(DBManager());
}

TEST_CASE("Get database from db manager", "[DBManager]")
{
    DBManager db_manager;
    Database *db = db_manager.getDatabase();
    REQUIRE_NOTHROW(db->sync_schema());
}

TEST_CASE("Get table names from database", "[DBManager]")
{
    DBManager db_manager;
    Database *db = db_manager.getDatabase();

    auto tables = db->table_names();
    std::sort(tables.begin(), tables.end());
    REQUIRE(tables.size() == 4);
    REQUIRE(tables[0] == "categories");
    REQUIRE(tables[1] == "sqlite_sequence");
    REQUIRE(tables[2] == "transactions");
    REQUIRE(tables[3] == "users");
}
