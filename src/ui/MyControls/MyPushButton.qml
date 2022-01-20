import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Button {
    property color backgroundColor
    property real buttonRadius

    id: control
    hoverEnabled: false
    height: control.font.pixelSize * 2

    contentItem: Text {
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: control.text
        font.pixelSize: control.font.pixelSize
        color: "white"
    }

    function animate(){
        control_rectangle.color = Qt.darker(backgroundColor, 1.3)
        control_timer.start()
    }

    Timer {
           id: control_timer
           interval: 100
           running: false
           repeat: false
           onTriggered:
           {
               control_rectangle.color = backgroundColor
           }
    }

    background: Rectangle {
        id: control_rectangle
        anchors.centerIn: control

        height: control.height * 0.9
        width: control.width * 0.95

        anchors.horizontalCenter: control.horizontalCenter
        color: control.backgroundColor
        radius: buttonRadius
    }
}
