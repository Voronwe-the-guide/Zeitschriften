import QtQuick 2.15
import QtQuick.Controls 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.3
import "Helper"
Item
{
    id: artikelListDisplay
    width: 480
    height: 800
    property int fontSize: 20
   // property int currentIndex: 0
    property int oldIndex: -1;
       focus: true
    onVisibleChanged:
    {
        if (visible)
        {

        }
    }


    function readList()
    {
        artikelList.focus = true
        cListenController.recallArtikelList()
        artikelList.currentIndex = oldIndex
        artikelList.positionViewAtIndex(oldIndex,ListView.Center)
        oldIndex = -1
    }

    function callEdit(dbIndex)
    {
        oldIndex = artikelList.currentIndex;
        cArtikelEditor.setArtikelForUpdate(dbIndex);
       var this_component = Qt.createComponent("ArtikelWriter.qml").createObject(artikelListDisplay)// artikeleditor.visible = true;

  //     cAusgabeEditor.setForUpdate(dbIndex)
   //     var this_component = Qt.createComponent("AusgabeWriter.qml").createObject(ausgabenDisplay)// artikeleditor.visible = true;
        this_component.saveButtonPressed.connect(readList);
    }



    Connections
    {
        target: cArtikelList
        function onListEmpty()
        {
        //    artikelList.positionViewAtIndex(0,artikelList.Beginning);
            artikelList.positionViewAtBeginning();
            artikelList.currentIndex = -1;
           // console.log("Empty: Go to 0");
        }
        function onElementAdded(index)
        {
        //    artikelList.positionViewAtIndex(0,artikelList.Beginning);
            if (index === 1)
            {
                artikelList.positionViewAtBeginning();
                artikelList.currentIndex = 0;
             //   console.log("Go to 0");
            }
        }
    }

    Connections
    {
        target: cArtikelEditor
        function onDisplayArtikelIndex(listIndex)
        {
            if (listIndex>=0)
            {
                artikelList.currentIndex = listIndex;
                artikelList.positionViewAtIndex(artikelList.currentIndex,ListView.Center)

            }
        }
    }

    Component
    {
        id: artikelComponent
        Rectangle
        {
            id: showArtikel
            width: artikelListDisplay.width-50
            height: artikelDisplay.height+artikelSeperator.height
            color: model.index == artikelList.currentIndex?"lightblue": "white" //"#EBEBEB"/"white"

            MouseArea
            {
                anchors.fill: parent
                propagateComposedEvents: true

                onClicked:
                {
                   // ausgabe.color= "red"
                    artikelList.focus = true
                    artikelList.currentIndex = model.index
                    artikelList.positionViewAtIndex(model.index,ListView.Center)
                 }
            }
            Artikel
            {
                id: artikelDisplay
                width: parent.width
                zeitschrift:model.zeitschrift
                jahrgang: model.jahr
                ausgabe:model.ausgabe
                seite: model.seite
                rubrik: model.rubrik
                kurztext: model.kurztext
                ueberschrift: model.ueberschrift
                zusammenfassung: model.zusammenfassung
                stichworte: model.schlagworte
                author:model.autor
                fotos: model.fotos
                land: model.land
                notizen: model.notizen
                coordinates: model.koordinate
                language: model.sprache
        //        hasGPS: true
                onEditButtonPressed:
                {
                    artikelList.currentIndex = model.index
                    callEdit(model.dbIndex)

                 //   editElement.active = true;
                }
                onDeleteButtonPressed:
                {
                    deleteDialog.dBDeleteIndex = model.dbIndex;
                    deleteDialog.visible = true;
                }

            }
            Item
            {
                id: artikelSeperator
                width:parent.width
                height: 40
                anchors.top: artikelDisplay.bottom
            Rectangle
               {
                   id: artikelSeperatorLine


                   width: parent.width
                   height: 5
                   color: "black"
               }
            }
          /*     MouseArea
               {
                   anchors.fill: parent
                   propagateComposedEvents: true
                   onClicked:
                   {
                       artikelList.currentIndex = model.index
                     }
               }
*/
        }
    }

    ArtikelMap
    {
        id: map
        width: 600 //parent.width
        height:300
        anchors.horizontalCenter: parent.horizontalCenter
        onItemSelected:
        {
           var listIndex=cArtikelList.getIndexInList(dbIndex);
            artikelList.currentIndex = listIndex;
            artikelList.positionViewAtIndex(artikelList.currentIndex,ListView.Center)

        }
    }

    ListView
    {
       id: artikelList
        width: parent.width-20
        height: parent.height-map.height
        anchors.top: map.bottom
         currentIndex: 0
         x: 20
        model: cArtikelList
        delegate: artikelComponent
        focus: true
        clip: true


       onCurrentIndexChanged:
        {
   //        console.log("Current Index: "+currentIndex);
           if (currentIndex>=0)
           {
                map.currenUniqueIndex = cArtikelList.getDBIndex(currentIndex)// currentItem.dbIndex
           }
           else
           {
               map.currenUniqueIndex = -1;
           }
        }
      //  snapMode: ListView.SnapToItem
      //  highlightRangeMode: ListView.StrictlyEnforceRange

       flickableDirection: Flickable.VerticalFlick
         boundsBehavior: Flickable.StopAtBounds
         Layout.fillWidth: true
          Layout.fillHeight: true
          highlightFollowsCurrentItem : false
          preferredHighlightBegin: height / 2 - 100 // 100 being item height / 2
          preferredHighlightEnd: height / 2 + 100 // 100 being item height / 2


       //   focus: true
          Keys.onUpPressed:
          {
              if (artikelList.currentIndex>0)
              {
                  artikelList.currentIndex--
                  artikelList.positionViewAtIndex(artikelList.currentIndex,ListView.Center)
              }
          } // scrollBar.decrease()
          Keys.onDownPressed:
          {
        //      console.log("down pressed");
              if (artikelList.currentIndex<artikelList.count-1)
              {
                  artikelList.currentIndex++
                  artikelList.positionViewAtIndex(artikelList.currentIndex,ListView.Center)
              }
          }
          Keys.onReturnPressed:
          {
              callEdit(model.getDBIndex(artikelList.currentIndex))

          }

/* taken from: https://forum.qt.io/topic/88248/custom-scrollbar-to-add-top-bottom-buttons-windows-style/3 */
        ScrollBar.vertical: ScrollVertical {id: scrollBar}

    }


    MessageDialog
    {
        id: deleteDialog
        width: 400
        height: 300
        title: qsTr("Löschen")
        icon: StandardIcon.Question
        property int dBDeleteIndex:-1
        text:qsTr("Wirklich löschen?")
        visible: false
        modality: Qt.ApplicationModal
        standardButtons:StandardButton.No| StandardButton.Yes
        onNo:
        {
            console.log("No pressed for "+dBDeleteIndex);
            visible: false
        }
        onYes:
        {
            console.log("Yes pressed for "+dBDeleteIndex);
            cListenController.deleteArtikel(dBDeleteIndex);
            visible: false
        }
    }


}
