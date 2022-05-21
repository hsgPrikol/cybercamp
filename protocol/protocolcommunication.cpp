#include "protocolcommunication.h"

const QString ProtocolCommunication::DFLT_PATH_FILE = "C:\\tula_hack_att";

const QString ProtocolCommunication::___COMMAND = QString("command");
const QString ProtocolCommunication::___CMD_AUTHORIZATION = QString("authorization");
const QString ProtocolCommunication::___CMD_REGISTRATION = QString("registration");

const QString ProtocolCommunication::___CMD_CURRENT_GEO_LOCATION = QString("current_geolocation");
const QString ProtocolCommunication::___CMD_GET_GEO_LOCATION = QString("get_geolocation");

const QString ProtocolCommunication::___CMD_GET_INFO_USER_KID = QString("get_info_user_kid");
const QString ProtocolCommunication::___CMD_INFO_USER_KID = QString("info_user_kid");

const QString ProtocolCommunication::___CMD_GET_INFO_USER_PARENT = QString("get_info_user_parent");
const QString ProtocolCommunication::___CMD_INFO_USER_PARENT = QString("info_user_parent");

const QString ProtocolCommunication::___CMD_GET_SCHEDULE_ON_TODAY_FOR_KID = QString("get_schedule_on_today_for_kid");
const QString ProtocolCommunication::___CMD_SCHEDULE_ON_TODAY_FOR_KID = QString("schedule_on_today_for_kid");

const QString ProtocolCommunication::___CMD_GET_SCHEDULE_ON_TODAY_FOR_PARENT = QString("get_schedule_on_today_for_parent");
const QString ProtocolCommunication::___CMD_SCHEDULE_ON_TODAY_FOR_PARENT = QString("schedule_on_today_for_parent");

const QString ProtocolCommunication::___CMD_KID_SHOPPING = QString("kid_shopping");
const QString ProtocolCommunication::___CMD_PARENT_MAKE_DEPOSIT = QString("parent_make_deposit");

const QString ProtocolCommunication::___CMD_GET_HISTORY_CASH = QString("get_history_cash");
const QString ProtocolCommunication::___CMD_HISTORY_CASH = QString("history_cash");

const QString ProtocolCommunication::___CMD_GET_GEOLOCATION_LOG_TODAY = QString("get_geolocation_log_today");
const QString ProtocolCommunication::___CMD_GEOLOCATION_LOG_TODAY = QString("geolocation_log_today");

const QString ProtocolCommunication::___LOGIN = QString("login");
const QString ProtocolCommunication::___PASSWORD = QString("password");
const QString ProtocolCommunication::___STATUS = QString("status");
const QString ProtocolCommunication::___STS_DONE = QString("done");
const QString ProtocolCommunication::___STS_NOPE = QString("nope");
const QString ProtocolCommunication::___E_MAIL = QString("email");
const QString ProtocolCommunication::___LATITUDE = QString("latitude");
const QString ProtocolCommunication::___LONGITUDE = QString("longitude");
const QString ProtocolCommunication::___NAME = QString("name");
const QString ProtocolCommunication::___IMAGE = QString("image");
const QString ProtocolCommunication::___HOUSE = QString("house");
const QString ProtocolCommunication::___ROOM = QString("room");
const QString ProtocolCommunication::___PARTY_NAME = QString("party_name");
const QString ProtocolCommunication::___OWNER_NAME = QString("owner_name");
const QString ProtocolCommunication::___CASH = QString("cash");
const QString ProtocolCommunication::___FROM_DATE_TIME = QString("from_date_time");
const QString ProtocolCommunication::___TO_DATE_TIME = QString("to_date_time");
const QString ProtocolCommunication::___SCHEDULE_LIST = QString("schedule_list");
const QString ProtocolCommunication::___LOCATION_LOG_LIST = QString("location_log_list");
const QString ProtocolCommunication::___TRANSITION_LOG_LIST = QString("transition_log_list");
const QString ProtocolCommunication::___INFO = QString("info");
const QString ProtocolCommunication::___EVENT_STATUS = QString("event_status");
const QString ProtocolCommunication::___EVENT_TYPE = QString("event_type");
const QString ProtocolCommunication::___DATE_TIME = QString("date_time");
const QString ProtocolCommunication::___DESCRIPTION = QString("description");
const QString ProtocolCommunication::___VALUE = QString("value");
const QString ProtocolCommunication::___ROLE = QString("role");
const QString ProtocolCommunication::___DIET = QString("diet");
const QString ProtocolCommunication::___EXCURSION = QString("excursion");
const QString ProtocolCommunication::___MOVE_MODE = QString("move_mode");
const QString ProtocolCommunication::___MIN_WATER = QString("min_water");
const QString ProtocolCommunication::___YFZ = QString("yfz");
const QString ProtocolCommunication::___SPORT_GAMES = QString("sport_games");
const QString ProtocolCommunication::___CLIMAT = QString("climat");
const QString ProtocolCommunication::___MAIN_DIAGNOZ = QString("main_diagnoz");
const QString ProtocolCommunication::___SECOND_DIAGNOZ = QString("second_diagnoz");
const QString ProtocolCommunication::___ORGANIZATION = QString("organization");
const QString ProtocolCommunication::___DOCTOR_NAME = QString("doctor_name");
const QString ProtocolCommunication::___HEALT_GROUP = QString("healt_group");

QString ProtocolCommunication::ByteArrayToString(QByteArray array)
{
    QString result(array.size(), QChar(255));

    for(int i = 0; i < array.size(); i++)
    {
        result[i] = array[i];
    }

    return result;
}

QByteArray ProtocolCommunication::StringToByteArray(QString string)
{
    QByteArray byteArray(string.size(), (char)255);

    for(int i = 0; i < byteArray.size(); i++)
    {
        byteArray[i] = string[i].toLatin1();
    }

    return byteArray;
}

void ProtocolCommunication::SaveBinaryFile(QString binary, QString name, QString type, QString idMedia, QString idInst)
{
    QFile file(DFLT_PATH_FILE + name + "." + type);

    QByteArray byteArray = StringToByteArray(binary);

    file.write(byteArray);
    file.close();
}

QString ProtocolCommunication::SaveBinaryFile(QString binary, QString name, QString id)
{
    QDir p=QDir::current();

    QString path = p.path()+"/" + name +"_"+id;
    QFile file(path);

    QByteArray byteArray = StringToByteArray(binary);

    file.open(QIODevice::WriteOnly);
    file.write(byteArray);
    file.close();

    return path;
}

void ProtocolCommunication::SendTextMessage(QString message, QWebSocket *client)
{
    client->sendTextMessage(message);
}

void ProtocolCommunication::SendBinaryMessage(QByteArray message, QWebSocket *client)
{
    client->sendBinaryMessage(message);
}

QString ProtocolCommunication::jsonObjectToString(QJsonObject *object)
{
    static QJsonDocument jDoc;
    jDoc.setObject(*object);
    return jDoc.toJson();
}

QJsonObject ProtocolCommunication::StringToJsonObject(QString str)
{
    static QJsonDocument jDoc;
    jDoc = QJsonDocument::fromJson(str.toUtf8());
    return jDoc.object();
}

bool ProtocolCommunication::CompareSocket(QWebSocket* a, QWebSocket* b)
{
    return ((a->peerAddress() == b->peerAddress()) && (a->peerPort() == b->peerPort()));
}

QByteArray ProtocolCommunication::LoadBinaryFile(QString path)
{
    QByteArray byteArray;
    QFile file(path);
    file.open(QFile::ReadOnly);
    byteArray = file.readAll();
    file.close();
    return byteArray;
}

QString ProtocolCommunication::GetTypeFromPathFile(QString path)
{
    int indexDot = path.lastIndexOf('.');
    indexDot++;
    int lenType = path.size() - indexDot;
    QString result(lenType, ' ');

    for(int i = 0; i < lenType; i++)
    {
        result[i] = path[indexDot + i];
    }

    return result;
}

QString ProtocolCommunication::GetNameFromPathFile(QString path)
{
    int indexDot = path.lastIndexOf('.');
    int indexStartName = path.lastIndexOf('\\') + 1;

    int lenType = indexDot - indexStartName;
    QString result(lenType, ' ');

    for(int i = 0; i < lenType; i++)
    {
        result[i] = path[indexStartName + i];
    }

    return result;
}

ProtocolCommunication::ProtocolCommunication(QObject *parent) : QObject(parent)
{

}
