import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    width: 506
    height: 1500
    color: "#dfdfdf"
    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 506
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
                text: qsTr("Книжка-малышка")
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

    DropShadow {
            anchors.fill: rectangle
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 17
            color: "#80000000"
            source: rectangle
        }

    Image{
        y:60
        x: -5
        width: 516
        source: "qrc:/Knijka_malyshka/prikol1.png"
        fillMode: Image.PreserveAspectFit
    }
}


