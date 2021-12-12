import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Button {
    id: control
    hoverEnabled: false
    property color backgroundColor

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
        radius: height * 0.5
        anchors.horizontalCenter: control.horizontalCenter
        color: control.backgroundColor
        width: control.width * 0.95
    }
}
