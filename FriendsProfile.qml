import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: contactPageMain

    property string namePlant
    property int idPlant
    property string pathAvatar

    property string nameContact
    property int indexContact

    x: 50
    y: 8
    width: 448
    height: 84
    color: noColor
    //                opacity: 0.7
    //    border.color: mouseContacts.containsPress ? "white" : noColor
//        border.width: 1

    Rectangle {
        id: contactPageAvatar
        x: 0
        y: 0
        width: 84
        height: parent.height
        color: noColor

        Rectangle {
            id: contactPageAvatarMask
            x: 10
            y: 10
            width: 64
            height: 65
            color: "#ffffff"
            radius: contactPageAvatarMask.width / 2


            Image {
                id: image1
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
                source: "qrc:/Questroom/" + (Math.floor(Math.random() * 7)+1) +".tif"
                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: parent
                }
            }
        }

        Rectangle {
            x: 80
            y: 0
            width: 367
            height: 84
            color: noColor

            Text {
                property int fontSize: 20
                id: textName
                anchors.fill: parent
                text: nameContact
                font.pixelSize: textName.fontSize
                color: "white"
                verticalAlignment: Text.AlignVCenter
                leftPadding: 10
            }
        }
    }

    MouseArea {
        id: mouseContacts
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {

        }
    }
}
