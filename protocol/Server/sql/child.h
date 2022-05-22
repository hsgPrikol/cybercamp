 #ifndef CHILD_H
#define CHILD_H

#include <QByteArray>
#include <QDate>
#include <QString>
#include "additionalchildinfo.h"
#include <QObject>


class Child : public QObject
{
    Q_OBJECT
public:
    explicit Child(QObject *parent = nullptr) : QObject(parent)
    {

    }
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

    QObject* add_info;

    Child(QString _name,QByteArray _avatar,QString _info,QDate _birthdate,QString _house,QString _room,QString _party_name,QString _owner_name,int _cash,QDate _from,QDate _to);
public slots:
//    QString getName(){return name;}
//    QByteArray getAvatar(){return avatar;}
//    QString getInfo(){return info;}
//    QDate getBirthdate(){return birthdate;}
//    QString getHouse(){return house;}
//    QString getRoom(){return room;}
//    QString getParty_name(){return party_name;}
//    QString getOwner_name(){return owner_name;}
//    int getCash(){return cash;}
//    QDate getFrom(){return from;}
//    QDate getTo(){return to;}

//    QObject* getAdd_info(){return add_info;}
};

#endif // CHILD_H
