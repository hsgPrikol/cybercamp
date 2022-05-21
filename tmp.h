#ifndef TMP_H
#define TMP_H

#include <QObject>
#include <QMap>
#include <QDebug>

class Tmp : public QObject
{
    Q_OBJECT
public:
    explicit Tmp(QObject *parent = nullptr);

private:
    QMap<QString, int> leaderboards;

public slots:
    QString getKeyLeaderBoards();
    int getValueLeaderBoards();

    QString getName(int index);
signals:

};

#endif // TMP_H
