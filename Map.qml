import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Shapes 1.12

Rectangle {


    function addGeoPoint(x, y){
        var xy=calcXY(x,y)
        drawGeoMark(x,y,"qrc:/Images/geomark.png","Это я","Передвижение")
    }

    function clearGeoMarks(){
        if(_imageMap.data!=null)
            for(var i = 1; i < _imageMap.data.length;i++)
            {
                _imageMap.data[i].destroy()
            }
    }

    function drawGeoMark(x,y,imagepath,header,  info){
        var tmp = tmpGeoMark.createObject(_imageMap,
                                          {
                                              textHeader: header,
                                              textInfo: info,
                                              imagePath: imagepath,
                                              x: x,
                                              y: y,

                                          });
        addPointLine(x,y)

    }

    function drawPoints(points){

        var p =points["0"]
        var p2=points[0]

        var p3=points[77]

        for(var i=0;points[i]!=null;i++){
            var xy = calcXY(points[i].getlongitude(), points[i].getlatitude());
//            if(i===0){
//                _shapePath.startX = xy[0]
//                _shapePath.startY = xy[1]
//            }
//            else
//            {
//                addPointLine(xy[0],xy[1])
//            }
            drawGeoMark(xy[0],xy[1],points[i].getpath(),points[i].getheader(),  points[i].getinfo())

        }
    }

    function addPointLine(x,y){

        if(_shapePath.startX===0 && _shapePath.startY ===0){
            _shapePath.startX = x
            _shapePath.startY = y
            return
        }

            var pathcurve = Qt.createQmlObject('import QtQuick 2.12; PathCurve {}',
                                                           _shapePath);
                        pathcurve.x = x
                        pathcurve.y = y

            _shapePath.pathElements.push(pathcurve)

    }

    function calcXY(x,y){
        //x = 44.9801104
        //y = 37.2526551
        var _dx = 270;//735;
        var _dy = 170//340;

        var _r = 6378137;

        var _g = _r * 3.1415926535897932384626433832795 / 180;

        //var x1 = 44.9803111; //left
        //var y1 = 37.2644784; //bottom

        var x1 = 44.9801416; //left
        var y1 = 37.2635941; //bottom
        var x2 = 44.9807679; //left
        var y2 = 37.2648543; //bottom

        var _m = 1 / Math.cos (y1)
        var lon = _dy / _g * _m
        var lat = _dx / _g



        //        var x2 = x1 + lat/2
        //        var y2 = y1 + lon/2

        //        x1 -= lat/2
        //        y1 -= lon/2
        //x2 = 44.9821104; //right
        //y2 = 37.2579901; //top

        var dx =  _imageMap.width / (x2-x1)
        var dy =  _imageMap.height /(y2-y1)

        var newx = ((x - x1)*dx)
        var newy = ((y - y1)*dy)

        //        tbText.text=((x - x1)*dx) + " " + dy + " " + _imageMap.width;


        var arr  = [(x - x1)*dx, (y - y1)*dy];
        return arr
        //       _rectmark.x = (x - x1)*dx
        //        _rectmark.y = (y - y1)*dy
    }

    id: root
    //    width: app_width
    //    height: app_height

    property int tmpWidth: 506
    property int tmpHeight: 900

    property var colorBlue: "#158BCD"

    property var tmpGeoMark

    //    width: Screen.width
    //    height: Screen.height

    width:  tmpWidth
    height: tmpHeight
    color: colorBlue

    Rectangle{
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
        radius: 10

        Rectangle{
                    width: parent.width
                    height: 40
                    color: colorBlue
                }

        //        z:1
        Rectangle {
            id: rectangle
            x: 0
            y: 0
            width: app_width
            height: 60
            color: colorBlue
            radius: 10
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

    DropShadow {
            anchors.fill: header
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 17
            color: "#80000000"
            source: header
        }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
