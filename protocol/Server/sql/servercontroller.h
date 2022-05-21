#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H
#include <QVariant>
#define ivalue(a) query.value(a).toInt()
#define svalue(a) query.value(a).toString()
#define tostr(a) QString::number(a)

#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include "locationlog.h"
#include "child.h"
#include "scheduleelement.h"
#include <QDebug>

class ServerController
{
private:
    QSqlDatabase db;
    static ServerController* instance;
    bool startServer();
public:
    ServerController();
    ///Паерн синглтон
    static ServerController * getInstance();
    int getLastId(QString table, QString column, QString where="");
    void addLocationLog(QString login, double latitude, double longitude);
    QVector<LocationLog> getLocationLog(QString login);
    QVector<LocationLog> getLocationLog(QString login, QDateTime from, QDateTime to);

    QVector<ScheduleElement> getSchedule(QString login);
    Child getChildInfo(QString login);

    void prikol(QString login);
};

#endif // SERVERCONTROLLER_H
