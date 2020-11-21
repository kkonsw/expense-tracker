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
    Database *db = db_manager.get_database();
    REQUIRE_NOTHROW(db->sync_schema());
}

TEST_CASE("Get table names from database", "[DBManager]")
{
    DBManager db_manager;
    Database *db = db_manager.get_database();

    auto tables = db->table_names();
    std::sort(tables.begin(), tables.end());
    REQUIRE(tables.size() == 3);
    REQUIRE(tables[0] == "sqlite_sequence");
    REQUIRE(tables[1] == "transactions");
    REQUIRE(tables[2] == "users");
}
