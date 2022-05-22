#include "scheduleelement.h"

ScheduleElement::ScheduleElement(int _id, QString _name, QDateTime _datetime, QString _info, double _latitude, double _longitude)
{
    id = _id;
    name = _name;
    datetime = _datetime;
    info = _info;
    latitude = _latitude;
    longitude = _longitude;
}
