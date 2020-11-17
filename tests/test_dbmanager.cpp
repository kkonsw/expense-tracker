#include <catch2/catch.hpp>
#include "dbmanager.h"

TEST_CASE("Create DB Manager", "[DBManager]")
{
    REQUIRE_NOTHROW(DBManager());
}
