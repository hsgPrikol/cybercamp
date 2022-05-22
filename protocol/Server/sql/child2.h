#ifndef CHILD2_H
#define CHILD2_H

#include <QObject>

class Child2 : public QObject
{
    Q_OBJECT
public:
    QString login;
    QString name;
    QByteArray avatar;
    explicit Child2(QObject *parent = nullptr);

signals:

};

#endif // CHILD2_H
