#ifndef SERVERGENERAL_H
#define SERVERGENERAL_H

#include <QObject>
#include <QWebSocketServer>
#include <QFile>
#include <QSslKey>
#include <QWebSocket>
#include <QJsonArray>
#include <../protocolcommunication.h>
#include <./sql/servercontroller.h>

struct DataClientOnline
{
    QWebSocket* socket;
    QString login;
    bool isAuthorized;
};

class ServerGeneral : public QObject
{
    Q_OBJECT
public:
    explicit ServerGeneral(QObject *parent = nullptr);

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void onSslErrors(const QList<QSslError> &errors);

private:

    ServerController* controllerDB;

    const quint16 PORT_LISTENER = 1234;
    QWebSocketServer *webSocketServer;
    QVector<DataClientOnline> clientsOnline;

    void RemoveClient(QWebSocket *client);

    DataClientOnline* FindClient(QWebSocket *client);
    DataClientOnline* FindClient(QString login);

    void MainHandlerMessage(QJsonObject* object, DataClientOnline* client);

    /// Обработчик запроса на авторизацию
    void handlerAuthorization(QJsonObject* object, DataClientOnline *client);
    /// Обработчик запроса на регистрацию
    void handlerRegistration(QJsonObject* object, DataClientOnline *client);

    /// Обработчик получения геолокации клиента
    void handlerCurrentGeolocation(QJsonObject* object, DataClientOnline *client);
    /// Запрос на получение геолокации клиента
    void sendGetGeolocation(DataClientOnline *client);

    /// Обработчик запроса на получение информации на родителя
    void handlerGetInfoUserParent(QJsonObject* object, DataClientOnline *client);
    /// Обработчик запроса на получение информации на ребенка
    void handlerGetInfoUserKid(QJsonObject* object, DataClientOnline *client);

    /// Обработчик запроса на получение расписания на сегодня для родителя
    void handlerGetScheduleOnTodayForParent(QJsonObject* object, DataClientOnline *client);
    /// Обработчик запроса на получение расписания на сегодня для ребенка
    void handlerGetScheduleOnTodayForKid(QJsonObject* object, DataClientOnline *client);

    /// Обработчик запроса на снятие денежных средств со счета ребенка
    void handlerKidShopping(QJsonObject* object, DataClientOnline *client);
    /// Обработчик запроса на внесение денежных средств на счета ребенка
    void handlerParentMakeDeposit(QJsonObject* object, DataClientOnline *client);

    /// Обработчик запроса на получение истории списания и пополнения
    void handlerGetHistoryCash(QJsonObject* object, DataClientOnline *client);

    /// Обработчик запроса на получение логов геолокации на сегодня
    void handlerGetGeolocationLogToday(QJsonObject* object, DataClientOnline *client);

signals:

};

#endif // SERVERGENERAL_H
