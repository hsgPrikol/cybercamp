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
//        sendGetInformationAboutUser();
//        emit onAnswerAuthorization(true);
    }
    else
    {
        // не авторизовался по какой то причине
//        emit onAnswerAuthorization(false);
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
    double latitude = 0;
    double longitude = 0;

    sendGeolocation(QString::number(latitude), QString::number(longitude));
}

void ClientGeneral::handlerInfoUserKid(QJsonObject *object)
{
    // TODO тут получаем нужную информацию о ребенке
}

void ClientGeneral::handlerInfoUserParent(QJsonObject *object)
{
    // TODO тут получаем нужную информацию о родителе
}

void ClientGeneral::handlerScheduleOnTodayForKid(QJsonObject *object)
{
    // TODO тут получаем расписание на сегодня для ребенка
}

void ClientGeneral::handlerScheduleOnTodayForParent(QJsonObject *object)
{
    // TODO тут получаем расписание на сегодня для родителя
}

void ClientGeneral::handlerHistoryCash(QJsonObject *object)
{
    // TODO тут получаем историю списания и пополнения
}

void ClientGeneral::handlerGeolocationLogToday(QJsonObject *object)
{
    // TODO тут получаем лог геолокации на сегодня
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

void ClientGeneral::sendGetUserInfoParent()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_INFO_USER_PARENT)}
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

void ClientGeneral::sendGetHistoryCash()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_HISTORY_CASH)}
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetGetGeolocationLogToday()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_GEOLOCATION_LOG_TODAY)}
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

