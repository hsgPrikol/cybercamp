import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0


Rectangle {
    id: root
    //    width: app_width
    //    height: app_height

    property int tmpWidth: 506
    property int tmpHeight: 900

    property var colorBlue: "#158BCD"

    //    width: Screen.width
    //    height: Screen.height

    width:  tmpWidth
    height: tmpHeight
    Rectangle{
        id: header
        width: parent.width
        height: 60
        color: colorBlue

        //        z:1
        Rectangle {
            id: rectangle
            x: 0
            y: 0
            width: app_width
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
                    id: arrow
                    x: 30
                    y: 13
                    width: 39
                    height: 35
                    source: "qrc:/Raspisanie/burger.tif"
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
                    text: "Карта"
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
                    //                    source: "qrc:/picture/luppa.tif"
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea {
                    anchors.fill: parent
                }
            }
        }
    }

    Image {
        id: image
        x: 0
        y: 60
        width: 506
        height: 840
        source: "qrc:/qtquickplugin/images/template_image.png"
        fillMode: Image.PreserveAspectFit
    }
}
