#include "child.h"


Child::Child(QString _name, QByteArray _avatar, QString _info, QDate _birthdate, QString _house, QString _room, QString _party_name, QString _owner_name, int _cash, QDate _from, QDate _to)
{
    name = _name;
    avatar = _avatar;
    info = _info;
    birthdate = _birthdate;
    house = _house;
    room = _room;
    party_name = _party_name;
    owner_name = _owner_name;
    cash = _cash;
    from = _from;
    to = _to;
}
