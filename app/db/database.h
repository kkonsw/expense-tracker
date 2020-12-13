#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite_orm.h"

struct User
{
    int id;
    std::string name;
};

struct Transaction
{
    int id;
    std::unique_ptr<int> user_id;
    int date;
    double amount;
    std::unique_ptr<int> cat_id;
    std::string note;
};

enum class TransactionHeaders {
        Id,
        Person,
        Date,
        Amount,
        Category,
        Note
};

struct Category
{
    int id;
    std::string cat_name;
};

struct SubCategory
{
    int id;
    std::unique_ptr<int> cat_id;
    std::string subcat_name;
};

using namespace sqlite_orm;

inline auto init_storage(const std::string &path = "db.sqlite")
{
    return make_storage(path,
                        make_table("users",
                                   make_column("id", &User::id, autoincrement(),
                                               primary_key()),
                                   make_column("name", &User::name)),
                        make_table("transactions",
                                   make_column("id", &Transaction::id,
                                               autoincrement(), primary_key()),
                                   make_column("user_id", &Transaction::user_id),
                                   make_column("date", &Transaction::date),
                                   make_column("amount", &Transaction::amount),
                                   make_column("cat_id", &Transaction::cat_id),
                                   make_column("note", &Transaction::note),
                                   foreign_key(&Transaction::user_id).references(&User::id),
                                   foreign_key(&Transaction::cat_id).references(&Category::id)),
                        make_table("categories",
                                   make_column("id", &Category::id,
                                               autoincrement(), primary_key()),
                                   make_column("cat_name", &Category::cat_name)),
                        make_table("subcategories",
                                   make_column("id", &SubCategory::id,
                                               autoincrement(), primary_key()),
                                   make_column("cat_id", &SubCategory::cat_id),
                                   make_column("subcat_name", &SubCategory::subcat_name),
                                   foreign_key(&SubCategory::cat_id).references(&Category::id)));
}

using Database = decltype(init_storage());

#endif // DATABASE_H
