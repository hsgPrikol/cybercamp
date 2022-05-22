#include "locationlog.h"

LocationLog::LocationLog(QObject *parent) : QObject(parent)
{

}

LocationLog::LocationLog(QString _login, QDateTime _datetime, double _latitude, double _longitude)
{
   login = _login;
   datetime = _datetime;
   latitude = _latitude;
   longitude = _longitude;
}
