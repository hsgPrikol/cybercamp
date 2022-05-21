#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDateTime>
#include <QString>



class Transaction
{
public:
    int value;
    QString description;
    QDateTime datetime;
    Transaction(int _val, QString _desc, QDateTime _datetime);
};

#endif // TRANSACTION_H
