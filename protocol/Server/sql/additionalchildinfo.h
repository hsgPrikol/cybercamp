#ifndef ADDITIONALCHILDINFO_H
#define ADDITIONALCHILDINFO_H

#include <QObject>
#include "doctor.h"

class AdditionalChildInfo : public QObject
{
    Q_OBJECT
public:
    explicit AdditionalChildInfo(QObject *parent = nullptr);

    QString diet;
    QString excursion;
    QString move_mode;
    QString min_water;
    QString yfz;
    QString sport_games;
    QString climat;
    QString main_diagnoz;
    QString second_diagnoz;
    QString organization;
    QObject* doctor;
    QString healt_group;

    AdditionalChildInfo(QString d):diet(d){}

signals:

};

#endif // ADDITIONALCHILDINFO_H
