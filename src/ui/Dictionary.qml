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

    Row{
        width: parent.width * 0.9

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: parent.width * 0.1 / 2

        MyPushButton {
            height: AppSettings.buttonSlimHeight
            width: parent.width / 2
            backgroundColor: AppSettings.blueLightColor

            text: qsTr("Back")
            font.pixelSize: AppSettings.fontSize_4
            onClicked: {
                animate()
                swipeView.setCurrentIndex(kStartPage)
            }
        }

        MyPushButton {
            height: AppSettings.buttonSlimHeight
            width: parent.width / 2
            backgroundColor: AppSettings.blueLightColor

            text: qsTr("Save")
            font.pixelSize: AppSettings.fontSize_4
            onClicked: {
                animate()
            }
        }
    }
}
