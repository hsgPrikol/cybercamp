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
    server->getChildInfo("maksim");
      return a.exec();
}
