import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    property color backgroundColor
    property color color
    property real progress
    property real total
    property real processed
    property real radius

    id: control

    Rectangle {
        anchors.fill: parent

        color: control.backgroundColor
        radius: control.radius
    }

    Rectangle {
        anchors.left: control.left
        height: control.height
        anchors.verticalCenter: control.verticalCenter
        width: control.width * (processed / total)
        color: control.color
        radius: control.radius
    }

    Text {
        anchors.centerIn: control
        text: processed + "/" + total
        font.pixelSize: control.height
        color: "white"
    }
}
