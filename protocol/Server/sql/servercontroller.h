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
#include "transaction.h"
#include <QDebug>
#include <QPair>

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

    /// <status, role>
    QPair<int, int> authorization(QString login, QString pass);
    Child getFullChildInfo(QString login);
    QVector<ScheduleElement> getSchedule(QString login, QDateTime from, QDateTime to);
    void updateCash(QString login, int value, double latitude, double longitude, QString description);
    void updateCash(QString login, int value);
    QVector<Transaction> getTransactions(QString login);
};

#endif // SERVERCONTROLLER_H
