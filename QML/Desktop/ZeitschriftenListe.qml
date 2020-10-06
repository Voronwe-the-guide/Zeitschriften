import QtQuick 2.14
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import ZeitschriftLib 1.0
Window
{
    id: zeitschriftenListeWindow
    property int windowType: WindowNames.WINDOW_LIST_ZEITSCHRIFT
    width:cSettings.getWindowSize(windowType).width // .mainWindowSize.width // .getWindowSize().width
    height: cSettings.getWindowSize(windowType).height //.mainWindowSize.height //.getWindowSize().height
    onWidthChanged: cSettings.setWindowWidth(windowType,width)
    onHeightChanged: cSettings.setWindowHeight(windowType,height)
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
