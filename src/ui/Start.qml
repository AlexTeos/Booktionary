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
            buttonRadius: AppSettings.standartRadius
            text: qsTr("Choose file...")
            fontSize: AppSettings.fontSize_6
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
            if(inputParser.loadFile(fileDialog.currentFile))
                swipeView.setCurrentIndex(kDictionaryPage)
        }
        onRejected: {
            console.log("Canceled")
            visible = false
        }
        visible: false
    }
}
