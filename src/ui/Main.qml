import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "MyControls"

ApplicationWindow {
    width: 360
    height: 800
    visible: true
    title: qsTr("Booktionary")

    Component.onCompleted: {
        AppSettings.wWidth = Qt.binding(function() {return width})
        AppSettings.wHeight = Qt.binding(function() {return height})
    }

    SwipeView {
          id: swipeView
          anchors.fill: parent

          interactive: false

          Start{
              id:startPage
          }
      }
}
