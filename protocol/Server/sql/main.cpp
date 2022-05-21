#include <QCoreApplication>
#include "servercontroller.h"
#include <QTimeZone>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerController* server = ServerController::getInstance();
    //server->addLocationLog("maksim", 54, 566);
    //QVector<LocationLog> test =  server->getLocationLog("maksim", QDateTime(QDate(2022,5,20), QTime(23,20)), QDateTime(QDate(2022,5,21), QTime(0,50)));

    //QVector<ScheduleElement> sc = server->getSchedule("maksim");
    //server->getChildInfo("maksim");

//    auto a1 = server->authorization("maksim", "123");
//    auto a2 = server->authorization("maksim1", "123");
//    auto a3 = server->authorization("maksim", "1234");
    //Child c = server->getFullChildInfo("maksim");
   //QVector<ScheduleElement> sc = server->getSchedule("maksim", QDateTime(QDate(2022,05,19)),QDateTime(QDate(2022,05,25)));

   server->updateCash("maksim", -228, 188,56,"vo prikol");

    //QVector<Transaction>test = server->getTransactions("maksim");
      return a.exec();
}
