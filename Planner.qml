import QtQuick 2.0
import QtQuick.Controls 2.12

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

    property var month_list: ["20.05.22","21.05.22","22.05.22"]

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#000000"
        anchors.fill: parent
        Image {
            id: mainPhone
            opacity: 0.6
            anchors.fill: parent
            source: "qrc:/pictureRegistration/anime_anime_girls_Touhou_Kochiya_Sanae-71537.jpg"
        }
    }

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
                    text: "Расписание"
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

    ScrollView{
        //        anchors.left: root.left
        //        anchors.leftMargin: 13
        anchors.top: header.bottom
        width: app_width
        height: app_height - header.height
        clip: true
        contentHeight: month.cheight
        contentWidth: app_width

        Column{
//                        anchors.horizontalCenter: parent.horizontalCenter
            anchors.left: parent.left
            anchors.leftMargin: 15
            width: app_height
            spacing: 10

            Repeater{
                model: 3
                Plannermonth {
                    id: month
                    textR: month_list[index]
                    currentIndex: index
                }
            }
        }
    }
}
