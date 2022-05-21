#ifndef DOCTOR_H
#define DOCTOR_H

#include <qstring.h>



class Doctor
{
public:
    QString name;
    QString specialization;
    QString room;
    QString workgraph;
    Doctor(QString _name, QString _spec, QString _room, QString _workgraph);
    Doctor(){};
};

#endif // DOCTOR_H
