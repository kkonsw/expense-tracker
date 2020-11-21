#include <catch2/catch.hpp>
#include "db/db_manager.h"
#include "db/database.h"
#include "db/user_table.h"

TEST_CASE("Create users table without database throws", "[User Table]")
{
    REQUIRE_THROWS(UserTable(nullptr));
}

TEST_CASE("Create users table with valid database", "[User Table]")
{
    DBManager db_manager;
    Database* db = db_manager.get_database();
    REQUIRE_NOTHROW(UserTable(db));
}

TEST_CASE("Get all users from users table", "[User Table]")
{
    DBManager db_manager;
    Database* db = db_manager.get_database();
    auto users = UserTable(db);
    users.remove_all_users();

    auto all_users = users.get_all_users();
    REQUIRE(all_users.size() == 0);

    User user{-1, "John", "Doe"};
    auto id = users.add_user(user);
    all_users = users.get_all_users();
    REQUIRE(id >= 0);
    REQUIRE(all_users.size() == 1);
}

TEST_CASE("Remove all users from users table", "[User Table]")
{
    DBManager db_manager;
    Database* db = db_manager.get_database();
    auto users = UserTable(db);
    users.remove_all_users();

    auto all_users = users.get_all_users();
    REQUIRE(all_users.size() == 0);
}

TEST_CASE("Add and Remove user from users table", "[User Table]")
{
    DBManager db_manager;
    Database* db = db_manager.get_database();
    auto users = UserTable(db);
    users.remove_all_users();

    User user{-1, "John", "Doe"};
    auto id = users.add_user(user);
    auto all_users = users.get_all_users();
    REQUIRE(id >= 0);
    REQUIRE(all_users.size() == 1);

    users.remove_user(id);
    all_users = users.get_all_users();
    REQUIRE(all_users.size() == 0);
}

TEST_CASE("Remove non-existent user from users table", "[User Table]")
{
    DBManager db_manager;
    Database* db = db_manager.get_database();
    auto users = UserTable(db);
    users.remove_all_users();

    auto all_users = users.get_all_users();
    REQUIRE(all_users.size() == 0);

    int id = 1;
    REQUIRE_NOTHROW(users.remove_user(id));
}

TEST_CASE("Get non-existent user returns nullptr", "[User Table]")
{
    DBManager db_manager;
    Database* db = db_manager.get_database();
    auto users = UserTable(db);
    users.remove_all_users();

    auto all_users = users.get_all_users();
    REQUIRE(all_users.size() == 0);

    int id = 1;
    REQUIRE(users.get_user(id) == nullptr);
}

TEST_CASE("Get existing user", "[User Table]")
{
    DBManager db_manager;
    Database* db = db_manager.get_database();
    auto users = UserTable(db);
    users.remove_all_users();

    User user{-1, "John", "Doe"};
    auto id = users.add_user(user);
    auto user_ptr = users.get_user(id);
    REQUIRE(user_ptr != nullptr);
    REQUIRE(user_ptr->id == id);
    REQUIRE(user_ptr->first_name == "John");
    REQUIRE(user_ptr->last_name == "Doe");
}

