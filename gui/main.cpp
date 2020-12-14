#include "transactions_window.h"
#include "newtransaction_dialog.h"
#include "db/db_manager.h"
#include "db/data.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NewTransactionDialog dialog;
    dialog.show();

    return a.exec();
}
