import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.0
import QtQuick.Controls 2.12

Window {
    visible: true
    width:800
    height: 800
    title: qsTr("Zeitschriften DB: "+width+"x"+height+" "+cSettings.currentDB())
  /*  Rectangle
    {
        anchors.fill: parent
        color: "blue"
    }
*/
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
      /*  AusgabenDisplay
        {
            id: ausgaben
            width: 50
            height: parent.height
            anchors.left: jahre.right
        }
    */
        ArtikelListDisplay
         {
            id: artikel
            anchors.left: jahre.right
             width: parent.width - jahre.width// -ausgaben.width
             Tracer{}
        }
    }


    FileDialog
    {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        selectMultiple: false
        onAccepted: {
            cSettings.setCurrentDB(fileDialog.fileUrl.toString())
            visible: false;
        }
        onRejected: {
           visible: false
        }
     //   Component.onCompleted: visible = true
    }
}
