#ifndef CAMERAASIST_H
#define CAMERAASIST_H

#include <QObject>
#include <QZXing.h>
#include <QtDebug>

class CameraAsist : public QObject
{
    Q_OBJECT
public:
    explicit CameraAsist(QObject *parent = nullptr);

signals:

public slots:
    QString recognizeQR(QString path);

};

#endif // CAMERAASIST_H
