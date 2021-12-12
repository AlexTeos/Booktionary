import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import "MyControls"

ApplicationWindow {
    width: 360
    height: 800
    visible: true
    title: qsTr("Booktionary")

    background: Rectangle {
        z: -1
        anchors.fill: parent
        color: AppSettings.blueSoftColor
    }

    Component.onCompleted: {
        AppSettings.wWidth = Qt.binding(function() {return width})
        AppSettings.wHeight = Qt.binding(function() {return height})
    }

    signal loadFile(string fileName)

    Column {
        anchors.centerIn: parent

        spacing: AppSettings.fontSize_6
        Text {
            text: qsTr("Hello!")
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: AppSettings.fontSize_6
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter

            text: qsTr("Please load file you want\nto convert into dictionary")
            font.pixelSize: AppSettings.fontSize_6
        }

        MyPushButton {
            anchors.horizontalCenter: parent.horizontalCenter

            height: AppSettings.buttonNormalHeight
            width: parent.width
            backgroundColor: AppSettings.blueLightColor

            text: qsTr("Choose file...")
            font.pixelSize: AppSettings.fontSize_6
            onClicked: {
                animate()
                fileDialog.visible = true
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        onAccepted: {
            console.log("You chose: " + fileDialog.currentFile)
            visible = false
            loadFile(fileDialog.currentFile)
        }
        onRejected: {
            console.log("Canceled")
            visible = false
        }
        visible: false
    }
}
