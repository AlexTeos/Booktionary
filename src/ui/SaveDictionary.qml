import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import "MyControls"

Page {

    signal loadFile(string fileName)

    background: Rectangle {
        z: -1
        anchors.fill: parent
        color: AppSettings.blueSoftColor
    }

    Column {
        anchors.centerIn: parent

        spacing: AppSettings.fontSize_6

        Text {
            anchors.horizontalCenter: parent.horizontalCenter

            text: qsTr("Save dictionary to")
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
        fileMode: FileDialog.SaveFile
        onAccepted: {
            console.log("You chose: " + fileDialog.currentFile)
            swipeView.setCurrentIndex(kStartPage)
        }
        onRejected: {
            console.log("Canceled")
            visible = false
        }
        visible: false
    }
}
