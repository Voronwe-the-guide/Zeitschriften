import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.0
import QtQuick.Controls 2.12

Window
{
    visible: true
    width:800
    height: 800
    title: qsTr("Zeitschriften DB: "+width+"x"+height+" "+cSettings.currentDB())

    Button
    {
       id: dbLoadButton
       text: qsTr("Lade DB")
       onClicked: fileDialog.visible = true
    }

    Item
    {
        id: searchArea
        width: parent.width
        anchors.left: dbLoadButton.right
        height: 50
        TextInput
        {
            width: parent.width
            height: parent.height
            onAccepted:
            {
                if (text == "")
                {
                    cListenController.getJahre();
                }
                else
                {
                    cListenController.searchArtikel(text);
                }
            }
        }
    }

    Item
    {
        id: listDisplayArea
        width: parent.width
        height: parent.height-searchArea.height
        anchors.top: searchArea.bottom
        clip: true

        JahreDisplay
        {
            id: jahre
            width: 100
            height: parent.height
        }

        ArtikelListDisplay
        {
            id: artikel
            anchors.left: jahre.right
             width: parent.width - jahre.width
        }
    }


    FileDialog
    {
        id: fileDialog
        title: qsTr("Datenbank auswählen")
        folder: shortcuts.home
        selectMultiple: false
        onAccepted: {
            cSettings.setCurrentDB(fileDialog.fileUrl.toString())
            visible: false;
        }
        onRejected: {
           visible: false
        }
    }
}
