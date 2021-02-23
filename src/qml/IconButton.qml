import QtQuick 2.4
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0

MouseArea {
    id: control
    width: 64
    height: width

    property alias source: icon.source
    property alias overlayColor: colorOverlay.color

    Image {
        id: icon
        anchors.fill: parent
        sourceSize: Qt.size(width, height)

        ColorOverlay {
            id: colorOverlay
            anchors.fill: icon
            source: icon
            color: "#000000"
            opacity: control.pressed ? 0.3 : 0
            Behavior on opacity {
                NumberAnimation {
                    duration: 90
                    easing.type: Easing.InOutCubic
                }
            }
        }
    }
}
