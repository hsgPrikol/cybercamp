import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle{
    id: root

    function scannerQRCode()
    {
        burgermenu.closeNavDrawer();
        loaderCamp.sourceComponent = cameraQRCodeComponent;

    }

    function shedule()
    {

        loaderCamp.sourceComponent = plannerComponent;

        burgermenu.closeNavDrawer();
        console.log("shedule")
    }

    function messandger()
    {
//        dateLeft.setIsFromGoto(false)
//        loaderCamp.
        loaderCamp.sourceComponent = dialogsComponent;
        burgermenu.closeNavDrawer();
        console.log("messandger")
    }

    function newsFeed()
    {
//        loader.sourceComponent = plannerComponent
        burgermenu.closeNavDrawer()
        console.log("newsFeed")
    }

    function quests()
    {
        loaderCamp.sourceComponent = cameraPlantGoComponent
        burgermenu.closeNavDrawer()
        console.log("quests")
    }

    function babyBook()
    {
//        loader.sourceComponent = cyberShopComponent
        burgermenu.closeNavDrawer()
        console.log("babyBook")
    }

    function whyuuuuchka()
    {
//        loader.sourceComponent = articlesComponent
        burgermenu.closeNavDrawer()
       console.log("whyuuuuchka")
    }

    function mapCapms()
    {
        loaderCamp.sourceComponent = mapComponent;
        burgermenu.closeNavDrawer();
        console.log("mapCapms");
    }

    function cyberShop()
    {
        loaderCamp.sourceComponent = cybershopComponent;
        burgermenu.closeNavDrawer();
        console.log("cyberShop")
    }

    function friends()
    {
        loaderCamp.sourceComponent = friendsComponent;
        burgermenu.closeNavDrawer();
        console.log("friends")
    }

    property var functionMenuElementArray: [shedule, messandger,friends, newsFeed, quests, babyBook, whyuuuuchka, mapCapms, cyberShop,scannerQRCode]

    property int fontSize: 20
    property int sizeHeightMenuElement: 60
    property int dfltWidthElementMenu: 337
    property color noColor: "#00000000"

    property var textArray: ["Расписание", "Мессенджер", "Друзья", "Лента новостей", "Квеструм", "Книжка-малышка", "Почемучка", "Карта лагеря", "Cyber-магазин", "QR-Code"]

    property var pictureArray: ["qrc:/Burger/Raspisanie.tif", "qrc:/Burger/Messenger.tif", "qrc:/Burger/Friends.tif", "qrc:/Burger/Lenta.tif", "qrc:/Burger/Questroom.tif", "qrc:/Burger/Knijka_malyshka.tif", "qrc:/Burger/Pochemuchka.tif","qrc:/Burger/Maps.tif","qrc:/Burger/Cyber_magazine.tif"]


    width: dfltWidthElementMenu
    height: sizeHeightMenuElement
    color: mouse.containsMouse ? Qt.darker(biruzoviu) : noColor

    Rectangle {
        id: rectangle
        x: 20
        y: 0
        width: 60
        height: 60
        color: "#00000000"

        Image {
            id: image
            height: 30
            anchors.fill: parent

            anchors.leftMargin: 5
            anchors.topMargin: 5
            anchors.rightMargin: 5
            anchors.bottomMargin: 5
            fillMode: Image.PreserveAspectCrop
        }
    }

    Rectangle {
        id: rectangle1
        x: 101
        y: 0
        width: 198
        height: 60
        color: "#00000000"

        Text {
            id: text1
            anchors.fill: parent
            color: "#ffffff"
            font.pixelSize: fontSize
            verticalAlignment: Text.AlignVCenter
        }
    }

    MouseArea{
        id: mouse
        anchors.fill: parent

        hoverEnabled: true

        onClicked: {
            functionMenuElementArray[index]()
        }
    }

    Component.onCompleted: {
        text1.text = textArray[index]
        image.source = pictureArray[index]
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:4}
}
##^##*/
