import QtQuick 2.11
import QtQuick.Controls 2.2

CheckBox {
    property string checkColor

    id: control
    hoverEnabled: false

    contentItem: Text {
        text: control.text
        font.pixelSize: control.font.pixelSize
        color: color
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
    
    indicator: Rectangle {
        implicitWidth: control.font.pixelSize
        implicitHeight: control.font.pixelSize
        x: control.leftPadding
        y: control.height / 2 - height / 2
        radius: height * 0.2
        border.color: color

        Rectangle {
            width: parent.height * 0.7
            height: width
            x: (parent.height - height) / 2
            y: x
            radius: height * 0.2
            color: checkColor
            visible: control.checked
        }
    }
}
