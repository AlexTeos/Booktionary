pragma Singleton
import QtQuick 2.15

Item {
    id: appSettings
    property int wHeight
    property int wWidth

    // Colors
    readonly property color blueDarkColor: "#021b35"
    readonly property color blueLightColor: "#0a82ff"
    readonly property color blueSoftColor: "#cee6ff"

    // Font sizes
    readonly property real fontSize_1: fontSize_8 * 0.2
    readonly property real fontSize_2: fontSize_8 * 0.4
    readonly property real fontSize_3: fontSize_8 * 0.5
    readonly property real fontSize_4: fontSize_8 * 0.6
    readonly property real fontSize_5: fontSize_8 * 0.7
    readonly property real fontSize_6: fontSize_8 * 0.8
    readonly property real fontSize_7: fontSize_8 * 0.9
    readonly property real fontSize_8: (wWidth + wHeight) * 0.03

    // Some other values
    readonly property real buttonSlimHeight: wHeight * 0.05
    readonly property real buttonNormalHeight: wHeight * 0.08
}
