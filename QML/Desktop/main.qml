import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.12
//import Qt.labs.folderlistmodel 2.1
//import Qt.labs.settings 1.0


ApplicationWindow
{
   id: mainWindow
    visible: true
    minimumHeight: 400
    minimumWidth: 650
    width:cSettings.getWindowSize().width
    height: cSettings.getWindowSize().height
    title: qsTr("Zeitschriften DB: "+width+"x"+height+" "+cSettings.currentDB())
    onWidthChanged: cSettings.setWindowWidth(width)
    onHeightChanged: cSettings.setWindowHeight(height)

    Connections
    {
        target: cErrorDisplay
        onDisplayError:
        {
            Qt.createComponent("MessageDisplay.qml").createObject(mainWindow, {text:error})// artikeleditor.visible = true;
        }
    }

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

        RoundButton
         {
            id: infoButton
            text: "i"
            anchors.right:parent.right
            anchors.rightMargin: 10
            width: 25
            height: 25
            onClicked:
            {
                 messageDialog.visible=true;

            }
            anchors.verticalCenter: parent.verticalCenter
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

   MessageDialog {
        id: messageDialog
        title: "License Information"
        text: "Zeitschriften DB Viewer "
              +"\n (c) by Thorsten Stapel"
              +"\n This Software is licensed under the GNU GENERAL PUBLIC LICENSE Version 3 "
              +"\n\n"
        +"\nBeside this, I would like you to ask to use this software only in good mood"
        +"\n and not for purposes which could harm people, animals, magical creatures or the environment."
         +"\n\n"
         +"\n This Software uses the Qt-Framework Version "+qtversion+" licensed under the LGPL3-License"
        +"\n https://www.qt.io/"
        +"\n "
        +"\n -------"
        +"\n "
        +"\n This Software includes the SQLite-code version "+sqliteversion+" licensed under public domain "
        +"\n https://www.sqlite.org"
        +"\n "
       +"\n  -------"
        +"\n "
       +"\n This Software uses graphics from Linearicons licensed under the CC BY-SA 4.0 license."
       +"\n https://linearicons.com "
       +"\n Linearicons where created by Perxis https://perxis.com"
        onAccepted: {
            visible = false;
         }
   //     Component.onCompleted: visible = true
    }


}


