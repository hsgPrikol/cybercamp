import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: achivments
    width: app_width
    height: app_height
    color: "#e6177bd9"

    property var listAchivmentImage: ["qrc:/ach/d1.png", "qrc:/ach/d2.png","qrc:/ach/d3.png","qrc:/ach/d4.png","qrc:/ach/d5.png", "qrc:/ach/d6.png","qrc:/ach/d7.png","qrc:/ach/d8.png","qrc:/ach/d9.png","qrc:/ach/d10.png","qrc:/ach/d11.png", "qrc:/ach/d12.png"]

    property var listAchivmentText: ["Увлажнитель","Климатолог","Освятитель","Cyber-Mandarin","Организатор","Успешный фермер","Пунктуал","Кактусовод","Ru-gramchik","Подаван","First-blood","Вместе на век"]

    Text {
        id: text2
        x: 20
        y: 5
        width: app_width
        height: 50
        color: "#ffffff"
        text: qsTr("Дата регистрации: 20.05.2022")// + client.getMyBirthDate()

        font.pixelSize: 16
        verticalAlignment: Text.AlignTop

        Text {
            id: text3
            x: 182
            y: 43
            width: 102
            height: 20
            color: "#ffffff"
            text: qsTr("Уровень: 5")//+client.getMyLvl()
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    ProgressBar {
        id: progressBar
        x: 119
        y: 69
        width: 268
        height: 36
        value: 0.24//client.getMyExp()/client.getExpToNextLvl()
    //#464f56 графитовый
        background: Rectangle{
            width: parent.width
            height: 36
            color: "#e6177bd9"
            border.width: 1
            border.color: "white"
            radius: 5
        }

        contentItem: Item {
            implicitWidth: 200
            implicitHeight: 4

            Rectangle {
                width: progressBar.visualPosition * parent.width
                height: parent.height
                radius: 5
                color: "white"
            }
        }
    }

    Text {
        id: text4
        x: 219
        y: 106
        width: 68
        height: 28
        color: "#ffffff"
        text: "24/100"//client.getMyExp()+"/"+client.getExpToNextLvl()
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }



    Rectangle {
        id: hatAccountMask
        height: 50
        color: "#00000000"


        property var nameText: "Аккаунт"
        x: 0
        y: 140
        width: app_width
        Text {

            x: 191
            y: 0
            width: 125
            height: 50
            color: "#ffffff"
            text: "Найденные растения"
            font.pixelSize: 18
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle {

            x: 8
            y: 24
            width: 142
            height: 2
            color: "#ffffff"
        }

        Rectangle {

            x: 348
            y: 24
            width: 151
            height: 2
            color: "#ffffff"
        }
    }

    Rectangle {
        id: rectangle2
        x: 0
        y: 212
        width: app_width
        height: 120
        color: "#00000000"

        RowLayout {
            id: rowLayout
            x: 0
            y: 0
            width: app_width
            height: 120
            spacing: 10


            CircleProgressBar {
                id: cirkleprogressbar


                value: 0.7
                valueProgress: "140/200"
                namePlant: "Музыка"

                Image {
                    id: image
                    x: 40
                    y: 40
                    width: 40
                    height: 40
                    source: "qrc:/ach/t1.png"
//                    sourceSize.height: 35
//                    sourceSize.width: 35
                    fillMode: Image.PreserveAspectFit
                }
            }

            CircleProgressBar {
                id: cirkleprogressbar1
                value: 0.81
                valueProgress: "130/160"
                namePlant: "Танцы"

                Image {
                    id: image1
                    x: 40
                    y: 40
                    width: 40
                    height: 40
                    source: "qrc:/ach/t2.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            CircleProgressBar {
                id: cirkleprogressbar2
                valueProgress: "13/100"
                namePlant: "Робототехника"

                Image {
                    id: image2
                    x: 40
                    y: 40
                    width: 40
                    height: 40
                    source: "qrc:/ach/t3.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            CircleProgressBar {
                id: cirkleprogressbar3
                width: 120
                height: 120
                valueProgress: "2/50"
                namePlant: "Медицина"
                value: 0.04

                Image {
                    id: image3
                    x: 40
                    y: 40
                    width: 40
                    height: 40
                    source: "qrc:/ach/t4.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }

    Rectangle {
        id: rectangle3
        x: 0
        y: 332
        width: app_width
        height: 120
        color: "#00000000"

        CircleProgressBar {
            id: cirkleprogressbar4
            x: 56
            y: 0
            value: 0.17
            valueProgress: "10/60"
            namePlant: "Картография"

            Image {
                id: image4
                x: 40
                y: 40
                width: 40
                height: 40
                source: "qrc:/ach/t5.png"
                sourceSize.height: 68
                sourceSize.width: 67
                fillMode: Image.Stretch
            }
        }

        CircleProgressBar {
            id: cirkleprogressbar5
            x: 193
            y: 0
            valueProgress: "8/70"
            value: 0.12
            namePlant: "Театр"

            Image {
                id: image5
                x: 40
                y: 40
                width: 40
                height: 40
                source: "qrc:/ach/t6.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        CircleProgressBar {
            id: cirkleprogressbar6
            x: 333
            y: 0
            value: 0.02
            valueProgress: "1/80"
            namePlant: "Химия"

            Image {
                id: image6
                x: 40
                y: 40
                width: 40
                height: 40
                source: "qrc:/ach/t7.png"
                fillMode: Image.PreserveAspectFit
            }
        }
    }

    Rectangle {
        id: hatAccountMask1
        height: 50
        color: "#00000000"


        property var nameText: "Аккаунт"
        x: 0
        y: 458
        width: app_width
        Text {

            x: 191
            y: 0
            width: 125
            height: 50
            color: "#ffffff"
            text: "Достижения"
            font.pixelSize: 18
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle {

            x: 8
            y: 24
            width: 177
            height: 2
            color: "#ffffff"
        }

        Rectangle {

            x: 316
            y: 26
            width: 183
            height: 2
            color: "#ffffff"
        }
    }

    Flow {
        id: flow1
        x: 20
        y: 514
        width: 490
        height: 128
        spacing: 20
        Repeater{
            model: listAchivmentImage.length
            Image {
                width: 60
                height: 60
                source: listAchivmentImage[index]

                MouseArea{
                    id: mouseImageTool
                    anchors.fill: parent

                    hoverEnabled: true
                }

                ToolTip{
                    Text {

                        text: listAchivmentText[index]
                        color: "white"
                    }

                    visible: mouseImageTool.containsMouse ? true : false

                    background: Rectangle{
                        width: parent.width
                        height: parent.height

                        color: "#00000000"
                        radius: 5
                    }

                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/
