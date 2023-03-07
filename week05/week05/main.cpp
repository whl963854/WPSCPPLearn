#include "lotteryticket.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LotteryTicket w;
    w.show();

    return a.exec();
}
