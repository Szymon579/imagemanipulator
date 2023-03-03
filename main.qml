import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0

import "ui/assets"
import "ui/LeftBar"
import "ui/ImgArea"
import "ui/Tile"
import "ui/JsonMaker/JsonMaker.js" as JsonMaker


Window {
    width: 800
    height: 600 //600
    visible: true
    title: qsTr("Image Manipulator")


    LeftBar{
        id: ui

        Tile {
            id: loadIcon
            source: "qrc:/ui/assets/open_file.png"
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    file_dialog.open()
                }
            }
        }

        Rectangle {
            id: scrollRect
            clip: true
            width: parent.width
            color: "black"
            anchors {
                top: loadIcon.bottom
                topMargin: parent.height / 30
                bottom: saveIcon.top
                bottomMargin: parent.height / 30
            }


            ScrollView {
                id: scrollUi
                width: parent.width
                height: parent.height

                //clip: false
                contentItem:

                    Flickable {
                    contentHeight: rotateIcon.height * 11 //happy 260
                    width: parent.width
                    boundsBehavior: Flickable.DragOverBounds

                    Rectangle {
                        color: "transparent"
                        width: parent.width
                        height: parent.height

                        Tile {
                            id: rotateIcon
                            source: "qrc:/ui/assets/rotate_right.png"
                            anchors.top: parent.top  //loadIcon.bottom
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: imageProcessor.rotateImage()
                            }
                        }

                        Tile {
                            id: hmirrorIcon
                            source: "qrc:/ui/assets/h_mirror.png"
                            anchors.top: rotateIcon.bottom
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: imageProcessor.hMirrorImage()
                            }
                        }

                        Tile {
                            id: vmirrorIcon
                            source: "qrc:/ui/assets/v_mirror.png"
                            anchors.top: hmirrorIcon.bottom
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: imageProcessor.vMirrorImage()
                            }
                        }

                        Tile {
                            id: blackWhiteIcon
                            source: "qrc:/ui/assets/black_white.png"
                            anchors.top: vmirrorIcon.bottom
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: imageProcessor.bwImage()
                            }
                        }

                        Tile {
                            id: excessIcon1
                            source: "qrc:/ui/assets/black_white.png"
                            anchors.top: blackWhiteIcon.bottom
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: imageProcessor.bwImage()
                            }
                        }

                        Tile {
                            id: excessIcon2
                            source: "qrc:/ui/assets/black_white.png"
                            anchors.top: excessIcon1.bottom
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: imageProcessor.bwImage()
                            }
                        }

                        Tile {
                            id: excessIcon3
                            source: "qrc:/ui/assets/black_white.png"
                            anchors.top: excessIcon2.bottom
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: imageProcessor.bwImage()
                            }
                        }
                        Tile {
                            id: sliderIcon
                            source: "qrc:/ui/assets/sliders.png"
                            anchors.top: excessIcon3.bottom
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: rgbPopup.open();
                            }
                        }



                    } // rectangle closing tag

                } // flickable closing tag

            } // scrollView closing tag

        } // scrollRect closing tag



        Image {
            id: saveIcon
            anchors {
                bottom: parent.bottom
                bottomMargin: parent.height / 30
                horizontalCenter: parent.horizontalCenter
            }
            width: parent.width * 0.55
            fillMode: Image.PreserveAspectFit
            source: "qrc:/ui/assets/save_file.png"
            MouseArea {
                anchors.fill: parent
                onClicked: save_file_dialog.open()
                cursorShape: Qt.PointingHandCursor
            }
        }

    } // left bar closing tag


    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    ImgArea {
        id: imgArea
        Image {
            id: image
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            width: parent.width * 0.90
            height: parent.height * 0.90
            fillMode: Image.PreserveAspectFit
            source: imageProcessor.imgUrl

        }
    }

    Popup {
            id: rgbPopup
            dim: false
            parent: sliderIcon
            x: Math.round(parent.width) * 1.4
            y: Math.round(parent.height - (height / 1.5)) // /3
            width: sliderIcon.width * 4
            height: sliderIcon.height * 3
            background: Rectangle {
                    color: "black"
                    border.color: "transparent"
            }

            modal: true
            focus: false
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

            Rectangle {
                id: redRect
                width: parent.width
                height: parent.height / 3
                color: "red"

                Slider {
                    id: redSlider
                    width: parent.width
                    height: parent.height

                    from: 0
                    to: 255
                    value: 128
                    stepSize: 1
                    live: false
                    onValueChanged: {
                        var obj = JsonMaker.export2json(redSlider.value,
                                    greenSlider.value, blueSlider.value)
                        jsonHandler.makeJsonObject(obj)
                        imageProcessor.colorTransformImage()
                    }
                }
            }

            Rectangle {
                id: greenRect

                parent: redRect
                width: parent.width
                height: parent.height
                color: "green"
                anchors {
                    top: redRect.bottom
                }

                Slider {
                    id: greenSlider
                    width: parent.width
                    height: parent.height

                    from: 0
                    to: 255
                    value: 128
                    stepSize: 1
                    live: false
                    onValueChanged: {
                        var obj = JsonMaker.export2json(redSlider.value,
                                    greenSlider.value, blueSlider.value)
                        jsonHandler.makeJsonObject(obj)
                        imageProcessor.colorTransformImage()
                    }
                }
            }

            Rectangle {
                id: blueRect

                parent: greenRect
                width: parent.width
                height: parent.height
                color: "blue"
                anchors {
                    top: greenRect.bottom
                }

                Slider {
                    id: blueSlider
                    width: parent.width
                    height: parent.height

                    from: 0
                    to: 255
                    value: 128
                    stepSize: 1
                    live: false
                    onValueChanged: {
                        var obj = JsonMaker.export2json(redSlider.value,
                                    greenSlider.value, blueSlider.value)
                        jsonHandler.makeJsonObject(obj)
                        imageProcessor.colorTransformImage()
                    }
                }
            }

    } //popup closing tag


    FileDialog {
        id: file_dialog
        selectMultiple: false
        selectFolder: false
        folder: shortcuts.pictures
        onAccepted: {
            imageProcessor.setUrl(file_dialog.fileUrl)
            imageProcessor.loadImage()
        }
        title: "Choose a file"
        nameFilters: [ "Image files (*.jpg *.png)",
                    "All files (*)" ]
    }

    FileDialog {
        id: save_file_dialog
        selectMultiple: false
        selectFolder: false
        folder: shortcuts.pictures
        selectExisting: false
        onAccepted: {
            imageProcessor.saveImage(save_file_dialog.fileUrl)
        }
        title: "Save file"
        nameFilters: [ "Image files (*.jpg *.png)",
                    "All files (*)" ]
    }

} //Window closing tag
