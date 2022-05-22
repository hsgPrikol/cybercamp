import QtQuick 2.0

Item {
    id: root
    width: 350
    height: 50

    property var day_value: 25
    property string button_text_: "Полить"
    property string textTime: "00:00"
    property string textHeader: "Header"


    Rectangle{
        id: background
        color: "#f5f5f5"
        opacity: .9
        radius: 10
        anchors.fill: parent
        Item {
            width: 1
            height: parent.height
        }


        Text{
            id: dayText
            x: 18
            y: 13
            //                    height: 45
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
            color: "#7F7F7F"
            text: textTime
            //                anchors.verticalCenter: row.verticalCenter
            //anchors.left: row.left
            //anchors.leftMargin: 10
        }

        Rectangle{
            x: 85
            y: 13
            width: 1
            height: parent.height - 20
            anchors.verticalCenter: row.verticalCenter
            color: "#7F7F7F"
        }


        Text {
            id: taskUsername
            x: 100
            y: 0
            text: textHeader
            font.pixelSize: 23
            height: background.height
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.family: "Calibri"
            anchors.verticalCenter: row.verticalCenter
        }
    }
}

