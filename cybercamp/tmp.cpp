#include "tmp.h"

Tmp::Tmp(QObject *parent) : QObject(parent)
{

}

QString Tmp::getName(int index)
{
    QList<QString> list = leaderboards.keys();





}

QString Tmp::getKeyLeaderBoards()
{
    leaderboards.insert("Алексей", 1021);




    qDebug() << leaderboards[0];

    return "s";
}

int Tmp::getValueLeaderBoards()
{
    return 1;
}
