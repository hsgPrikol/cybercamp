import QtQuick 2.0
import QtMultimedia 5.12
import QtGraphicalEffects 1.0

Rectangle{
    id: root
    //    width: app_width
    //    height: app_height

    property int tmpWidth: 506
    property int tmpHeight: 900

    property var colorBlue: "#177bd9"

    property var tmpGeoMark

    property var imgPath
    property var img

    //    width: Screen.width
    //    height: Screen.height

    width:  tmpWidth
    height: tmpHeight




    Rectangle{
        id: header
        width: parent.width
        height: 60
        color: colorBlue
        radius: 10
        z:1

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
                    text: "Plant-GO"
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



    Image {
        id: mainPhone
//            opacity: 0.3
        anchors.fill: parent
        source: "qrc:/pictureRegistration/anime_anime_girls_Touhou_Kochiya_Sanae-71537.jpg"
//        width: parent.width
//        height: parent.height

        Rectangle {
            opacity: 0.9
            color: "black"
            anchors.fill: parent

        }
    }

    Rectangle {
        id: cameraMask
        x: 0
        y: 66
        width: 506
        height: 460
        color: "#00000000"

        Camera{
            id: camera

            imageCapture {
                onImageCaptured: {
                    imagePreview.source = preview
                    imagePreview.visible = true
                    img = preview
                }

                onImageSaved: {
                    imgPath = path
                    planAPI.createRequestFromPath(imgPath)
                }
            }
        }

        ListView {
            anchors.fill: parent

            model: QtMultimedia.availableCameras
            delegate: Text {
                text: modelData.displayName

                MouseArea {
                    anchors.fill: parent
                    onClicked: camera.deviceId = modelData.deviceId
                }
            }
        }

        VideoOutput {
            id:videoOutput
            anchors.fill: parent
            source: camera
            focus : visible // to receive focus and capture key events when visible

            Image {
                id: imagePreview
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                visible: false
            }
        }
    }

    Image {
        id: makePhoto
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height * 0.8
        source: "qrc:/ach/makePhoto.png"
        fillMode: Image.PreserveAspectFit
        width: 100
        height: 100

        MouseArea {
            anchors.fill: parent

            onClicked: {
                camera.imageCapture.capture();
            }
        }
    }

    function onDataReceived(plant_name, probability, url, value)
    {
        value_camera_neuron = value;
        plant_name_camera_neuron = plant_name
        url_camera_neuron = url
        probability_camera_neuron = probability
        img_camera_neuron = img

        loaderCamp.sourceComponent = resultPlantGoComponent;
    }

    Component.onCompleted: {
        planAPI.dataReceived.connect(onDataReceived)
    }
}
