import QtQuick 2.0
import QtQuick.Dialogs 1.3
MessageDialog
{
    id: messageDialog
    text:"Hello"
    visible: true
    modality: Qt.ApplicationModal
    onAccepted: {
        messageDialog.close()
     }
}
