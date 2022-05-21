import QtQuick 2.0

Item {
    id: root
    width: 480
    height: 50

    property var day_value: 25
    property string button_text_: "Полить"
    property string textTime: "00:00"
    property string textHeader: "Header"
    property string textPosition: "Postition"


    Rectangle{
        id: background
        color: "#f5f5f5"
        opacity: .9
        radius: 10
        anchors.fill: parent


        //        Row{
        //            id: row
        //            spacing: 10
        //            anchors.fill: parent

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
            x: 319
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


        Rectangle{
            x: 75
            y: 10
            width: 1
            height: parent.height - 20
            anchors.verticalCenter: row.verticalCenter
            color: "#7F7F7F"
        }

        Text {
            id: plant_name
            x: 340
            y: 0
            text: textPosition
            font.pixelSize: 16
            horizontalAlignment: Text.AlignLeft
            color: "#7F7F7F"
            height: background.height
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: row.verticalCenter
            font.family: "Calibri"
        }
        //        }
        //        PlantButton{
        //            anchors.right: background.right
        //            anchors.rightMargin: 5
        //            anchors.verticalCenter: background.verticalCenter
        ////            is_active: false
        ////            is_overdue: false
        //            button_text: button_text_
        //            width: 150
        //        }
    }




}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.75}
}
##^##*/
