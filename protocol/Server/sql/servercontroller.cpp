#include "servercontroller.h"

#include <QByteArray>

QDate getDate(QString dateText)
{
    QDate date;

    if(dateText.contains("-"))
        date=QDate::fromString(dateText, "dd-MM-yyyy");
    if(dateText.contains("."))
        date=QDate::fromString(dateText, "dd.MM.yyyy");
    else
        date=QDate::fromString(dateText.remove(0,3), "MMM dd yyyy");
    return date;
}

QDateTime getDateTime(QString dateTimeText)
{
    QDateTime dateTime;
    if(dateTimeText.contains("."))
        dateTime=QDateTime::fromString(dateTimeText, "dd.MM.yyyy h:mm:ss");
    else
        dateTime=QDateTime::fromString(dateTimeText, "yyyy-MM-dd hh:mm:ss");
    return dateTime;
}

QByteArray StringToByteArray(QString string)
{
    QByteArray byteArray(string.size(), (char)255);

    for(int i = 0; i < byteArray.size(); i++)
    {
        byteArray[i] = string[i].toLatin1();
    }

    return byteArray;
}

ServerController* ServerController::instance = nullptr;

ServerController::ServerController()
{
    startServer();
}

bool ServerController::startServer()
{
    QVector<QString> paths({
                               "C:\\Users\\5rota\\Desktop\\SuperDataBase.db"
                           });

    db = QSqlDatabase::addDatabase("QSQLITE");

    foreach(QString p, paths){
        if(QFile::exists(p)){
            db.setDatabaseName(p);
        }
    }


    if(db.open()){
        return true;
    } else {
        return false;
    }
}

ServerController *ServerController::getInstance()
{
    if(!instance)
        instance = new ServerController();
    return instance;
}

int ServerController::getLastId(QString table, QString column, QString where)
{
    auto str = QString("SELECT %0 FROM %1 %3 ORDER BY %0 DESC LIMIT 1").arg(column).arg(table).arg(where);
    QSqlQuery query(str);
    query.first();
    return ivalue(0);
    //return 0;
}

void ServerController::addLocationLog(QString login, double latitude, double longitude)
{
    QString str = QString("INSERT INTO location_log (login, latitude, longitude) VALUES('%0', %1, %2 );").arg(login).arg(latitude).arg(longitude);
    QSqlQuery query(str);
    query.exec();
}

QVector<LocationLog> ServerController::getLocationLog(QString login)
{
    QString str = QString("select datetime, latitude, longitude from location_log where login='%0'").arg(login);
    QSqlQuery query(str);
    QVector<LocationLog> logs;
    while(query.next()){
        logs.append(LocationLog(login, getDateTime(svalue(0)), query.value(1).toDouble(), query.value(1).toDouble()));
    }
    return logs;
}

QVector<LocationLog> ServerController::getLocationLog(QString login, QDateTime from, QDateTime to)
{
    QString _from = from.toString("yyyy-MM-dd hh:mm:ss");
    QString _to = to.toString("yyyy-MM-dd hh:mm:ss");
    QString str = QString("select datetime, latitude, longitude from location_log where login='%0' and datetime < '%1' and datetime > '%2'").arg(login).arg(_to).arg(_from);
    QSqlQuery query(str);
    QVector<LocationLog> logs;
    while(query.next()){
        logs.append(LocationLog(login, getDateTime(svalue(0)), query.value(1).toDouble(), query.value(2).toDouble()));
    }
    return logs;
}

QVector<ScheduleElement> ServerController::getSchedule(QString login)
{
    QString now = QDateTime::currentDateTime().toString("dd.MM.yy hh:mm:ss");
    QString next_day = QDateTime(QDate::currentDate().addDays(1), QTime(0,0)).toString("dd.MM.yy hh:mm:ss");
    QString str = QString("select id, name, datetime, info, latitude, longitude from party_schedule inner join shedule on id = event_id inner join children_info on children_info.party_id = party_schedule.party_id where clogin = '%1' and datetime > '%2' and datetime < '%3'").arg(login).arg(now).arg(next_day);
    QSqlQuery query(str);
    QVector<ScheduleElement> sc;
    while(query.next()){
        sc.append(ScheduleElement(ivalue(0), svalue(1), getDateTime(svalue(2)), svalue(3),svalue(4).toDouble(), svalue(5).toDouble()));
    }

    str = QString("select id, name, datetime, info, latitude, longitude, status, event_type_id, description from person_schedule inner join shedule on id = event_id where person_id = '%1' and datetime > '%2' and datetime < '%3'").arg(login).arg(QDateTime::currentDateTime().toString("dd.MM.yy hh:mm:ss")).arg(QDateTime(QDate::currentDate().addDays(1), QTime(0,0)).toString("dd.MM.yy hh:mm:ss"));

    query = QSqlQuery(str);
    while(query.next()){
        sc.append(ScheduleElement(ivalue(0), svalue(1), getDateTime(svalue(2)), svalue(3),svalue(4).toDouble(), svalue(5).toDouble()));
    }

    return sc;
}

Child ServerController::getChildInfo(QString login)
{
    QString str = QString("select child_info_helper.name, child_info_helper.avatar, child_info_helper.info, child_info_helper.birthdate, house, room, child_info_helper.party_name, person.name as owner_name, child_info_helper.cash, period.from123, period.to123 from child_info_helper inner join person on owner = person.login inner join period on period_id = period.id where child_info_helper.login='%1'").arg(login);


    QSqlQuery query(str);
    qDebug() << str;

    query.first();
    QString name = svalue(0);
    QByteArray avatar = StringToByteArray(svalue(1));
    QString info = svalue(2);
    QDate bd = getDate(svalue(3));
    QString house = svalue(4);
    QString room = svalue(5);
    QString party_name = svalue(6);
    QString owner_name = svalue(7);
    int cash = ivalue(8);
    QDate from = getDate(svalue(9));
    QDate to = getDate(svalue(10));
    Child c(name, avatar, info, bd, house, room, party_name, owner_name, cash, from, to);

    return c;
}

void ServerController::prikol(QString login)
{
}

QPair<int, int> ServerController::authorization(QString login, QString pass)
{
    QPair<int, int> answer;
    QString str = QString("select role from person where login = '%1' and pass = '%2'").arg(login).arg(pass);
    QSqlQuery query(str);
    if(query.first())
    {
        answer.first = 1;
        answer.second = ivalue(0);
    }
    else{
        answer.first = 0;
        answer.second = -1;
    }
    return answer;
}

Child ServerController::getFullChildInfo(QString login)
{
    Child answer = getChildInfo(login);
    QString str = QString("SELECT diet, excursion, move_mode, min_water, yfz, sport_games, climat, second_dianoz, main_dianoz, organization, doctor_id, health_group FROM children_info where clogin = '%1'").arg(login);
    QSqlQuery query(str);
    query.first();
    QString diet = svalue(0);
    QString excursion = svalue(1);
    QString move_mode = svalue(2);
    QString min_water = svalue(3);
    QString yfz = svalue(4);
    QString sport_games = svalue(5);
    QString climat = svalue(6);
    QString main_diagnoz = svalue(8);
    QString second_diagnoz = svalue(7);
    QString organization = svalue(9);
    QString doctor_id = svalue(10);
    QString healt_group = svalue(11);

    str = QString("SELECT name, specialization, room, workgraph FROM doctor innaer join person on login = dlogin where login = '%1'").arg(doctor_id);
    query = QSqlQuery(str);
    query.first();
    QString doctor_name = svalue(0);
    QString doctor_specialization = svalue(1);
    QString doctor_room = svalue(2);
    QString workgraph = svalue(3);

    answer.add_info.climat = climat;
    answer.add_info.diet = diet;
    answer.add_info.doctor = Doctor(doctor_name, doctor_specialization, doctor_room, workgraph);
    answer.add_info.excursion = excursion;
    answer.add_info.healt_group = healt_group;
    answer.add_info.main_diagnoz = main_diagnoz;
    answer.add_info.second_diagnoz = second_diagnoz;
    answer.add_info.min_water = min_water;
    answer.add_info.move_mode = move_mode;
    answer.add_info.organization = organization;
    answer.add_info.sport_games = sport_games;
    answer.add_info.yfz = yfz;
    return answer;
}

QVector<ScheduleElement> ServerController::getSchedule(QString login, QDateTime from, QDateTime to)
{
    QString _from = from.toString("dd.MM.yy hh:mm:ss");
    QString _to = to.toString("dd.MM.yy hh:mm:ss");
    QString str = QString("select id, name, datetime, info, latitude, longitude from party_schedule inner join shedule on id = event_id inner join children_info on children_info.party_id = party_schedule.party_id where clogin = '%1' and datetime > '%2' and datetime < '%3'").arg(login).arg(_from).arg(_to);
    QSqlQuery query(str);
    QVector<ScheduleElement> sc;
    while(query.next()){
        sc.append(ScheduleElement(ivalue(0), svalue(1), getDateTime(svalue(2)), svalue(3),svalue(4).toDouble(), svalue(5).toDouble()));
    }

    str = QString("select id, name, datetime, info, latitude, longitude, status, event_type_id, description from person_schedule inner join shedule on id = event_id where person_id = '%1' and datetime > '%2' and datetime < '%3'").arg(login).arg(_from).arg(_to);

    query = QSqlQuery(str);
    while(query.next()){
        sc.append(ScheduleElement(ivalue(0), svalue(1), getDateTime(svalue(2)), svalue(3),svalue(4).toDouble(), svalue(5).toDouble()));
    }

    return sc;
}

void ServerController::updateCash(QString login, int value, double latitude, double longitude, QString description)
{
    QString str = QString("SELECT cash FROM children_info where clogin = '%1'").arg(login);
    QSqlQuery query(str);
    query.first();
    int cash = ivalue(0);
    str = QString("UPDATE children_info SET cash = '%1' WHERE clogin = '%2'").arg(cash+value).arg(login);
    query = QSqlQuery(str);
    query.exec();

    str = QString("INSERT INTO location_log (login,latitude,longitude)VALUES ('%1','%2','%3');").arg(login).arg(latitude).arg(longitude);

    QSqlQuery(str).exec();

    str = QString("INSERT INTO cash_history (clogin,value,description)VALUES ('%1','%2','%3');").arg(login).arg(value).arg(description);

    QSqlQuery(str).exec();
}

void ServerController::updateCash(QString login, int value)
{
    QString description = "Addition cash";
    QString str = QString("SELECT cash FROM children_info where clogin = '%1'").arg(login);
    QSqlQuery query(str);
    query.first();
    int cash = ivalue(0);
    str = QString("UPDATE children_info SET cash = '%1' WHERE clogin = '%2'").arg(cash+value).arg(login);
    query = QSqlQuery(str);
    query.exec();

    str = QString("INSERT INTO cash_history (clogin,value,description)VALUES ('%1','%2','%3');").arg(login).arg(value).arg(description);

    QSqlQuery(str).exec();
}

QVector<Transaction> ServerController::getTransactions(QString login)
{
    QString str = QString("SELECT datetime, value, description FROM cash_history where clogin = '%1';").arg(login);
    QSqlQuery query(str);
    QVector<Transaction> ts;
    while(query.next()){
        ts.append(Transaction(ivalue(1), svalue(2), getDateTime(svalue(0))));
    }

    return ts;
}




