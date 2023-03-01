import QtQuick 2.15

Image {
    id: loadIcon
    anchors {
        top: parent.top
        topMargin: parent.height / 30
        horizontalCenter: parent.horizontalCenter
    }
    width: parent.width * 0.55
    fillMode: Image.PreserveAspectFit
    source: ""
}

