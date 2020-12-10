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
    Database* db = DBManager::getDatabase();
    REQUIRE_NOTHROW(UserTable(db));
}

class UserTableFixture
{
public:
    UserTableFixture():
        db(DBManager::getDatabase()),
        users(std::make_unique<UserTable>(UserTable(db))),
        user({-1, "John Doe"})
    {
        // clear database
        db->remove_all<Transaction>();
        db->remove_all<User>();
    }

protected:
    Database* db;
    std::unique_ptr<UserTable> users;
    User user;
};

TEST_CASE_METHOD(UserTableFixture, "Get all users from users table",
                 "[User Table]")
{
    auto all_users = users->getAll();
    REQUIRE(all_users.size() == 0);

    auto id = users->add(user);
    all_users = users->getAll();
    REQUIRE(id >= 0);
    REQUIRE(all_users.size() == 1);
}

TEST_CASE_METHOD(UserTableFixture, "Remove all users from users table",
                 "[User Table]")
{
    users->removeAll();
    REQUIRE(users->size() == 0);
}

TEST_CASE_METHOD(UserTableFixture, "Add and Remove user from users table",
                 "[User Table]")
{
    auto id = users->add(user);
    auto all_users = users->getAll();
    REQUIRE(id >= 0);
    REQUIRE(all_users.size() == 1);
    REQUIRE(users->size() == 1);

    users->remove(id);
    REQUIRE(users->size() == 0);
}

TEST_CASE_METHOD(UserTableFixture, "Remove non-existent user from users table",
                 "[User Table]")
{
    REQUIRE(users->size() == 0);

    int id = 1;
    REQUIRE_NOTHROW(users->remove(id));
}

TEST_CASE_METHOD(UserTableFixture,"Get non-existent user returns nullptr",
                 "[User Table]")
{
    REQUIRE(users->size() == 0);

    int id = 1;
    REQUIRE(users->get(id) == nullptr);
}

TEST_CASE_METHOD(UserTableFixture, "Get existing user", "[User Table]")
{
    auto id = users->add(user);
    auto user_ptr = users->get(id);
    REQUIRE(user_ptr != nullptr);
    REQUIRE(user_ptr->id == id);
    REQUIRE(user_ptr->name == "John Doe");
}

TEST_CASE_METHOD(UserTableFixture, "Get existing user ID from name",
                 "[User Table]")
{
    auto id = users->add(user);
    auto idFromName = users->getIdFromName(user.name);
    REQUIRE(id == idFromName);
}

TEST_CASE_METHOD(UserTableFixture, "Get non-existing user ID from name returns invalid ID",
                 "[User Table]")
{
    auto idFromName = users->getIdFromName(user.name);
    REQUIRE(idFromName == users->invalidID);
}

