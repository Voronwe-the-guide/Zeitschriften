import QtQuick 2.14
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
Window
{
    id: zeitschriftenListeWindow
    width: 600
    height: 400
    visible: true
    modality:Qt.ApplicationModal
    property bool readOnlyMode: false


    title: "Edit Zeitschrift"
    flags:  Qt.Window | Qt.WindowSystemMenuHint
            | Qt.WindowTitleHint | Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint
     |Qt.WindowCancelButtonHint
            | Qt.WindowMaximizeButtonHint// | Qt.WindowStaysOnTopHint



    Rectangle {
        color: "yellow"
        width: 100; height: 100

        MouseArea {
            anchors.fill: parent
            onClicked: console.log("clicked yellow")
        }

        Rectangle {
            color: "blue"
            width: 50; height: 50

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked: {
                    console.log("clicked blue")
                    mouse.accepted = false
                }
            }
        }
    }

}
