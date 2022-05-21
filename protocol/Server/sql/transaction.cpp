#include "transaction.h"


Transaction::Transaction(int _val, QString _desc, QDateTime _datetime)
{
    value = _val;
    description = _desc;
    datetime = _datetime;
}
