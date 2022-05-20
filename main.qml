import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
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

        sourceComponent: autorizationComponent
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

    Burgermenu{
        id: burgermenu
        x: -tmpWidth
    }
}
