#include "servergeneral.h"

ServerGeneral::ServerGeneral(QObject *parent) : QObject(parent)
{
    controllerDB = ServerController::getInstance();

    webSocketServer = new QWebSocketServer(QStringLiteral("SSL Server"),
                                           QWebSocketServer::NonSecureMode,
                                           this);
    QSslConfiguration sslConfiguration;
    QFile certFile(QStringLiteral(":/localhost.cert"));
    QFile keyFile(QStringLiteral(":/localhost.key"));
    certFile.open(QIODevice::ReadOnly);
    keyFile.open(QIODevice::ReadOnly);
    QSslCertificate certificate(&certFile, QSsl::Pem);
    QSslKey sslKey(&keyFile, QSsl::Rsa, QSsl::Pem);
    certFile.close();
    keyFile.close();
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setLocalCertificate(certificate);
    sslConfiguration.setPrivateKey(sslKey);
    webSocketServer->setSslConfiguration(sslConfiguration);

    if (webSocketServer->listen(QHostAddress::Any, PORT_LISTENER))
    {
        qDebug() << "SSL Echo Server listening on port" << PORT_LISTENER;

        connect(webSocketServer,
                &QWebSocketServer::newConnection,
                this,
                &ServerGeneral::onNewConnection);

        connect(webSocketServer,
                &QWebSocketServer::sslErrors,
                this,
                &ServerGeneral::onSslErrors);
    }
}

void ServerGeneral::onNewConnection()
{
    QWebSocket *pSocket = webSocketServer->nextPendingConnection();

    qDebug() << "Client connected:" << pSocket->peerPort();

    connect(pSocket,
            &QWebSocket::textMessageReceived,
            this,
            &ServerGeneral::processTextMessage);

    connect(pSocket,
            &QWebSocket::binaryMessageReceived,
            this,
            &ServerGeneral::processBinaryMessage);

    connect(pSocket,
            &QWebSocket::disconnected,
            this,
            &ServerGeneral::socketDisconnected);

    clientsOnline.push_back({pSocket, "", false});
}

void ServerGeneral::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    QJsonObject object = ProtocolCommunication::StringToJsonObject(message);

    MainHandlerMessage(&object, FindClient(pClient));
}

void ServerGeneral::processBinaryMessage(QByteArray message)
{
    //QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    qDebug() << message;
}

void ServerGeneral::socketDisconnected()
{
    qDebug() << "Client disconnected";

    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    if (pClient)
    {
        RemoveClient(pClient);
        pClient->deleteLater();
    }
}

void ServerGeneral::onSslErrors(const QList<QSslError> &errors)
{
    qDebug() << "Ssl errors occurred " << errors;
}

void ServerGeneral::RemoveClient(QWebSocket *client)
{
    for(int i = 0; i < clientsOnline.count(); i++)
    {
        if((clientsOnline[i].socket->peerAddress() == client->peerAddress()) && (clientsOnline[i].socket->peerPort() == client->peerPort()))
        {
            clientsOnline.remove(i);
        }
    }
}

DataClientOnline* ServerGeneral::FindClient(QWebSocket *client)
{
    for(int i = 0; i < clientsOnline.count(); i++)
    {
        if((clientsOnline[i].socket->peerAddress() == client->peerAddress()) && (clientsOnline[i].socket->peerPort() == client->peerPort()))
        {
            return &(clientsOnline[i]);
        }
    }

    return nullptr;
}

DataClientOnline* ServerGeneral::FindClient(QString login)
{
    for(int i = 0; i < clientsOnline.count(); i++)
    {
        if(clientsOnline[i].login == login)
        {
            return &(clientsOnline[i]);
        }
    }

    return nullptr;
}

void ServerGeneral::MainHandlerMessage(QJsonObject *object, DataClientOnline *client)
{
    qDebug() << ProtocolCommunication::jsonObjectToString(object);

    QString command = ((*object)[ProtocolCommunication::___COMMAND]).toString();

    if(command == ProtocolCommunication::___CMD_AUTHORIZATION)
    {
        handlerAuthorization(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_REGISTRATION)
    {
        handlerRegistration(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_CURRENT_GEO_LOCATION)
    {
        handlerCurrentGeolocation(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_INFO_USER_KID)
    {
        handlerGetInfoUserKid(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_INFO_USER_PARENT)
    {
        handlerGetInfoUserParent(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_SCHEDULE_ON_TODAY_FOR_KID)
    {
        handlerGetScheduleOnTodayForKid(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_SCHEDULE_ON_TODAY_FOR_PARENT)
    {
        handlerGetScheduleOnTodayForParent(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_KID_SHOPPING)
    {
        handlerKidShopping(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_PARENT_MAKE_DEPOSIT)
    {
        handlerParentMakeDeposit(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_HISTORY_CASH)
    {
        handlerGetHistoryCash(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_GEOLOCATION_LOG_TODAY)
    {
        handlerGetGeolocationLogToday(object, client);
    }
}

void ServerGeneral::handlerAuthorization(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();
    QString password = ((*object)[ProtocolCommunication::___PASSWORD]).toString();

    int result = 0;//controllerDB->confirmAuthorization(login, password);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_AUTHORIZATION)}
                                         });

    if(result == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));
        client->login = login;
        client->isAuthorized = true;
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerRegistration(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();
    QString password = ((*object)[ProtocolCommunication::___PASSWORD]).toString();
    QString email = ((*object)[ProtocolCommunication::___E_MAIL]).toString();

    int result = 0;//controllerDB->registrationUser(*farmerNew);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_REGISTRATION)}
                                         });

    if(result == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));
        client->login = login;
        client->isAuthorized = true;
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerCurrentGeolocation(QJsonObject *object, DataClientOnline *client)
{
    QString latitude = ((*object)[ProtocolCommunication::___LATITUDE]).toString();
    QString longitude = ((*object)[ProtocolCommunication::___LONGITUDE]).toString();
}

void ServerGeneral::sendGetGeolocation(DataClientOnline *client)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_GEO_LOCATION)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), client->socket);
}

void ServerGeneral::handlerGetInfoUserParent(QJsonObject *object, DataClientOnline *client)
{
    // TODO дописать информацию полученную из БД
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_INFO_USER_PARENT)}
                                         });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), client->socket);
}

void ServerGeneral::handlerGetInfoUserKid(QJsonObject *object, DataClientOnline *client)
{
    Child child = controllerDB->getChildInfo(client->login);

    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_INFO_USER_KID)},
                                            {ProtocolCommunication::___NAME, QJsonValue(child.name)},
                                            {ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(child.avatar))},
                                            {ProtocolCommunication::___DESCRIPTION, QJsonValue(child.info)},
                                            {ProtocolCommunication::___HOUSE, QJsonValue(child.house)},
                                            {ProtocolCommunication::___ROOM, QJsonValue(child.room)},
                                            {ProtocolCommunication::___PARTY_NAME, QJsonValue(child.party_name)},
                                            {ProtocolCommunication::___OWNER_NAME, QJsonValue(child.owner_name)},
                                            {ProtocolCommunication::___CASH, QJsonValue(child.cash)},
                                            {ProtocolCommunication::___FROM_DATE_TIME, QJsonValue(child.from.toString())},
                                            {ProtocolCommunication::___TO_DATE_TIME, QJsonValue(child.to.toString())},
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), client->socket);
}

void ServerGeneral::handlerGetScheduleOnTodayForParent(QJsonObject *object, DataClientOnline *client)
{
    // TODO дописать информацию полученную из БД
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_SCHEDULE_ON_TODAY_FOR_PARENT)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), client->socket);
}

void ServerGeneral::handlerGetScheduleOnTodayForKid(QJsonObject *object, DataClientOnline *client)
{
    QVector<ScheduleElement> vectorSchedule = controllerDB->getSchedule(client->login);

    QJsonArray jArr;
    QJsonObject jObj;

    for(int i = 0; i < vectorSchedule.size(); i++)
    {
        QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___NAME, QJsonValue(vectorSchedule[i].name)},
                                                {ProtocolCommunication::___DESCRIPTION, QJsonValue(vectorSchedule[i].description)},
                                                {ProtocolCommunication::___INFO, QJsonValue(vectorSchedule[i].info)},
                                                {ProtocolCommunication::___DATE_TIME, QJsonValue(vectorSchedule[i].datetime.toString())},
                                                {ProtocolCommunication::___LATITUDE, QJsonValue(QString::number(vectorSchedule[i].latitude))},
                                                {ProtocolCommunication::___LONGITUDE, QJsonValue(QString::number(vectorSchedule[i].longitude))},
                                                {ProtocolCommunication::___EVENT_STATUS, QJsonValue(QString::number(vectorSchedule[i].status))},
                                                {ProtocolCommunication::___EVENT_TYPE, QJsonValue(QString::number(vectorSchedule[i].event_type_id))}

                                            });

        jArr.push_back(*jObj);
    }

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_SCHEDULE_ON_TODAY_FOR_KID)}
                                          });

    answer->insert(ProtocolCommunication::___SCHEDULE_LIST, jArr);

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerKidShopping(QJsonObject *object, DataClientOnline *client)
{
    QString value = ((*object)[ProtocolCommunication::___VALUE]).toString();
    QString description = ((*object)[ProtocolCommunication::___DESCRIPTION]).toString();

    // TODO дописать вызов функции для снятия денежных средств
}

void ServerGeneral::handlerParentMakeDeposit(QJsonObject *object, DataClientOnline *client)
{
    QString value = ((*object)[ProtocolCommunication::___VALUE]).toString();

    // TODO дописать вызов функции для внесения денежных средств
}

void ServerGeneral::handlerGetHistoryCash(QJsonObject *object, DataClientOnline *client)
{
    // TODO дописать информацию полученную из БД
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_HISTORY_CASH)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), client->socket);
}

void ServerGeneral::handlerGetGeolocationLogToday(QJsonObject *object, DataClientOnline *client)
{
    QDateTime today(QDate::currentDate());

    QVector<LocationLog> vectorLocationLog = controllerDB->getLocationLog(client->login, today, today.addDays(1));

    QJsonArray jArr;
    QJsonObject jObj;

    for(int i = 0; i < vectorLocationLog.size(); i++)
    {
        QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___DATE_TIME, QJsonValue(vectorLocationLog[i].datetime.toString())},
                                                {ProtocolCommunication::___LATITUDE, QJsonValue(QString::number(vectorLocationLog[i].latitude))},
                                                {ProtocolCommunication::___LONGITUDE, QJsonValue(QString::number(vectorLocationLog[i].longitude))}
                                            });

        jArr.push_back(*jObj);
    }

    // TODO дописать информацию полученную из БД
    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GEOLOCATION_LOG_TODAY)}
                                            });

    answer->insert(ProtocolCommunication::___LOCATION_LOG_LIST, jArr);

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}
