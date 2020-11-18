#ifndef USER_H
#define USER_H

#include "database.h"


class UserTable
{
public:
    UserTable();

private:
    Database* db;
};

#endif // USER_H
