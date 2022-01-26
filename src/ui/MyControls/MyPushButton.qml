import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

MouseArea {
    property color backgroundColor
    property real buttonRadius
    property string text
    property real fontSize
    property string animatedIcon

    id: control
    hoverEnabled: false
    height: fontSize * 2

    Rectangle {
        id: control_rectangle
        anchors.centerIn: control

        height: control.height
        width: control.width

        anchors.horizontalCenter: control.horizontalCenter
        color: control.backgroundColor
        radius: buttonRadius
    }

    Text {
        anchors.centerIn: control
        text: control.text
        font.pixelSize: control.fontSize
        color: "white"
        visible: control.text !== ""
    }

    AnimatedImage {
        anchors.centerIn: control
        height: parent.height
        fillMode: Image.PreserveAspectFit
        visible: control.animatedIcon !== ""
        source: control.animatedIcon === "" ? "" : "../" + control.animatedIcon
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
}
