#include <catch2/catch.hpp>
#include "db/dbmanager.h"
#include "db/database.h"
#include "db/user_table.h"

TEST_CASE("Create User Table Without Database Throws", "[User Table]")
{
    REQUIRE_THROWS(UserTable(nullptr));
}

TEST_CASE("Create User Table With Valid Database", "[User Table]")
{
    DBManager dbmanager;
    Database* db = dbmanager.GetDatabase();
    REQUIRE_NOTHROW(UserTable(db));
}

TEST_CASE("Add user to User Table", "[User Table]")
{
    DBManager dbmanager;
    Database* db = dbmanager.GetDatabase();
    auto users = UserTable(db);
    User user{-1, "Jonh", "Doe"};
    auto id = users.AddUser(user);

    REQUIRE(id >= 0);
    db->remove<User>(id);
}

TEST_CASE("Remove user from User Table", "[User Table]")
{
    DBManager dbmanager;
    Database* db = dbmanager.GetDatabase();
    auto users = UserTable(db);
    User user{-1, "Jonh", "Doe"};
    auto id = users.AddUser(user);

    auto all_users = db->get_all<User>();
    REQUIRE(id >= 0);
    REQUIRE(all_users.size() == 1);
    users.RemoveUser(id);
    all_users = db->get_all<User>();
    REQUIRE(all_users.size() == 0);
}
