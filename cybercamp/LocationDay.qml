import QtQuick 2.0


//Rectangle{
//    property int dfltWidth: 506
//    property int dfltHeight: 900

//    width: dfltWidth
//    height: dfltHeight
//    color: "black"

    Rectangle {
        id: root
        anchors.horizontalCenter: parent.horizontalCenter
        property int cheight: column.height
        property string textR: "21 мая"
        property int currentIndex: -1
        property var times : [
            "5:30","6:00","6:30","7:00", "7:08","7:30","8:00","8:25","8:30","9:00","9:18","9:30","10:23","10:20"
        ]

        property var headers : [
            "2 корпус","2 корпус","Утренний туалет","Завтрак", "2 корпус","2 корпус","2 корпус","Амфитеатр","Амфитеатр","Амфитеатр","2 корпус","2 корпус","Медицинский корпус","Медицинский корпус"
        ]

        width: 350

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
                    model: times.length
                    Locationposition {
                        textTime: times[index]
                        textHeader: headers[index]
                    }
                }

                Item{
                    width: 1
                    height: 1
                }
            }
        }
    }
//}
