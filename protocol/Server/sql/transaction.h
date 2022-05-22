#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDateTime>
#include <QString>
#include <QObject>


class Transaction: public QObject
{
    Q_OBJECT
public:
    explicit Transaction(QObject *parent = nullptr);
    int value;
    QString description;
    QDateTime datetime;
    Transaction(int _val, QString _desc, QDateTime _datetime);
};

#endif // TRANSACTION_H
