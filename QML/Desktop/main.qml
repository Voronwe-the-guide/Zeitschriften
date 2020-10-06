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
    minimumWidth: 900
    width:cSettings.mainWindowSize.width // .getWindowSize().width
    height: cSettings.mainWindowSize.height //.getWindowSize().height
    title: qsTr("Zeitschriften DB: "+width+"x"+height+" "+cSettings.currentDB)
    onWidthChanged: cSettings.setWindowWidth(width)
    onHeightChanged: cSettings.setWindowHeight(height)
   // var this_component
    function callNewArtikelWindow()
    {
        var this_component = Qt.createComponent("ArtikelWriter.qml").createObject(mainWindow, {isNewOne:true})// artikeleditor.visible = true;
        this_component.nextButtonPressed.connect(restart);
    }

    function callNewZeitschriftWindow()
    {
        var this_component = Qt.createComponent("ZeitschriftWriter.qml").createObject(mainWindow, {isNewOne:true})// artikeleditor.visible = true;
   //     this_component.nextButtonPressed.connect(restart);
    }

    function callNewAusgabeWindow()
    {
        var this_component = Qt.createComponent("AusgabeWriter.qml").createObject(mainWindow, {isNewOne:true})// artikeleditor.visible = true;
   //     this_component.nextButtonPressed.connect(restart);
    }

    function callAusgabeList()
    {
        cListenController.getListOfAusgaben()
        var this_component = Qt.createComponent("AusgabenListe.qml").createObject(mainWindow)// artikeleditor.visible = true;

    }

    function restart()
    {
    //    console.log("Restart");
        callWriter()
    }


    MessageDialog
    {
        id: errorDialog
        width: 400
        height: 300
        title: qsTr("Fehler")
        icon: StandardIcon.Critical

        text:"Hello"
        visible: false
        modality: Qt.ApplicationModal
        onAccepted: {
          visible: false
         }
    }

    Connections
    {
        target: cErrorDisplay
        function onDisplayError(error)
        {
            console.log ("Error output: "+error)
            errorDialog.text = error;
            errorDialog.visible = true;
  //          Qt.createComponent("MessageDisplay.qml").createObject(mainWindow/*, {text:error}*/)// artikeleditor.visible = true;
        }

    }
    Connections
    {
        target: cListenController
        function onNewZeitschriftDetected(zeitschrift)
        {
            Qt.createComponent("ZeitschriftWriter.qml").createObject(mainWindow)// artikeleditor.visible = true;

        }

    }

    Connections
    {
        target: cListenController
        function onNewAusgabeDetected(ausgabe)
        {
            Qt.createComponent("AusgabeWriter.qml").createObject(mainWindow)// artikeleditor.visible = true;

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
            spacing:10
            Button
            {
               id: dbLoadButton
               text: qsTr("Lade DB")
               onClicked: fileDialog.visible = true
               anchors.verticalCenter: parent.verticalCenter
          //     color: "lightblue"
            }
        /*    Item
            {
               width: 10
               height: parent.height
            }
*/
            Rectangle
            {
                id: searchArea
                width: 500
                //anchors.left: dbLoadButton.right
                height: parent.height
                color: "lightgrey"
                Row
                {
                    width: parent.width
                    height: parent.height
                    Rectangle
                    {
                        id: searchtextArea
                        width: parent.width - 50
                        height: searchText.height
                        color: "white"
                      //  anchors.left: parent.left
                        x:10
                       ///anchors.leftMargin: 10

                        anchors.verticalCenter: parent.verticalCenter

                        TextInput
                        {
                            id: searchText
                           font.pixelSize: 15
                            width: parent.width-10
                            anchors.left:parent.left
                            anchors.leftMargin: 5
                            anchors.verticalCenter: parent.verticalCenter
                            verticalAlignment: Text.AlignVCenter

                            height:25//parent.height
                            onAccepted:
                            {
                               // searchButton.click();
                               cListenController.searchArtikel(text);

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
                          // cListenController.getOverview();
                           cListenController.searchArtikel("");

                       }
                       anchors.verticalCenter: parent.verticalCenter
                    }

                }
            }
      /*      Item
            {
               width: 10
               height: parent.height
            }
        */    Button
            {
                id: newEntry
                text: qsTr("Neuer Artikel")
                onClicked:
                {
                    cArtikelEditor.setNewArtikel();
                    mainWindow.callNewArtikelWindow();
                }
                anchors.verticalCenter: parent.verticalCenter
            }
            Button
            {
                id: neueZeitschrift
                text: qsTr("Neue Zeitschrift")
                onClicked:
                {
                    cZeitschriftEditor.setNew();
                    mainWindow.callNewZeitschriftWindow();
                }
                anchors.verticalCenter: parent.verticalCenter
            }
            Button
            {
                id: neueAusgabe
                text: qsTr("Neue Ausgabe")
                onClicked:
                {
                    cAusgabeEditor.setNew();
                    mainWindow.callNewAusgabeWindow();
                }
                anchors.verticalCenter: parent.verticalCenter
            }
            Button
            {
                id: showAusgabenListe
                text: qsTr("Liste der Ausgaben")
                onClicked:
                {
                     mainWindow.callAusgabeList();
                }
                anchors.verticalCenter: parent.verticalCenter
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
        height: parent.height-searchArea.height-zeitschriftenArea.height
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
             height: parent.height
        }
    }


   FileDialog
    {
        id: fileDialog
        title: qsTr("Datenbank auswählen")
        folder: cSettings.currentDB // shortcuts.home
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
             +"\n with the additional exemption that compiling, linking, and/or using OpenSSL is allowed."
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
              +"\n  -------"
               +"\n "
              +"\n This Software uses the OpenSSL-Libraries 1.1.1g released under OpenSSL-License"
              +"\n https://www.openssl.org/ "
              +"\n Libraries where build by FireDaemon: https://kb.firedaemon.com/support/solutions/articles/4000121705"

         onAccepted: {
            visible = false;
         }
   //     Component.onCompleted: visible = true
    }

  AusgabenListe
   {

   }

  /*AusgabeWriter
   {

   }

/*   Window {
       width: Qt.platform.os == "android" ? Screen.width :800
       height: Qt.platform.os == "android" ? Screen.height : 512
       visible: true

       DisplayMap
       {
           anchors.fill: parent
       }



   }
   */

/*ArtikelWriter
{
}
*/
}


