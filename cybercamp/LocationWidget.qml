import QtQuick 2.0

Rectangle {
    id: root
        property int dfltWidth: 506
        property int dfltHeight: 900

        width: dfltWidth
        height: dfltHeight

        color: "#cc000000"

        MouseArea{
            anchors.fill: parent

            onClicked: {
                z = -1
//                loaderCamp =
            }
        }

        LocationDay{
            MouseArea{
                anchors.fill: parent
            }
        }
}
