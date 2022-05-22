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
#include "child2.h"
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
    QList<QObject*> getLocationLog(QString login);
    QList<QObject*> getLocationLog(QString login, QDateTime from, QDateTime to);

    QList<QObject*> getSchedule(QString login);
    Child* getChildInfo(QString login);

    void prikol(QString login);

    /// <status, role>
    QPair<int, int> authorization(QString login, QString pass);
    Child* getFullChildInfo(QString login);
    QList<QObject*> getSchedule(QString login, QDateTime from, QDateTime to);
    void updateCash(QString login, int value, double latitude, double longitude, QString description);
    void updateCash(QString login, int value);
    QList<QObject*> getTransactions(QString login);

    QVector<Child2*> getChildsByParent(QString login){
        QVector<Child2*> childs;
        QString str = QString("select clogin from parent_child where plogin='%1'").arg(login);
        QSqlQuery query(str);
        while(query.next()){
//            Child()
            QString clogin = svalue(0);
            str = QString("select name, avatar from person where login='%1'").arg(svalue(0));
            QSqlQuery query2  = QSqlQuery(str);
            query2.first();
            Child2* c = new Child2();
            c->login = clogin;
            c->name = query2.value(0).toString();
            c->avatar = query2.value(1).toByteArray();
            childs.append(c);
        }
        return childs;
    }
};

#endif // SERVERCONTROLLER_H
