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
        id: navigationButtons
        width: parent.width
        height: AppSettings.fontSize_4*2
        anchors.horizontalCenter: parent.horizontalCenter

        anchors.top: parent.top
        anchors.left: parent.left

        MyPushButton {
            height: AppSettings.buttonSlimHeight
            width: (parent.width) / 2 //- AppSettings.standartMargin

            buttonRadius: AppSettings.standartRadius
            backgroundColor: AppSettings.blueLightColor
            text: qsTr("Back")
            font.pixelSize: parent.height/2
            onClicked: {
                animate()
                swipeView.setCurrentIndex(kStartPage)
            }
        }

        MyPushButton {
            height: AppSettings.buttonSlimHeight
            width: (parent.width) / 2 //- AppSettings.standartMargin
            //anchors.leftMargin: AppSettings.standartMargin

            buttonRadius: AppSettings.standartRadius
            backgroundColor: AppSettings.blueLightColor
            text: qsTr("Save")
            font.pixelSize: parent.height/2
            onClicked: {
                animate()
                swipeView.setCurrentIndex(kSaveDictionaryPage)
            }
        }
    }

    //Rectangle{
    //    color: "green"
    //    anchors.fill: navigationButtons
    //}

    ListView {
        id: dictionaryListView
        width: parent.width * 0.9
        anchors.top: navigationButtons.bottom
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        model: dictionaryModel

        spacing: AppSettings.standartSpacing
        clip: true

        delegate: Rectangle{
            radius: AppSettings.standartRadius
            width: dictionaryListView.width
            height: AppSettings.fontSize_4 * 2
            color: AppSettings.blueDarkColor
            Text {
                anchors.centerIn: parent
                font.pixelSize: parent.height / 2
                color: AppSettings.whiteColor
                text: word
            }
        }
    }
}
