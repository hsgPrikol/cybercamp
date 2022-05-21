 import QtQuick 2.0

Rectangle {
    id: root
    property int cheight: column.height
    width: app_height
    property string textR: "Месяц"
    property int currentIndex: -1
    property var times : [
    ["6:00","6:10","7:00","7:30", "8:30","10:00","11:00","13:00","14:00","15:00","19:00","20:00","21:00","22:00"],
        ["6:00","6:10","7:00","7:30", "8:30","10:00","11:00","13:00","14:00","15:00","19:00","20:00","21:00","22:00"],
        ["6:00","6:10","7:00","7:30", "8:30","10:00","11:00","13:00","14:00","15:00","19:00","20:00","21:00","21:30","23:00"]
    ]

    property var headers : [
        ["Подъём","Зарядка","Утренний туалет","Завтрак", "Медпроцедуры","Поход на море","Спортмасс","Обед","Сон-час","Личное время","Ужин","Личное время","Прогулка","Отбой"],
        ["Подъём","Зарядка","Утренний туалет","Завтрак", "Прогулка","Развивающие игры","Соревнования","Обед","Сон-час","Личное время","Ужин","Личное время","Прогулка","Отбой"],
        ["Подъём","Зарядка","Утренний туалет","Завтрак", "Медпроцедуры","Поход на море","Спортмасс","Обед","Сон-час","Личное время","Ужин","Личное время","Прогулка","Личное время","Отбой"]
    ]

    property var positions : [
        ["2 корпус","Спортплощадка","2 корпус","Столовай", "Территория","Пляж","Спортзал","Столовая","2 корпус","Территория","Столовая","2 корпус","Территория","2 корпус"],
        ["2 корпус","Спортплощадка","2 корпус","Столовай", "Территория","Пляж","Спортзал","Столовая","2 корпус","Территория","Столовая","2 корпус","Территория","2 корпус"],
        ["2 корпус","Спортплощадка","2 корпус","Столовай", "Территория","Пляж","Спортзал","Столовая","2 корпус","Территория","Столовая","2 корпус","Территория","2 корпус","2 корпус"]
    ]

    height: 10+30+items.height
    color: "#00000000"

    Column {
        id: column
        width: parent.width
        //anchors.horizontalCenter: root.horizontalCenter
        Item{
            width: 1
            height: 10
        }
        Rectangle{
            y: 10
            height: 30
            width: 100
            radius: 5
            color: "#f5f5f5"
            opacity: .7

            anchors.horizontalCenter: items.horizontalCenter

            Text{
                anchors.fill: parent
                text: textR
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        Column{
            id:items
            spacing: 7
            Item{
                width: 1
                height: 1
            }

            Repeater {
                model: times[currentIndex].length
                TaskChildren {
                    textTime: times[currentIndex][index]
                    textHeader: headers[currentIndex][index]
                    textPosition: positions[currentIndex][index]
                }
            }

            Item{
                width: 1
                height: 1
            }
        }
    }
}
