import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: plantGlossaryInfo

    width: app_width
    height: app_height
    color: "#00000000"

     property var colorBlue: "#177bd9"

    Rectangle {
        id: header
        x: 0
        y: 0
        width: app_width
        height: 70
        color: colorBlue
        radius: 10

        Rectangle{
                    width: parent.width
                    height: 40
                    color: colorBlue
                }

        Rectangle {
            id: rectangle
            x: 17
            y: 0
            width: 70
            height: 70
            color: colorBlue

            Image {
                id: arrow
                x: 13
                y: 20
                width: 44
                height: 31
                source: "qrc:/Dialog/vyhod.tif"
                fillMode: Image.PreserveAspectFit
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        loaderCamp.sourceComponent=plannerComponent
                    }
                }
            }
        }

        Rectangle {
            id: rectangle1
            x: 93
            y: 0
            width: 405
            height: 70
            color: colorBlue

            Text {
                id: text1
                x: 8
                y: 0
                width: 303
                height: 70
                color: "#ffffff"
                text: "Игорь Юрьевич"//client.getMyName()
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    DropShadow {
            anchors.fill: header
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 17
            color: "#80000000"
            source: header
        }

    Rectangle{
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "black"
        Image {
            id: mainPhone
            opacity: 0.8
            anchors.fill: parent
            source: "qrc:/pictureRegistration/anime_anime_girls_Touhou_Kochiya_Sanae-71537.jpg"
        }
    }



    ScrollView {
        id: scrollView
        x: 0
        y: 69
        width: app_width
        height: 831
        contentHeight: 1000
        contentWidth: parent.width
        clip: true

        Column {
            id: column
            width: 200
            height: 400

            Rectangle {
                id: photo
                width: app_width
                height: 314
                color: "#ffffff"

                Image {
                    id: image
                    x: 0
                    y: 0
                    width: app_width
                    height: 314
                    source: client.getMyAvatar()
                    fillMode: Image.PreserveAspectFit
                }
            }

            Achivments {
                id: achivments

            }
        }
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
