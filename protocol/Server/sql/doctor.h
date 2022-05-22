#ifndef DOCTOR_H
#define DOCTOR_H

#include <qstring.h>
#include <QObject>


class Doctor: public QObject
{
    Q_OBJECT
public:
    explicit Doctor(QObject *parent = nullptr);
    QString name;
    QString specialization;
    QString room;
    QString workgraph;
    Doctor(QString _name, QString _spec, QString _room, QString _workgraph);
};

#endif // DOCTOR_H
