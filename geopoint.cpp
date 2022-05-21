#include "geopoint.h"

GeoPoint::GeoPoint(QObject *parent) : QObject(parent)
{

}
QList<QObject*> GeoPoint::getTestGeoPoints()
{
    QList<QObject*> arr;

    arr.push_back(new GeoPoint(44.9805679, 37.26379414, "Это я", "Моё местоположение", "qrc:/Images/geomark.png"));
    arr.push_back(new GeoPoint(44.9803679, 37.26399414, "Это не я", "Моё местоположение", "qrc:/Images/geomark.png"));

    arr.push_back(new GeoPoint(44.9802679, 37.26409414, "Чайная", "Моё местоположение", "qrc:/Images/coffe.png"));
    arr.push_back(new GeoPoint(44.9804679, 37.26419414, "Комната релакса", "Моё местоположение", "qrc:/Images/sleep.png"));
    arr.push_back(new GeoPoint(44.9806679, 37.26389414, "Туалет", "Моё местоположение", "qrc:/Images/toilet.png"));

    return arr;
}

QObject* GeoPoint::getPointTestIndex(int index)
{
    return getTestGeoPoints()[index];
}

int GeoPoint::getCountTest()
{
    return getTestGeoPoints().count();
}
