#ifndef TABLE_H
#define TABLE_H

#include "database.h"

template <typename T>
class Table
{
public:
    Table() = delete;
    Table(Database *database);
    virtual ~Table();

    /** Adds row to table. Returns id from database.
     *
     */
    virtual int add(const T& row);

    /** Removes row from table.
     *
     */
    virtual void remove(int id);

    /** Returns row with requested id from table.
     *  Returns nullptr if row with requested id is not found.
     */
    virtual std::unique_ptr<T> get(int id) const;

    /** Removes all rows from table.
     *
     */
    virtual void remove_all();

    /** Returns all rows from table.
     *
     */
    virtual std::vector<T> get_all() const;

protected:
    Database* db;
};

template <typename T>
Table<T>::Table(Database *database):
    db(database)
{
    if (db == nullptr)
    {
        throw std::runtime_error("Database is not initialized!");
    }
}

template <typename T>
Table<T>::~Table()
{

}

template <typename T>
int Table<T>::add(const T &row)
{
    int id = db->insert(row);
    return id;
}

template <typename T>
void Table<T>::remove(int id)
{
    db->remove<T>(id);
}

template <typename T>
std::unique_ptr<T> Table<T>::get(int id) const
{
    return db->get_pointer<T>(id);
}

template <typename T>
void Table<T>::remove_all()
{
    db->remove_all<T>();
}

template <typename T>
std::vector<T> Table<T>::get_all() const
{
    return db->get_all<T>();
}

#endif // TABLE_H
