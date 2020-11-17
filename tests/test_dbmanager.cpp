#include <catch2/catch.hpp>
#include "dbmanager.h"
#include "database.h"

TEST_CASE("Create DB Manager", "[DBManager]")
{
    REQUIRE_NOTHROW(DBManager());
}

TEST_CASE("Get Database", "[DBManager]")
{
    DBManager DBManager;
    Database *db = DBManager.GetDatabase();
    REQUIRE_NOTHROW(db->sync_schema());
}
