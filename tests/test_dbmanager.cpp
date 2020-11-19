#include <catch2/catch.hpp>
#include "db/db_manager.h"
#include "db/database.h"

TEST_CASE("Create DB Manager", "[DBManager]")
{
    REQUIRE_NOTHROW(DBManager());
}

TEST_CASE("Get Database from DB Manager", "[DBManager]")
{
    DBManager db_manager;
    Database *db = db_manager.get_database();
    REQUIRE_NOTHROW(db->sync_schema());
}

TEST_CASE("Get Table Names From Database", "[DBManager]")
{
    DBManager db_manager;
    Database *db = db_manager.get_database();
    auto tables = db->table_names();
    INFO("Number of tables - " << tables.size());
    INFO("Table names - " << tables[0] << ", " << tables[1])
    REQUIRE(tables.size() == 2);
    REQUIRE(tables[0] == "users");
    REQUIRE(tables[1] == "sqlite_sequence");
}
