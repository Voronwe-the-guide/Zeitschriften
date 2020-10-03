import QtQuick 2.0
import QtQuick.Dialogs 1.3
MessageDialog
{
    id: messageDialog
    width: 400
    height: 300
    text:"Hello"
    visible: true
    modality: Qt.ApplicationModal
    onAccepted: {
        messageDialog.close()
     }
}
