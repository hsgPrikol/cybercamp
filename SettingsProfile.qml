import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Dialogs 1.2

Rectangle{
    id: root

    width: app_width
    height: app_height
    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#3fae51"
    property var colorBlue: "#e6177bd9"

    property int countIndexVessage: 0


    property color darkerBiruzoviu: Qt.darker(colorBlue) //слишком темный, использовать Qt.darker(biruzoviu)


                    //массивы для теста визуализации настроек через репитер
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    property int fontSize: 14

//    width: app_width
//    height: app_height
    color: "#00000000"

    property int heightToolSettings: 60


    FileDialog {
            id: fileOpenDialog
            title: "Select an image file"
            folder: shortcuts.documents
            nameFilters: [
                "Image files (*.png *.jpeg *.jpg)",
            ]
            onAccepted: {
                console.log(fileOpenDialog.fileUrl)
            }
        }

    Rectangle {
        id: separatorLine
        x: 0
        y: 60
        width: parent.width
        height: 1
        color: Qt.darker(colorBlue)
    }

    Rectangle {
        id: toolBar
        width: parent.width
        height: 60
        color: colorBlue
        radius: 10

        Rectangle{
                    width: parent.width
                    height: 40
                    color: colorBlue
                }

        Rectangle {
            id: rectangle
            x: 8
            y: 0
            width: 60
            height: 60
            color: "#00000000"

            Image {
                id: image
                x: 5
                y: 5
                width: 50
                height: 50
                source: "qrc:/Dialog/vyhod.tif"

                fillMode: Image.PreserveAspectFit
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    loaderCamp.sourceComponent = plannerComponent
                }
            }
        }

        Rectangle {
            id: maskText
            x: 163
            y: 0
            width: 180
            height: 60
            color: "#00000000"

            Text {
                id: textSettings
                anchors.fill: parent
                color: "#ffffff"
                text: qsTr("Настройки")
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    Rectangle{
        anchors.top: toolBar.bottom
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

    DropShadow {
            anchors.fill: toolBar
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 17
            color: "#80000000"
            source: toolBar
        }

//    Rectangle {
//        id: pictureMask
//        x: 0
//        y: 60
//        width: app_width
//        height: 220
//        color: "#ffffff"

//        Image {
//            id: avatar
//            x: 0
//            y: 0
//            width: app_width
//            height: 220
//            source: client.getMyAvatar()//  lientData.getPathAvatar(index) != ""?"file:///" +currentDir+"/" + clientData.getPathAvatar(index):"qrc:/resourses/avatar/lobkov.tif"
////            source: "qrc:/resourses/avatar/lobkov.tif"
//            fillMode: Image.PreserveAspectFit
//        }

//        Rectangle {
//            id: nameMask
//            x: 0
//            y: 180
//            width: app_width
//            height: 40
//            color: colorBlue
//            opacity: customOpacity
//        }

//        Text {
//            id: tbName
//            x: 0
//            y: 180
//            width: 415
//            height: 40
//            color: "#ffffff"
//            text: currentUser.getName()
//            font.pixelSize: 16
//            verticalAlignment: Text.AlignVCenter
//            minimumPixelSize: 16
//            leftPadding: 15
//        }

//        Rectangle {
//            id: chooseAvatarButtonMask
//            x: 414
//            y: 160
//            width: 76
//            height: 60
//            color: "#00000000"

//            Image {
//                id: chooseAvatarImage
//                anchors.fill: parent
//                source: "qrc:/resourses/nastroiki/kopka_obovit`_photo.tif"
//                anchors.leftMargin: 0
//                anchors.topMargin: 0
//                fillMode: Image.PreserveAspectFit
//            }

//            MouseArea{
//                anchors.fill: parent

//                onClicked: {
//                    fileOpenDialog.open()
//                }
//            }
//        }
//    }

    Rectangle {
        id: scrollViewMask
        x: 0
        y: 60
        width: parent.width
        height: 840
        color: colorBlue

        ScrollView{
            property int contentHeightSettings: 1040
            id: scrollSetting
            width: parent.width
            height: 840

            contentHeight: contentHeightSettings
            contentWidth: parent.width
            clip: true

            Settings{

            }
        }
    }
}


