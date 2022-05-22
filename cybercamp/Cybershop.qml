import QtQuick 2.0
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

Rectangle{
    width: app_width
    height: app_height
    color: "black"
    property var colorBlue: "#177bd9"


    Rectangle{
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        width: parent.width
        height: parent.height
        color: "black"

        Image {
            id: mainPhone
            anchors.fill: parent
            source: "qrc:/pictureRegistration/anime_anime_girls_Touhou_Kochiya_Sanae-71537.jpg"
            opacity: 0.8


        }
        Rectangle {
            id: rectangle
            x: 0
            y: 0
            width: app_width
            height: 60
            color: colorBlue
            radius: 10

            Rectangle{
                        width: parent.width
                        height: 40
                        color: colorBlue
                    }

            Rectangle {
                id: rectangle1
                x: 0
                y: 0
                width: 117
                height: 60
                color: "#00000000"

                Image {
                    id: image
                    x: 40
                    y: 14
                    width: 38
                    height: 32
                    source: "qrc:/Dialog/burger.tif"
                    fillMode: Image.PreserveAspectFit


                    MouseArea {
                                            anchors.fill: parent

                                            onClicked: {
                                                burgermenu.showNavDrawer()
                                                //                            burgermenu.showNavDrawer()
                                            }
                                        }
                }
            }

            Text {
                id: text1
                x: 193
                y: 8
                width: 125
                height: 44
                color: "#ffffff"
                text: qsTr("Cyber-магазин")
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        DropShadow {
                anchors.fill: rectangle
                horizontalOffset: 3
                verticalOffset: 3
                radius: 8.0
                samples: 17
                color: "#80000000"
                source: rectangle
            }

        Column{

            anchors.top: rectangle.bottom
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 25
//                spacing: 10

            Rectangle {
                height: 1
                width: 1
                color: "#00000000"
            }

            Image {
                id: price1700
//                    x: 13
//                    y: 49
                width: parent.width - 25
                height: 150
                anchors.horizontalCenter: parent.horizontalCenter
                source: "qrc:/Resourse_v2/1 lot.tif"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: price2149
//                    x: 13
//                    y: 243
                width: parent.width - 25
                height: 150
                anchors.horizontalCenter: parent.horizontalCenter
                source: "qrc:/Resourse_v2/2 lot.tif"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: price2490
//                    x: 13
//                    y: 436
                width: parent.width - 25
                height: 150
                anchors.horizontalCenter: parent.horizontalCenter
                source: "qrc:/Resourse_v2/3 lot.tif"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: price
//                    x: 13
//                    y: 692
                width: parent.width - 50
                height: 150
                anchors.horizontalCenter: parent.horizontalCenter
                source: "qrc:/Resourse_v2/4 lot.tif"
                fillMode: Image.PreserveAspectFit
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
