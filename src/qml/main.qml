import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import Recorder 1.0
import MeuiKit 1.0 as Meui

Meui.Window {
    id: root

    minimumWidth: 400
    minimumHeight: 550
    width: 400
    height: 550

    visible: true
    title: qsTr("Recorder")

    headerBar: Rectangle {
        color: "transparent"
        anchors.fill: parent
        anchors.rightMargin: -140

        Label {
            text: root.title
            color: Meui.Theme.titleBarTextColor
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
        }
    }

    HomePage {
        id: homePage

        onRecordClicked: {
            AudioRecorder.record()
            stackView.push(recordPage)
        }
    }

    RecordPage {
        id: recordPage
        visible: false

        onFinished: {
            stackView.pop()
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: homePage
    }
}
