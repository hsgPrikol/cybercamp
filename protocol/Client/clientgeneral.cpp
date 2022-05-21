#include "clientgeneral.h"

void ClientGeneral::onConnected()
{
    qDebug() << "WebSocketServer connected";
    connect(&socketServer,
            &QWebSocket::textMessageReceived,
            this,
            &ClientGeneral::onTextMessageReceived);

    sendAuthorization("login", "password");
}

void ClientGeneral::onTextMessageReceived(QString message)
{
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());

    QJsonObject object = ProtocolCommunication::StringToJsonObject(message);

    if(ProtocolCommunication::CompareSocket(socket, &socketServer))
    {
        processingEventFromServer(&object);
    }
    else
    {
        qDebug() << "не от сервера";
    }
}

void ClientGeneral::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);
    socketServer.ignoreSslErrors();
}

void ClientGeneral::processingEventFromServer(QJsonObject *object)
{
    qDebug() << ProtocolCommunication::jsonObjectToString(object);

    QString command = ((*object)[ProtocolCommunication::___COMMAND]).toString();

    if(command == ProtocolCommunication::___CMD_AUTHORIZATION)
    {
        handlerAuthorization(object);
    }
    else if(command == ProtocolCommunication::___CMD_REGISTRATION)
    {
        handlerRegistration(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_GEO_LOCATION)
    {
        handlerGetGeolocation(object);
    }
    else if(command == ProtocolCommunication::___CMD_INFO_USER_KID)
    {
        handlerInfoUserKid(object);
    }
    else if(command == ProtocolCommunication::___CMD_INFO_USER_PARENT)
    {
        handlerInfoUserParent(object);
    }
    else if(command == ProtocolCommunication::___CMD_SCHEDULE_ON_TODAY_FOR_KID)
    {
        handlerScheduleOnTodayForKid(object);
    }
    else if(command == ProtocolCommunication::___CMD_SCHEDULE_ON_TODAY_FOR_PARENT)
    {
        handlerScheduleOnTodayForParent(object);
    }
    else if(command == ProtocolCommunication::___CMD_HISTORY_CASH)
    {
        handlerHistoryCash(object);
    }
    else if(command == ProtocolCommunication::___CMD_GEOLOCATION_LOG_TODAY)
    {
        handlerGeolocationLogToday(object);
    }
}

void ClientGeneral::handlerAuthorization(QJsonObject *object)
{
    QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

    if(resultStatus == ProtocolCommunication::___STS_DONE)
    {
        // успешная авторизация
        isAuthorization = true;
        role = ((*object)[ProtocolCommunication::___ROLE]).toString().toInt();
    }
    else
    {
        // не авторизовался по какой то причине
        // TODO
    }
}

void ClientGeneral::handlerRegistration(QJsonObject *object)
{
    QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

    if(resultStatus == ProtocolCommunication::___STS_DONE)
    {
        // успешная регистрация
        isAuthorization = true;
//        sendGetInformationAboutUser();
//        emit onAnswerRegistration(true);
    }
    else
    {
        // не зарегистрировался по какой то причине
//        emit onAnswerRegistration(false);
    }
}

void ClientGeneral::handlerGetGeolocation(QJsonObject *object)
{
    // TODO получение геолокации
    double latitude = 0;
    double longitude = 0;

    sendGeolocation(QString::number(latitude), QString::number(longitude));
}

void ClientGeneral::handlerInfoUserKid(QJsonObject *object)
{
    QString name = ((*object)[ProtocolCommunication::___NAME]).toString();
    QByteArray image = ProtocolCommunication::StringToByteArray(((*object)[ProtocolCommunication::___IMAGE]).toString());
    QString description = ((*object)[ProtocolCommunication::___DESCRIPTION]).toString();
    QString house = ((*object)[ProtocolCommunication::___HOUSE]).toString();
    QString room = ((*object)[ProtocolCommunication::___ROOM]).toString();
    QString partyName = ((*object)[ProtocolCommunication::___PARTY_NAME]).toString();
    QString ownerName = ((*object)[ProtocolCommunication::___OWNER_NAME]).toString();
    QString cash = ((*object)[ProtocolCommunication::___CASH]).toString();
    QDate from = QDate::fromString(((*object)[ProtocolCommunication::___FROM_DATE_TIME]).toString());
    QDate to = QDate::fromString(((*object)[ProtocolCommunication::___TO_DATE_TIME]).toString());
    QDate birthDate = QDate::fromString(((*object)[ProtocolCommunication::___DATE_TIME]).toString());

    person = Child(name, ProtocolCommunication::StringToByteArray(image), description, birthDate, house, room, partyName, ownerName, cash.toInt(), from, to);
}

void ClientGeneral::handlerInfoUserParent(QJsonObject *object)
{
    QString name = ((*object)[ProtocolCommunication::___NAME]).toString();
    QByteArray image = ProtocolCommunication::StringToByteArray(((*object)[ProtocolCommunication::___IMAGE]).toString());
    QString description = ((*object)[ProtocolCommunication::___DESCRIPTION]).toString();
    QString house = ((*object)[ProtocolCommunication::___HOUSE]).toString();
    QString room = ((*object)[ProtocolCommunication::___ROOM]).toString();
    QString partyName = ((*object)[ProtocolCommunication::___PARTY_NAME]).toString();
    QString ownerName = ((*object)[ProtocolCommunication::___OWNER_NAME]).toString();
    QString cash = ((*object)[ProtocolCommunication::___CASH]).toString();
    QDate from = QDate::fromString(((*object)[ProtocolCommunication::___FROM_DATE_TIME]).toString());
    QDate to = QDate::fromString(((*object)[ProtocolCommunication::___TO_DATE_TIME]).toString());
    QDate birthDate = QDate::fromString(((*object)[ProtocolCommunication::___DATE_TIME]).toString());
    QString loginChild = ((*object)[ProtocolCommunication::___LOGIN]).toString();

    child = Child(name, ProtocolCommunication::StringToByteArray(image), description, birthDate, house, room, partyName, ownerName, cash.toInt(), from, to);

    child.add_info.diet = ((*object)[ProtocolCommunication::___DIET]).toString();
    child.add_info.excursion = ((*object)[ProtocolCommunication::___EXCURSION]).toString();
    child.add_info.move_mode = ((*object)[ProtocolCommunication::___MOVE_MODE]).toString();
    child.add_info.min_water = ((*object)[ProtocolCommunication::___MIN_WATER]).toString();
    child.add_info.yfz = ((*object)[ProtocolCommunication::___YFZ]).toString();
    child.add_info.sport_games = ((*object)[ProtocolCommunication::___SPORT_GAMES]).toString();
    child.add_info.climat = ((*object)[ProtocolCommunication::___CLIMAT]).toString();
    child.add_info.main_diagnoz = ((*object)[ProtocolCommunication::___MAIN_DIAGNOZ]).toString();
    child.add_info.second_diagnoz = ((*object)[ProtocolCommunication::___SECOND_DIAGNOZ]).toString();
    child.add_info.organization = ((*object)[ProtocolCommunication::___ORGANIZATION]).toString();
    child.add_info.doctor.name = ((*object)[ProtocolCommunication::___DOCTOR_NAME]).toString();
    child.add_info.healt_group = ((*object)[ProtocolCommunication::___HEALT_GROUP]).toString();
}

void ClientGeneral::handlerScheduleOnTodayForKid(QJsonObject *object)
{
    QJsonArray jArr = ((*object)[ProtocolCommunication::___SCHEDULE_LIST]).toArray();
    QJsonObject jObj;

    for(int i = 0; i < jArr.size(); i++)
    {
        jObj = jArr[i].toObject();

        QString name = ((jObj)[ProtocolCommunication::___NAME]).toString();
        QString description = ((jObj)[ProtocolCommunication::___DESCRIPTION]).toString();
        QString info = ((jObj)[ProtocolCommunication::___INFO]).toString();
        QDateTime dateTime = QDateTime::fromString(((jObj)[ProtocolCommunication::___DATE_TIME]).toString());
        QString latitude = ((jObj)[ProtocolCommunication::___LATITUDE]).toString();
        QString longitude = ((jObj)[ProtocolCommunication::___LONGITUDE]).toString();
        QString eventStatus = ((jObj)[ProtocolCommunication::___EVENT_STATUS]).toString();
        QString eventType = ((jObj)[ProtocolCommunication::___EVENT_TYPE]).toString();

        vectorScheduleElement.push_back(*(new ScheduleElement(-1, name, dateTime, info, latitude.toDouble(), longitude.toDouble(), eventStatus.toInt(), eventType.toInt(), description)));
    }
}

void ClientGeneral::handlerScheduleOnTodayForParent(QJsonObject *object)
{
    handlerScheduleOnTodayForKid(object);
}

void ClientGeneral::handlerHistoryCash(QJsonObject *object)
{
    QJsonArray jArr = ((*object)[ProtocolCommunication::___TRANSITION_LOG_LIST]).toArray();
    QJsonObject jObj;

    for(int i = 0; i < jArr.size(); i++)
    {
        jObj = jArr[i].toObject();

        QString value = ((jObj)[ProtocolCommunication::___VALUE]).toString();
        QString description = ((jObj)[ProtocolCommunication::___DESCRIPTION]).toString();
        QDateTime dateTime = QDateTime::fromString(((jObj)[ProtocolCommunication::___DATE_TIME]).toString());

        vectorTransition.push_back(*(new Transaction(value.toInt(), description, dateTime)));
    }
}

void ClientGeneral::handlerGeolocationLogToday(QJsonObject *object)
{
    QString loginChild = ((*object)[ProtocolCommunication::___LOGIN]).toString();
    QJsonArray jArr = ((*object)[ProtocolCommunication::___LOCATION_LOG_LIST]).toArray();
    QJsonObject jObj;

    for(int i = 0; i < jArr.size(); i++)
    {
        jObj = jArr[i].toObject();

        QDateTime dateTime = QDateTime::fromString(((jObj)[ProtocolCommunication::___DATE_TIME]).toString());
        QString latitude = ((jObj)[ProtocolCommunication::___LATITUDE]).toString();
        QString longitude = ((jObj)[ProtocolCommunication::___LONGITUDE]).toString();

        vectorLocationLog.push_back(*(new LocationLog(loginChild, dateTime, latitude.toDouble(), longitude.toDouble())));
    }
}

void ClientGeneral::sendAuthorization(QString login, QString password)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_AUTHORIZATION)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(login)},
                                                {ProtocolCommunication::___PASSWORD, QJsonValue(password)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);

    myLogin = login;
}

void ClientGeneral::sendRegistration(QString login, QString password, QString email)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_AUTHORIZATION)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(login)},
                                                {ProtocolCommunication::___PASSWORD, QJsonValue(password)},
                                                {ProtocolCommunication::___E_MAIL, QJsonValue(email)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);

    myLogin = login;
}

void ClientGeneral::sendGeolocation(QString latitude, QString longitude)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_CURRENT_GEO_LOCATION)},
                                                {ProtocolCommunication::___LATITUDE, QJsonValue(latitude)},
                                                {ProtocolCommunication::___LONGITUDE, QJsonValue(longitude)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetUserInfoKid()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_INFO_USER_KID)}
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetUserInfoParent(QString login)
{
    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_INFO_USER_PARENT)},
                                            {ProtocolCommunication::___LOGIN, QJsonValue(login)}
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetScheduleOnTodayForKid()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_SCHEDULE_ON_TODAY_FOR_KID)}
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetScheduleOnTodayForParent()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_SCHEDULE_ON_TODAY_FOR_PARENT)}
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendKidShopping(QString description, QString value)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_KID_SHOPPING)},
                                                {ProtocolCommunication::___VALUE, QJsonValue(value)},
                                                {ProtocolCommunication::___DESCRIPTION, QJsonValue(description)}
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendParentMakeDeposit(QString value)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_KID_SHOPPING)},
                                                {ProtocolCommunication::___VALUE, QJsonValue(value)}
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetHistoryCash(QString login)
{
    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_HISTORY_CASH)},
                                            {ProtocolCommunication::___LOGIN, QJsonValue(login)}
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetGetGeolocationLogToday(QString login)
{
    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_GEOLOCATION_LOG_TODAY)},
                                            {ProtocolCommunication::___LOGIN, QJsonValue(login)}
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

ClientGeneral::ClientGeneral(QObject *parent) : QObject(parent)
{
    connect(&socketServer,
            &QWebSocket::connected,
            this,
            &ClientGeneral::onConnected);

    connect(&socketServer,
            QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors),
            this,
            &ClientGeneral::onSslErrors);

    socketServer.open(URL_SERVER);
}

