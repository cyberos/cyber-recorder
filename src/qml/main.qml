import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import Recorder 1.0
import MeuiKit 1.0 as Meui

ApplicationWindow {
    id: root
//    width: 500
//    height: 600

    minimumWidth: 400
    minimumHeight: 550

    visible: true
    title: qsTr("Recorder")

    background: Rectangle {
        color: Meui.Theme.backgroundColor
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
