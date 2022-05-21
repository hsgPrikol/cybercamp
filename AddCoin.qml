import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: root1


    property var colorBlue: "#e6177bd9"

    property int dfltWidth: 506
    property int dfltHeight: 900

    width: dfltWidth
    height: dfltHeight

    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"

    property var tmpNewDialog

    color: noColor

    property int countRep: 6
    Rectangle{
        id: root
        anchors.fill: parent
        width: parent.width
        height: parent.height
        color: "black"

        Image {
            id: mainPhone
            anchors.fill: parent
            source: "qrc:/pictureRegistration/anime_anime_girls_Touhou_Kochiya_Sanae-71537.jpg"
            opacity: 0.3
        }

        Drawer {
            id: drawer
            width: Math.min(dfltWidth, dfltHeight) / 3 * 2
            height: parent.height

            ListView{
                focus: true
                currentIndex: 0
                anchors.fill: parent

                delegate: ItemDelegate {
                    width: parent.width
                    text: model.text
                    highlighted: ListView.isCurrentItem
                    onClicked: {
                        drawer.close()
                        model.triggered()
                    }
                }

                model: ListModel {
                    ListElement {
                        text: qsTr("Open...")
                        triggered: function()


                        {
                            console.log("Open...")
                        }
                    }
                    ListElement {

                        text: qsTr("About...")
                        triggered: function()
                        {
                            console.log("About...");
                        }
                    }
                }

                ScrollIndicator.vertical: ScrollIndicator { }
            }
        }


        Rectangle {
            id: rectangle
            x: 0
            y: 0
            width: 506
            height: 60
            color: colorBlue

            Rectangle {
                id: rectangle1
                x: 0
                y: 0
                width: 117
                height: 60
                color: "#00000000"

                Image {
                    id: image
                    x: 8
                    y: 0
                    width: 40
                    height: 60
                    source: "qrc:/Raspisanie/burger.tif"
                    fillMode: Image.PreserveAspectFit


                }
                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        burgermenu.showNavDrawer()
                        console.log("navDrawer.showNavDrawer()")
                    }
                }
            }

            Rectangle {
                id: rectangle2
                x: 195
                y: 0
                width: 117
                height: 60
                color: "#00000000"

                Text {
                    id: text2
                    x: 0
                    y: 0
                    width: 117
                    height: 60
                    color: "#ffffff"
                    text: qsTr("Диалоги")
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle {
                id: rectangle3
                x: 389
                y: 0
                width: 117
                height: 60
                color: "#00000000"

                Image {
                    id: image1
                    x: 44
                    y: 8
                    width: 65
                    height: 44
                    source: "qrc:/Messenger/poisk.tif"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }

    }


    Rectangle{
        x: 53
        y: 344
        width: 450
        height: 213
        color: "white"
        radius: 14

        Rectangle{
            width: 450
            height: 90
            color: colorBlue
            radius: 14

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y: 7
                text: qsTr("Пополнение")
                color: "white"
                font.pixelSize: 24
            }
        }
        Rectangle{
            x: 0
            width: 450
            height: 155
            y: 44
            color: white


            Column{
                spacing: 20
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                Row {
                    id: textRow
                    spacing: 3

                    anchors.horizontalCenter: parent.horizontalCenter
                    Text{
                        text: qsTr("Пополнить на сумму:")
                        font.pixelSize: 24
                    }

                    TextField{
                        id: coins
                        width: 90
                        color: "white"
                        background: Rectangle{
                            width: 90
                            height: 40
                            color: "green"
                            radius: 5
                            anchors.centerIn: coins
                        }
                    }

                    Text{
                        text: qsTr("Vita-coin")
                        font.pixelSize: 24
                    }
                }
                Button{
                    id: button
                    width: 200
                    height: 43
                    Text{
                        color: "white"
                        text: "Перевести"
                        font.pointSize: 15
                        anchors.centerIn: parent
                    }


                    anchors.horizontalCenter: parent.horizontalCenter
                    background: Rectangle{
                        id: button_back

                        color: button.pressed ? Qt.darker("green") : "green"
                        radius: 5
                    }
                }
            }
        }
    }

}
