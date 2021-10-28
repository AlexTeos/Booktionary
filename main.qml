import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    signal loadFile(string fileName)

    RowLayout {
        Button {
            text: "Load"
            onClicked: {
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
