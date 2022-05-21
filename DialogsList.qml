import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: listDialog


    property var colorBlue: "#177bd9"

    property int dfltWidth: 506
    property int dfltHeight: 900

    width: dfltWidth
    height: dfltHeight

    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"

    property var tmpNewDialog

    property var testDialogs:[
    ["Общий чат","Отряд орлёнок", "Лариса Владимировна", "Новостной чат"],
    ["Выбираем кино для просмотра", "В море глубоко не заплываем!!!", "Хорошо покушал? а то родители беспокоятся", "Вечером просмотр кинофильма"],
    ["12:37","10:42","Вчера","20.05"]
    ]

    color: noColor

    property int countRep: 6
    function addNewDialogs()
    {
        var tmpDialog = tmpNewDialog.createObject(columnDialogs,
                                                  {



                                                  });

        repDialogs.itemAdded(++countRep ,tmpDialog)
        console.log(repDialogs.model)

    }

    function redrawDialogs()
    {
        if(columnDialogs.data!=null)
        for(var i = 1; i < columnDialogs.data.length;i++)
        {
            columnDialogs.data[i].destroy()
        }

        let countD = clientData.getCountDialogs();

        var tmp;

        for(var i=0;i<countD;i++){
            tmp = tmpNewDialog.createObject(columnDialogs,
                                            {
                                                nameFamilia: clientData.getNameDialog(i),
                                                //                        avatarClients: "file:///C:/Users/rota/Documents/build-SuperDesign-MinGW64-Debug/" + clientData.getPathAvatar(index)
                                                avatarClients: clientData.getPathAvatar(i) != ""?"file:///" +currentDir+"/" + clientData.getPathAvatar(i):"qrc:/resourses/avatar/cop.tif",

                                                lastMessageUser: clientData.getTextLastMessage(i),
                                                timeMessage: clientData.getDateLastMessage(i),
                                                isChecked: clientData.getIsCheckedLastMessage(i),
                                                isGroup: clientData.getDialogIsGroup(i),
                                                isOnline: clientData.getDialogIsOnline(i),
                                                countUnChecked: clientData.getDialogCountUnChecked(i),
                                                indexInListDialogs: i
                                            });
        }


        console.log(tmp.dfltHeight)

        //        scrollView.contentHeight = countD * (columnDialogs.spacing + tmp.dfltHeight)
        //        columnDialogs.children = []
        //        scrollView.contentHeight=150;
        //        scrollView.height=150;
        //        scrollView.focus=true
        //showDialog()

    }

    function showDialog()
    {
        loader.sourceComponent  = userChat
    }



    Rectangle{
        id: root
        anchors.fill: parent
        width: parent.width
        height: parent.height
        color: "black"

        Image {
            id: mainPhone
            anchors.fill: parent
            source: ""
            opacity: 0.7
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

        DropShadow {
            anchors.fill: rectangle
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 17
            color: "#80000000"
            source: rectangle
        }

        property int sizeDialogs: 10

        ScrollView {
            id: scrollView
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            //            anchors.fill: parent
            anchors.top: rectangle.bottom
            anchors.right: rectangle.right
            anchors.left: rectangle.left
            anchors.bottom: parent.bottom
            //            background: Rectangle{color: "red"}
            //            contentHeight: 10000
            contentWidth: parent.width
            clip: true

            Component.onCompleted: {

            }

            Column {
                id: columnDialogs
                anchors.fill: parent
                spacing: 10

                Rectangle{
                    width: parent.width
                    height: 1
                    color: noColor
                }

                Repeater {
                     model: 4

                     Dialogs{
                         avatarClients: "qrc:/Questroom/" + (Math.floor(Math.random() * 7)+1) +".tif"
                         timeMessage: testDialogs[2][index]
                         nameFamilia: testDialogs[0][index]
                         isOnline: index==2
                         isGroup: index!=2
                         isChecked: index!=0
                         lastMessageUser: testDialogs[1][index]
                         countUnChecked: 1

                     }
                }
            }
        }

        //        Rectangle {
        //            id: addNewDialogMask
        //            x: 434
        //            y: 828
        //            width: 72
        //            height: 72

        //            anchors.right: root.right
        //            anchors.rightMargin: 15

        //            anchors.bottom: root.bottom
        //            anchors.bottomMargin: 15

        //            radius: addNewDialogMask.width / 7

        //            opacity: customOpacity

        //            color: addNewDialogMouse.containsPress ? Qt.lighter(biruzoviu) : biruzoviu

        //            Image {
        //                id: addNewDialog
        //                x: 11
        //                y: 11
        //                width: 50
        //                height: 50
        //                source: "qrc:/resourses/create chat_2.tif"
        //                fillMode: Image.PreserveAspectFit
        //            }

        //            MouseArea{
        //                id: addNewDialogMouse
        //                anchors.fill: parent

        //                onClicked: {
        //                    //                    loader.sourceComponent = contactsList


        //                    var str = "123213"
        //                    testMap.createNewDialog(str)


        //                    console.log("loader.source = contactsList")
        //                }
        //            }
        //        }
    }

    Component.onCompleted: {
        console.log(" Component.onCompleted list dialogs");
        //testMap.onCreateNewDialog.connect(addNewDialogs)
        tmpNewDialog = Qt.createComponent("Dialogs.qml");
        client.onUpdateAllChats.connect(redrawDialogs);
        redrawDialogs();
    }
}
