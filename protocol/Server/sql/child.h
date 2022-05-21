#ifndef CHILD_H
#define CHILD_H

#include <QByteArray>
#include <QDate>
#include <QString>



class Child
{
public:
    QString name;
    QByteArray avatar;
    QString info;
    QDate birthdate;
    QString house;
    QString room;
    QString party_name;
    QString owner_name;
    int cash;
    QDate from;
    QDate to;


    Child(QString _name,QByteArray _avatar,QString _info,QDate _birthdate,QString _house,QString _room,QString _party_name,QString _owner_name,int _cash,QDate _from,QDate _to);
    Child(){};
};

#endif // CHILD_H
