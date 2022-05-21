#ifndef SCHEDULEELEMENT_H
#define SCHEDULEELEMENT_H

#include <qdatetime.h>
#include <qstring.h>



class ScheduleElement
{
public:
    int id;
    QString name;
    QDateTime datetime;
    QString info;
    double latitude;
    double longitude;

    int status;
    int event_type_id;
    QString description;

    ScheduleElement(int _id, QString _name, QDateTime _datetime, QString _info, double _latitude, double _longitude);
    ScheduleElement(int _id, QString _name, QDateTime _datetime, QString _info, double _latitude, double _longitude, int _status, int _event_type_id, QString _description) : ScheduleElement(_id, _name, _datetime, _info, _latitude, _longitude){
        status = _status;
        event_type_id = _event_type_id;
        description = _description;
    }
};

#endif // SCHEDULEELEMENT_H
