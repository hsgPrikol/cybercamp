#ifndef GEOPOINT_H
#define GEOPOINT_H

#include <QObject>


class GeoPoint : public QObject
{
    Q_OBJECT
public:
    double longitude;
    double latitude;
    QString header;
    QString info;
    QString path;

    explicit GeoPoint(QObject *parent = nullptr);

    GeoPoint(double _long, double lat, QString head, QString inf, QString p): longitude(_long), latitude(lat), header(head), info(inf), path(p){}


public slots:
    double getlongitude() {return longitude;};
    double getlatitude() {return latitude;};
    QString getheader() {return header;};
    QString getinfo() {return header;};
    QString getpath() {return path;};
    QList<QObject*> getTestGeoPoints();

    QObject* getPointTestIndex(int index);
    int getCountTest();

signals:


};

#endif // GEOPOINT_H
