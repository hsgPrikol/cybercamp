import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: main_window
    visible: true
    title: qsTr("CyberCamp")

    property int app_width: width
    property int app_height: height

    property int tmpWidth: 506
    property int tmpHeight: 900

    property var colorBlue: "#158BCD"

//    width: Screen.width
//    height: Screen.height

    width:  tmpWidth
    height: tmpHeight

    Loader{
        id: loaderCamp

        sourceComponent: addCoinComponent
    }

    Component{
        id: lilBookComponent
        LilBook{
            anchors.fill: main_window
        }
    }

    Component{
        id: addCoinComponent
        AddCoin{

        }
    }

    Component{
        id: cameraQRCodeComponent
        CameraQRCode{

        }
    }

    Component{
        id: usercharComponent

        Userchat{

        }
    }

    Component{
        id: settingsComponent

        SettingsProfile{

        }
    }

    Component{
        id: registrationComponent

        Registration{

        }
    }

    Component{
        id: plannerComponent

        Planner{

        }
    }

    Component{
        id: autorizationComponent

        Autorization{

        }
    }

    Component{
        id: friendsComponent

        FriendList{

        }
    }


    Component{
        id: dialogsComponent

        DialogsList{

        }
    }

    Component{
        id: mapComponent

        Map{

        }
    }

    Component{
        id: cybershopComponent

        Cybershop{

        }
    }

    Burgermenu{
        id: burgermenu
        x: -tmpWidth
    }
}
