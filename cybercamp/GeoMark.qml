import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: root

    property var textHeader: "геоМетка"
    property var textInfo: "описание"
    property var imagePath: "qrc:/Images/geomark.png"

    x: -25
    y: -25
    width: 50
    height: 50
    color: "#00000000"


    Image {
        source: imagePath
        height: parent.height
        width: parent.width
        x:-25
        y:-25
    }

    Text {
        id: _textHeader
        text: textHeader
        visible: true
        y: 30
        x:-width/2
    }

    MouseArea{
        anchors.fill: parent
        preventStealing: true
        onClicked: {
            _textHeader.visible = !_textHeader.visible
            console.log("click")
        }
    }
}
