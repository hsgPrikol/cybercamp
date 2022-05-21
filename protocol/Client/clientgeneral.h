#ifndef CLIENTGENERAL_H
#define CLIENTGENERAL_H

#include <QObject>
#include <QFile>
#include <QSslKey>
#include <QWebSocket>
#include <QJsonArray>
#include <QMap>
#include <qmath.h>

#include "../protocolcommunication.h"
#include "../Server/sql/child.h"
#include "../Server/sql/locationlog.h"
#include "../Server/sql/scheduleelement.h"
#include "../Server/sql/transaction.h"

class ClientGeneral : public QObject
{
    Q_OBJECT
public:
    explicit ClientGeneral(QObject *parent = nullptr);

private:
    const QUrl URL_SERVER = QUrl(QStringLiteral("ws://localhost:1234"));

    QWebSocket socketServer;

    Child person;

    Child child;
    QVector<ScheduleElement> vectorScheduleElement;
    QVector<QString> vectorChild;
    QVector<Transaction> vectorTransition;
    QVector<LocationLog> vectorLocationLog;

    bool isAuthorization = false;
    int role = -1;
    QString myLogin;

    void onConnected();
    void onTextMessageReceived(QString message);
    void onSslErrors(const QList<QSslError> &errors);

    void processingEventFromServer(QJsonObject* object);

    /// Обработчик запроса на авторизацию
    void handlerAuthorization(QJsonObject* object);
    /// Обработчик запроса на регистрацию
    void handlerRegistration(QJsonObject* object);

    /// Обработчик запроса на получение геолокации
    void handlerGetGeolocation(QJsonObject* object);

    /// Обработчик ответа сервера на запрос информации о ребенке
    void handlerInfoUserKid(QJsonObject* object);
    /// Обработчик ответа сервера на запрос информации о родителе
    void handlerInfoUserParent(QJsonObject* object);

    /// Обработчик ответа сервера на запрос расписания на сегодня для ребенка
    void handlerScheduleOnTodayForKid(QJsonObject* object);
    /// Обработчик ответа сервера на запрос расписания на сегодня для родителя
    void handlerScheduleOnTodayForParent(QJsonObject* object);

    /// Обработчик ответа сервера на запрос истории счета ребенка
    void handlerHistoryCash(QJsonObject* object);

    /// Обработчик ответа сервера на запрос лога геолокации на сегодня
    void handlerGeolocationLogToday(QJsonObject* object);

public slots:


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на авторизацию
    void sendAuthorization(QString login, QString password);

    /// Отправка запроса на регистрацию
    void sendRegistration(QString login, QString password, QString email);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка текущей геопозиции
    void sendGeolocation(QString latitude, QString longitude);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на получение информации о ребенке
    void sendGetUserInfoKid();

    /// Отправка запроса на получении информации о родителе
    void sendGetUserInfoParent(QString login);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на получение расписания на сегодня для ребенка
    void sendGetScheduleOnTodayForKid();

    /// Отправка запроса на получение расписания на сегодня для родителя
    void sendGetScheduleOnTodayForParent();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка события ребенок сделал покупку
    void sendKidShopping(QString description, QString value);

    /// Отправка события родитель внес денежные средства
    void sendParentMakeDeposit(QString value);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на получение истории счета ребенка
    void sendGetHistoryCash(QString login);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на получение лога геолокации на сегодня
    void sendGetGetGeolocationLogToday(QString login);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signals:

};

#endif // CLIENTGENERAL_H
