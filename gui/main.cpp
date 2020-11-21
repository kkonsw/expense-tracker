#include "main_window.h"
#include "transactions_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TransactionsWindow w;
    w.show();
    return a.exec();
}
