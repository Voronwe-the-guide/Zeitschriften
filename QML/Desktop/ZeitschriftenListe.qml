import QtQuick 2.14
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Qt.labs.qmlmodels 1.0
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



     TableModel {
         id: zeitschrifenModel
        TableModelColumn { display: "name" }
        TableModelColumn { display: "color" }

        rows: [
            {
                "name": "cat",
                "color": "black"
            },
            {
                "name": "dog",
                "color": "brown"
            },
            {
                "name": "bird",
                "color": "white"
            }
        ]
    }

        ListView {
        anchors.fill: parent
        //columnSpacing: 1
        //rowSpacing: 1
        clip: true
        model: cZeitschriftenList

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            Tracer{}
            Text {
                text: model.zeitschrift
            }
        }
}
}
