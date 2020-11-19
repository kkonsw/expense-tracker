#include <catch2/catch.hpp>
#include "db/dbmanager.h"
#include "db/database.h"

TEST_CASE("Create DB Manager", "[DBManager]")
{
    REQUIRE_NOTHROW(DBManager());
}

TEST_CASE("Get Database from DB Manager", "[DBManager]")
{
    DBManager DBManager;
    Database *db = DBManager.GetDatabase();
    REQUIRE_NOTHROW(db->sync_schema());
}

TEST_CASE("Get Table Names From Database", "[DBManager]")
{
    DBManager DBManager;
    Database *db = DBManager.GetDatabase();
    auto tables = db->table_names();
    INFO("Number of tables - " << tables.size());
    INFO("Table names - " << tables[0] << ", " << tables[1])
    REQUIRE(tables.size() == 2);
    REQUIRE(tables[0] == "users");
    REQUIRE(tables[1] == "sqlite_sequence");
}
