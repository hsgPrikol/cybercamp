#ifndef PROTOCOLCOMMUNICATION_H
#define PROTOCOLCOMMUNICATION_H

#include <QObject>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>

class ProtocolCommunication : public QObject
{
    Q_OBJECT
private:
    const static QString DFLT_PATH_FILE;

public:
    explicit ProtocolCommunication(QObject *parent = nullptr);

    const static QString ___COMMAND;

    //~~~~~commands start~~~~~
    const static QString ___CMD_AUTHORIZATION;
    const static QString ___CMD_REGISTRATION;

    const static QString ___CMD_CURRENT_GEO_LOCATION;
    const static QString ___CMD_GET_GEO_LOCATION;

    const static QString ___CMD_GET_INFO_USER_KID;
    const static QString ___CMD_INFO_USER_KID;

    const static QString ___CMD_GET_INFO_USER_PARENT;
    const static QString ___CMD_INFO_USER_PARENT;

    const static QString ___CMD_GET_SCHEDULE_ON_TODAY_FOR_PARENT;
    const static QString ___CMD_SCHEDULE_ON_TODAY_FOR_PARENT;

    const static QString ___CMD_GET_SCHEDULE_ON_TODAY_FOR_KID;
    const static QString ___CMD_SCHEDULE_ON_TODAY_FOR_KID;

    const static QString ___CMD_KID_SHOPPING;
    const static QString ___CMD_PARENT_MAKE_DEPOSIT;

    const static QString ___CMD_GET_HISTORY_CASH;
    const static QString ___CMD_HISTORY_CASH;

    const static QString ___CMD_GET_GEOLOCATION_LOG_TODAY;
    const static QString ___CMD_GEOLOCATION_LOG_TODAY;
    //~~~~~commands end~~~~~~~

    const static QString ___LOGIN;
    const static QString ___PASSWORD;
    const static QString ___STATUS;
    const static QString ___E_MAIL;
    const static QString ___LATITUDE;
    const static QString ___LONGITUDE;
    const static QString ___NAME;
    const static QString ___IMAGE;
    const static QString ___HOUSE;
    const static QString ___ROOM;
    const static QString ___PARTY_NAME;
    const static QString ___OWNER_NAME;
    const static QString ___CASH;
    const static QString ___FROM_DATE_TIME;
    const static QString ___TO_DATE_TIME;
    const static QString ___SCHEDULE_LIST;
    const static QString ___LOCATION_LOG_LIST;
    const static QString ___TRANSITION_LOG_LIST;
    const static QString ___INFO;
    const static QString ___EVENT_STATUS;
    const static QString ___EVENT_TYPE;
    const static QString ___DATE_TIME;
    const static QString ___DESCRIPTION;
    const static QString ___VALUE;
    const static QString ___ROLE;

    const static QString ___DIET;
    const static QString ___EXCURSION;
    const static QString ___MOVE_MODE;
    const static QString ___MIN_WATER;
    const static QString ___YFZ;
    const static QString ___SPORT_GAMES;
    const static QString ___CLIMAT;
    const static QString ___MAIN_DIAGNOZ;
    const static QString ___SECOND_DIAGNOZ;
    const static QString ___ORGANIZATION;
    const static QString ___HEALT_GROUP;
    const static QString ___DOCTOR_NAME;

    //~~~~~status start~~~~~
    const static QString ___STS_DONE;
    const static QString ___STS_NOPE;
    //~~~~~status end~~~~~~~

    static QString ByteArrayToString(QByteArray array);
    static QByteArray StringToByteArray(QString string);
    static bool CompareSocket(QWebSocket* a, QWebSocket* b);
    static void SaveBinaryFile(QString binary, QString name, QString type, QString idMedia, QString idInst);
    static QString SaveBinaryFile(QString binary, QString name, QString id);
    static void SendTextMessage(QString message, QWebSocket *client);
    static void SendBinaryMessage(QByteArray message, QWebSocket *client);
    static QString jsonObjectToString(QJsonObject *object);
    static QJsonObject StringToJsonObject(QString str);
    static QByteArray LoadBinaryFile(QString path);
    static QString GetTypeFromPathFile(QString path);
    static QString GetNameFromPathFile(QString path);

signals:

};

#endif // PROTOCOLCOMMUNICATION_H
