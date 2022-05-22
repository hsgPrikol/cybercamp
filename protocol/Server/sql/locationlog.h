#ifndef LOCATIONLOG_H
#define LOCATIONLOG_H

#include <QDateTime>
#include <QString>
#include <QObject>


class LocationLog: public QObject
{
    Q_OBJECT
public:
    explicit LocationLog(QObject *parent = nullptr);
    QString login;
    QDateTime datetime;
    double latitude;
    double longitude;
    LocationLog(QString _login, QDateTime _datetime, double _latitude, double _longitude);
};

#endif // LOCATIONLOG_H
