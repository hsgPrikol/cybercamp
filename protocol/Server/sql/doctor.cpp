#include "doctor.h"

Doctor::Doctor(QObject *parent) : QObject(parent)
{

}

Doctor::Doctor(QString _name, QString _spec, QString _room, QString _workgraph)
{
    name = _name;
    specialization = _spec;
    room = _room;
    workgraph = _workgraph;
}
