#ifndef LOCATIONLOG_H
#define LOCATIONLOG_H

#include <QDateTime>
#include <QString>



class LocationLog
{
public:
    QString login;
    QDateTime datetime;
    double latitude;
    double longitude;
    LocationLog(QString _login, QDateTime _datetime, double _latitude, double _longitude);
};

#endif // LOCATIONLOG_H
