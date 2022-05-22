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


//    QVector<Child2*> test = ServerController::getInstance()->getChildsByParent("parent");
//    int c = 34/8;
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

    QPair<int, int> result = controllerDB->authorization(login, password);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_AUTHORIZATION)}
                                         });

    if(result.first == 1)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));
        answer->insert(ProtocolCommunication::___ROLE, QJsonValue(QString::number(result.second)));
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

    int result = 1;

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_REGISTRATION)}
                                         });

    if(result == 1)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));
        client->login = login;
        client->isAuthorized = true;
//        answer->insert(ProtocolCommunication::___ROLE, QJsonValue(QString::number(result.second)));
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

    controllerDB->addLocationLog(client->login, latitude.toDouble(), longitude.toDouble());
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
    Child* child = controllerDB->getChildInfo(((*object)[ProtocolCommunication::___LOGIN]).toString());

    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_INFO_USER_KID)},
                                            {ProtocolCommunication::___NAME, QJsonValue(child->name)},
                                            {ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(child->avatar))},
                                            {ProtocolCommunication::___DESCRIPTION, QJsonValue(child->info)},
                                            {ProtocolCommunication::___HOUSE, QJsonValue(child->house)},
                                            {ProtocolCommunication::___ROOM, QJsonValue(child->room)},
                                            {ProtocolCommunication::___PARTY_NAME, QJsonValue(child->party_name)},
                                            {ProtocolCommunication::___OWNER_NAME, QJsonValue(child->owner_name)},
                                            {ProtocolCommunication::___CASH, QJsonValue(child->cash)},
                                            {ProtocolCommunication::___FROM_DATE_TIME, QJsonValue(child->from.toString())},
                                            {ProtocolCommunication::___TO_DATE_TIME, QJsonValue(child->to.toString())},
                                            {ProtocolCommunication::___DATE_TIME, QJsonValue(child->birthdate.toString())},
                                            {ProtocolCommunication::___DIET, QJsonValue(((AdditionalChildInfo*)child->add_info)->diet)},
                                            {ProtocolCommunication::___EXCURSION, QJsonValue(((AdditionalChildInfo*)child->add_info)->excursion)},
                                            {ProtocolCommunication::___MOVE_MODE, QJsonValue(((AdditionalChildInfo*)child->add_info)->move_mode)},
                                            {ProtocolCommunication::___MIN_WATER, QJsonValue(((AdditionalChildInfo*)child->add_info)->min_water)},
                                            {ProtocolCommunication::___YFZ, QJsonValue(((AdditionalChildInfo*)child->add_info)->yfz)},
                                            {ProtocolCommunication::___SPORT_GAMES, QJsonValue(((AdditionalChildInfo*)child->add_info)->sport_games)},
                                            {ProtocolCommunication::___CLIMAT, QJsonValue(((AdditionalChildInfo*)child->add_info)->climat)},
                                            {ProtocolCommunication::___MAIN_DIAGNOZ, QJsonValue(((AdditionalChildInfo*)child->add_info)->main_diagnoz)},
                                            {ProtocolCommunication::___SECOND_DIAGNOZ, QJsonValue(((AdditionalChildInfo*)child->add_info)->second_diagnoz)},
                                            {ProtocolCommunication::___ORGANIZATION, QJsonValue(((AdditionalChildInfo*)child->add_info)->organization)},
                                            {ProtocolCommunication::___DOCTOR_NAME, QJsonValue(((Doctor*)((AdditionalChildInfo*)child->add_info)->doctor)->name)},
                                            {ProtocolCommunication::___HEALT_GROUP, QJsonValue(((AdditionalChildInfo*)child->add_info)->healt_group)},
                                            {ProtocolCommunication::___LOGIN, QJsonValue(((*object)[ProtocolCommunication::___LOGIN]).toString())},

                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), client->socket);
}

void ServerGeneral::handlerGetInfoUserKid(QJsonObject *object, DataClientOnline *client)
{
    Child* child = controllerDB->getChildInfo(client->login);

    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_INFO_USER_KID)},
                                            {ProtocolCommunication::___NAME, QJsonValue(child->name)},
                                            {ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(child->avatar))},
                                            {ProtocolCommunication::___DESCRIPTION, QJsonValue(child->info)},
                                            {ProtocolCommunication::___HOUSE, QJsonValue(child->house)},
                                            {ProtocolCommunication::___ROOM, QJsonValue(child->room)},
                                            {ProtocolCommunication::___PARTY_NAME, QJsonValue(child->party_name)},
                                            {ProtocolCommunication::___OWNER_NAME, QJsonValue(child->owner_name)},
                                            {ProtocolCommunication::___CASH, QJsonValue(child->cash)},
                                            {ProtocolCommunication::___FROM_DATE_TIME, QJsonValue(child->from.toString())},
                                            {ProtocolCommunication::___TO_DATE_TIME, QJsonValue(child->to.toString())},
                                            {ProtocolCommunication::___DATE_TIME, QJsonValue(child->birthdate.toString())}
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), client->socket);
}

void ServerGeneral::handlerGetScheduleOnTodayForParent(QJsonObject *object, DataClientOnline *client)
{
    Child* child = controllerDB->getChildInfo(client->login);

    QJsonObject* jObj = new QJsonObject({
                                            {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_INFO_USER_KID)},
                                            {ProtocolCommunication::___NAME, QJsonValue(child->name)},
                                            {ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(child->avatar))},
                                            {ProtocolCommunication::___DESCRIPTION, QJsonValue(child->info)},
                                            {ProtocolCommunication::___HOUSE, QJsonValue(child->house)},
                                            {ProtocolCommunication::___ROOM, QJsonValue(child->room)},
                                            {ProtocolCommunication::___PARTY_NAME, QJsonValue(child->party_name)},
                                            {ProtocolCommunication::___OWNER_NAME, QJsonValue(child->owner_name)},
                                            {ProtocolCommunication::___CASH, QJsonValue(child->cash)},
                                            {ProtocolCommunication::___FROM_DATE_TIME, QJsonValue(child->from.toString())},
                                            {ProtocolCommunication::___TO_DATE_TIME, QJsonValue(child->to.toString())},
                                            {ProtocolCommunication::___DIET, QJsonValue(((AdditionalChildInfo*)child->add_info)->diet)},
                                            {ProtocolCommunication::___EXCURSION, QJsonValue(((AdditionalChildInfo*)child->add_info)->excursion)},
                                            {ProtocolCommunication::___MOVE_MODE, QJsonValue(((AdditionalChildInfo*)child->add_info)->move_mode)},
                                            {ProtocolCommunication::___MIN_WATER, QJsonValue(((AdditionalChildInfo*)child->add_info)->min_water)},
                                            {ProtocolCommunication::___YFZ, QJsonValue(((AdditionalChildInfo*)child->add_info)->yfz)},
                                            {ProtocolCommunication::___SPORT_GAMES, QJsonValue(((AdditionalChildInfo*)child->add_info)->sport_games)},
                                            {ProtocolCommunication::___CLIMAT, QJsonValue(((AdditionalChildInfo*)child->add_info)->climat)},
                                            {ProtocolCommunication::___MAIN_DIAGNOZ, QJsonValue(((AdditionalChildInfo*)child->add_info)->main_diagnoz)},
                                            {ProtocolCommunication::___SECOND_DIAGNOZ, QJsonValue(((AdditionalChildInfo*)child->add_info)->second_diagnoz)},
                                            {ProtocolCommunication::___ORGANIZATION, QJsonValue(((AdditionalChildInfo*)child->add_info)->organization)},
                                            {ProtocolCommunication::___DOCTOR_NAME, QJsonValue(((Doctor*)((AdditionalChildInfo*)child->add_info)->doctor)->name)},
                                            {ProtocolCommunication::___HEALT_GROUP, QJsonValue(((AdditionalChildInfo*)child->add_info)->healt_group)}
                                        });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), client->socket);
}

void ServerGeneral::handlerGetScheduleOnTodayForKid(QJsonObject *object, DataClientOnline *client)
{
    QList<QObject*> vectorSchedule = controllerDB->getSchedule(client->login);

    QJsonArray jArr;
    QJsonObject jObj;

    for(int i = 0; i < vectorSchedule.size(); i++)
    {
        QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___NAME, QJsonValue(((ScheduleElement*)vectorSchedule[i])->name)},
                                                {ProtocolCommunication::___DESCRIPTION, QJsonValue(((ScheduleElement*)vectorSchedule[i])->description)},
                                                {ProtocolCommunication::___INFO, QJsonValue(((ScheduleElement*)vectorSchedule[i])->info)},
                                                {ProtocolCommunication::___DATE_TIME, QJsonValue(((ScheduleElement*)vectorSchedule[i])->datetime.toString())},
                                                {ProtocolCommunication::___LATITUDE, QJsonValue(QString::number(((ScheduleElement*)vectorSchedule[i])->latitude))},
                                                {ProtocolCommunication::___LONGITUDE, QJsonValue(QString::number(((ScheduleElement*)vectorSchedule[i])->longitude))},
                                                {ProtocolCommunication::___EVENT_STATUS, QJsonValue(QString::number(((ScheduleElement*)vectorSchedule[i])->status))},
                                                {ProtocolCommunication::___EVENT_TYPE, QJsonValue(QString::number(((ScheduleElement*)vectorSchedule[i])->event_type_id))}
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
    QString latitude = ((*object)[ProtocolCommunication::___LATITUDE]).toString();
    QString longitude = ((*object)[ProtocolCommunication::___LONGITUDE]).toString();

    controllerDB->updateCash(client->login, value.toInt(), latitude.toDouble(), longitude.toDouble(), description);
}

void ServerGeneral::handlerParentMakeDeposit(QJsonObject *object, DataClientOnline *client)
{
    QString value = ((*object)[ProtocolCommunication::___VALUE]).toString();

    controllerDB->updateCash(client->login, value.toInt());
}

void ServerGeneral::handlerGetHistoryCash(QJsonObject *object, DataClientOnline *client)
{
    QList<QObject*> vectorTransition = controllerDB->getTransactions(((*object)[ProtocolCommunication::___LOGIN]).toString());

    QJsonArray jArr;
    QJsonObject jObj;

    for(int i = 0; i < vectorTransition.size(); i++)
    {
        QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___VALUE, QJsonValue(((Transaction*)vectorTransition[i])->value)},
                                                {ProtocolCommunication::___DESCRIPTION, QJsonValue(((Transaction*)vectorTransition[i])->description)},
                                                {ProtocolCommunication::___DATE_TIME, QJsonValue(((Transaction*)vectorTransition[i])->datetime.toString())}
                                            });

        jArr.push_back(*jObj);
    }

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_HISTORY_CASH)}
                                            });

    answer->insert(ProtocolCommunication::___TRANSITION_LOG_LIST, jArr);

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetGeolocationLogToday(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();

    QDateTime today(QDate::currentDate(), QTime());

    QList<QObject*> vectorLocationLog = controllerDB->getLocationLog(login, today, today.addDays(1));

    QJsonArray jArr;
    QJsonObject jObj;

    for(int i = 0; i < vectorLocationLog.size(); i++)
    {
        QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___DATE_TIME, QJsonValue(((LocationLog*)vectorLocationLog[i])->datetime.toString())},
                                                {ProtocolCommunication::___LATITUDE, QJsonValue(QString::number(((LocationLog*)vectorLocationLog[i])->latitude))},
                                                {ProtocolCommunication::___LONGITUDE, QJsonValue(QString::number(((LocationLog*)vectorLocationLog[i])->longitude))}
                                            });

        jArr.push_back(*jObj);
    }

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GEOLOCATION_LOG_TODAY)}
                                            });

    answer->insert(ProtocolCommunication::___LOCATION_LOG_LIST, jArr);

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}
