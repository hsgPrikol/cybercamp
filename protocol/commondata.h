#ifndef COMMONDATA_H
#define COMMONDATA_H

#include <QObject>

class CommonData : public QObject
{
    Q_OBJECT
public:
    explicit CommonData(QObject *parent = nullptr);

signals:

};

#endif // COMMONDATA_H
