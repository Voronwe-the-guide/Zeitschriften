import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.0
import QtQuick.Controls 2.12

Window
{
    visible: true
    minimumHeight: 400
    minimumWidth: 600
    width:cSettings.getWindowSize().width
    height: cSettings.getWindowSize().height
    title: qsTr("Zeitschriften DB: "+width+"x"+height+" "+cSettings.currentDB())
    onWidthChanged: cSettings.setWindowWidth(width)
    onHeightChanged: cSettings.setWindowHeight(height)

    Item
    {
        id: topArea
        width: parent.width
        height: 50

        Row
        {
            anchors.fill: parent
            Button
            {
               id: dbLoadButton
               text: qsTr("Lade DB")
               onClicked: fileDialog.visible = true
               anchors.verticalCenter: parent.verticalCenter
          //     color: "lightblue"
            }
            Item
            {
               width: 10
               height: parent.height
            }

            Rectangle
            {
                id: searchArea
                width: 500
                //anchors.left: dbLoadButton.right
                height: parent.height
               // Tracer {}
                color: "lightgrey"
                Row
                {
                    anchors.fill: parent
                    Rectangle
                    {
                        id: searchtextArea
                        width: parent.width - 50
                        height: searchText.height
                        color: "white"
                        anchors.left: parent.left
                        anchors.leftMargin: 10

                        anchors.verticalCenter: parent.verticalCenter
                     //   Tracer {bc: "green"}

                        TextInput
                        {
                            id: searchText
                           font.pixelSize: 15
                        //    Tracer{bc: "green"}
                            width: parent.width-10
                            anchors.left:parent.left
                            anchors.leftMargin: 5
                            anchors.verticalCenter: parent.verticalCenter
                            verticalAlignment: Text.AlignVCenter

                            height:25//parent.height
                            onAccepted:
                            {
                               // searchButton.click();
                                if (text == "")
                                {
                                    cListenController.getOverview();
                                }
                                else
                                {
                                    cListenController.searchArtikel(text);
                                }

                            }
                        }
                    }
                   RoundButton
                    {
                       id: searchButton
                       text: "X"
                       anchors.left:searchtextArea.right
                       anchors.leftMargin: 5
                       width: 25
                       height: 25
                       onClicked:
                       {
                           searchText.text="";
                           cListenController.getOverview();

                       }
                       anchors.verticalCenter: parent.verticalCenter
                    }

                }
            }
        }
    }
   ZeitschriftenDisplay
    {
        id: zeitschriftenArea
        anchors.top: topArea.bottom


    }

    Item
    {
        id: listDisplayArea
        width: parent.width
        height: parent.height-searchArea.height
        clip: true
        anchors.top: zeitschriftenArea.bottom

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
        folder: cSettings.currentDB() // shortcuts.home
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
