import QtQuick 2.0

Rectangle {
    id: root
    //    width: app_width
    //    height: app_height

    property int tmpWidth: 506
    property int tmpHeight: 900

    //    width: Screen.width
    //    height: Screen.height

    width:  tmpWidth
    height: tmpHeight
    color: colorBlue

    Scroll{
        {
        x: 0
        y: 60
        width: parent.width
        height: parent.height - 60
        color: colorBlue

        Image {
            id: _imageMap

            width: parent.width
            height: parent.height
            source: "qrc:/Images/map.png"
            smooth: false
            fillMode: Image.PreserveAspectCrop

            property var coorXstart: 0
            property var coorYstart: 0

            clip: true

            Shape {
                id: _shape
                ShapePath {
                    id: _shapePath
                    strokeColor: "black"
                    strokeWidth: 3
                    fillColor: "transparent"

                }

            }

            Component.onCompleted: {
                tmpGeoMark= Qt.createComponent("GeoMark.qml");
                geodd.onUpdateGeo.connect(addGeoPoint);

                var count = gp.getTestGeoPoints()
                drawPoints(count)
            }

            WheelHandler {
                target: _imageMap
                acceptedDevices: PointerDevice.AllPointerTypes
                orientation: Qt.Vertical

                property: "scale"
                rotationScale: 0.1

                targetTransformAroundCursor: false
            }



            onScaleChanged: {
                if(_imageMap.scale <= 1){
                    _imageMap.scale =1

                }

                coords.onReleased(null)

                if(_imageMap.scale> 2)
                    _imageMap.scale=2
            }

        }

        MouseArea {
            id: coords
            anchors.fill: parent
    //        preventStealing: true
            property var isClicked: false
            property var cX: 0
            property var cY: 0

            onPositionChanged: {
                if(isClicked){
                    _imageMap.x += mouseX - cX
                    _imageMap.y += mouseY - cY

                    cX = mouseX
                    cY = mouseY
                }
            }

            onReleased: {
                isClicked=false

                if(_imageMap.x  - _imageMap.width*(_imageMap.scale-1)/2 > 0)
                    _imageMap.x= _imageMap.width*(_imageMap.scale-1)/2
                if(_imageMap.y - _imageMap.height*(_imageMap.scale-1)/2 > 0)
                    _imageMap.y= _imageMap.height*(_imageMap.scale-1)/2

                if(_imageMap.x + _imageMap.width  + (_imageMap.width*(_imageMap.scale - 1)/2) < parent.width)
                    _imageMap.x= (parent.width- _imageMap.width * _imageMap.scale)/2
                if(_imageMap.y + _imageMap.height  + (_imageMap.height*(_imageMap.scale - 1)/2) < parent.height)
                    _imageMap.y= (parent.height - _imageMap.height * _imageMap.scale)/2
            }

            onPressed: {
                cX = mouseX
                cY = mouseY
                isClicked= true
            }
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
}
