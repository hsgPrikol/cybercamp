#ifndef GEOCLASS_H
#define GEOCLASS_H

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QDebug>

class GeoClass : public QObject
{
    Q_OBJECT
public:
    explicit GeoClass(QObject *parent = nullptr){

        QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
        if (source) {
            source->setUpdateInterval(1000);
            connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                    this, SLOT(positionUpdated(QGeoPositionInfo)));
            source->startUpdates();
        }
        else
        {
            qDebug("No geoposition");
        }
    }


public slots:
    void positionUpdated(const QGeoPositionInfo &info)
    {
        qDebug("Position updated:");
        QString asd=info.coordinate().toString();
        qDebug() << asd;
        emit onUpdateGeo(info.coordinate().latitude(), info.coordinate().longitude());
    }

signals:
    void onUpdateGeo(double x, double y);
};

#endif // GEOCLASS_H
