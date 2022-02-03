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

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: AppSettings.fontSize_1
        spacing: AppSettings.fontSize_1

        Row{
            id: navigationButtons
            Layout.fillWidth: true
            height: AppSettings.fontSize_4*2

            MyPushButton {
                height: AppSettings.buttonSlimHeight
                width: (parent.width) / 2

                buttonRadius: AppSettings.standartRadius
                backgroundColor: AppSettings.blueLightColor
                text: qsTr("Back")
                fontSize: parent.height/2
                onClicked: {
                    animate()
                    swipeView.setCurrentIndex(kStartPage)
                    dictionaryModel.reset()
                }
            }

            MyPushButton {
                height: AppSettings.buttonSlimHeight
                width: (parent.width) / 2

                buttonRadius: AppSettings.standartRadius
                backgroundColor: AppSettings.blueLightColor
                text:      if(dictionaryModel.state === 0) qsTr("Translate")
                      else if(dictionaryModel.state === 1) qsTr("")
                      else qsTr("Save")

                animatedIcon: if(dictionaryModel.state === 1) "res/wait.gif"
                              else ""
                fontSize: parent.height/2
                onClicked: {
                    animate()
                         if(dictionaryModel.state === 0) dictionaryModel.translate()
                    else if(dictionaryModel.state === 2) swipeView.setCurrentIndex(kSaveDictionaryPage)

                }
            }
        }

        MyProgressBar {
            id: translationProgressBar
            height: AppSettings.fontSize_4
            radius: AppSettings.standartRadius
            visible: dictionaryModel.state === 1
            Layout.fillWidth: true
            color:"green"
            backgroundColor:"black"
            total: dictionaryListView.count
            processed: dictionaryModel.translatedCount
        }

        ListView {
            id: dictionaryListView
            Layout.fillWidth: true
            Layout.fillHeight: true

            model: dictionaryModel

            spacing: AppSettings.standartSpacing
            clip: true

            delegate:
                Rectangle {
                    height: delegateColumn.height
                    width: delegateColumn.width
                    radius: AppSettings.standartRadius
                    color: AppSettings.blueDarkColor
                    z:-1

                    Column {
                        id: delegateColumn
                        width: dictionaryListView.width
                        spacing: AppSettings.fontSize_1
                        padding: AppSettings.fontSize_1
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.pixelSize: AppSettings.fontSize_4
                            color: AppSettings.whiteColor
                            text: word
                        }
                        Text {
                            font.pixelSize: AppSettings.fontSize_2
                            color: AppSettings.whiteColor
                            text: meanings.join("\n")
                            wrapMode: Text.WordWrap
                            width: parent.width - parent.padding * 2
                            visible: meanings.length > 0
                        }
                    }

                    Rectangle {
                        anchors.margins: AppSettings.fontSize_1
                        anchors.right: parent.right
                        anchors.top: parent.top
                        radius: AppSettings.fontSize_2
                        width: radius
                        height: radius
                        visible: dictionaryModel.state !== 0
                        color:       if(translationState === 0) "yellow"
                                else if(translationState === 1) "green"
                                else "red"
                    }
                }
        }
    }
}
