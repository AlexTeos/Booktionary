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

        MyCheckBox {
            id: saveMostPopularMeaningCheckBox
            checkColor: AppSettings.blueLightColor
            text: "The most used meaning"
            font.pixelSize: AppSettings.fontSize_4
        }

        MyCheckBox {
            id: saveWordsOnlyWithExamplesCheckBox
            checkColor: AppSettings.blueLightColor
            text: "Only words with examples"
            font.pixelSize: AppSettings.fontSize_4
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter

            text: qsTr("Save dictionary to")
            font.pixelSize: AppSettings.fontSize_5
        }

        MyPushButton {
            anchors.horizontalCenter: parent.horizontalCenter

            height: AppSettings.buttonNormalHeight
            width: parent.width
            backgroundColor: AppSettings.blueLightColor

            buttonRadius: AppSettings.standartRadius
            text: qsTr("Choose file...")
            fontSize: AppSettings.fontSize_5
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
            if(outputGenerator.generateOutput(fileDialog.currentFile, saveMostPopularMeaningCheckBox.checked, saveWordsOnlyWithExamplesCheckBox.checked))
                swipeView.setCurrentIndex(kDictionaryPage)
        }
        onRejected: {
            console.log("Canceled")
            visible = false
        }
        visible: false
    }
}
