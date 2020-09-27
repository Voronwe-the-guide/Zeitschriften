import QtQuick 2.0
import QtQuick.Controls 2.9
import QtQuick.Layouts 1.3
Item
{
    id: artikelListDisplay
    width: 480
    height: 800
    property int fontSize: 20
   // property int currentIndex: 0

    onVisibleChanged:
    {
        if (visible)
        {

        }
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

    Component
    {
        id: artikelComponent
        Item
        {
            id: showArtikel
            width: artikelListDisplay.width-50
            height: artikelDisplay.height+artikelSeperator.height
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
                     cArtikelEditor.setArtikelForUpdate(model.dbindex);
                   Qt.createComponent("ArtikelWriter.qml").createObject(artikelListDisplay)// artikeleditor.visible = true;
                 //   editElement.active = true;
                }
                onDeleteButtonPressed:
                {
                    cListenController.deleteArtikel(model.dbindex);
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
    }

    ListView
    {
       id: artikelList
        width: parent.width-20
        height: parent.height-map.height
        anchors.top: map.bottom
        x: 20
        model: cArtikelList
        delegate: artikelComponent
        clip: true
       onCurrentIndexChanged:
        {
           //console.log("Current Index: "+currentIndex);
        }
      //  snapMode: ListView.SnapToItem
      //  highlightRangeMode: ListView.StrictlyEnforceRange
        flickableDirection: Flickable.VerticalFlick
         boundsBehavior: Flickable.StopAtBounds
         Layout.fillWidth: true
          Layout.fillHeight: true

       //   focus: true
          Keys.onUpPressed: scrollBar.decrease()
          Keys.onDownPressed: scrollBar.increase()

/* taken from: https://forum.qt.io/topic/88248/custom-scrollbar-to-add-top-bottom-buttons-windows-style/3 */
        ScrollBar.vertical: ScrollBar
        { id: scrollBar;
            width: 30
         policy: ScrollBar.AlwaysOn
         topPadding: 25 + 2
                     bottomPadding: 25 + 2

                     Rectangle {
                         width: parent.width
                         height: 25
                         color: upButton.pressed ? "lightblue" : "transparent"
                         Image
                         {
                             anchors.fill: parent
                             source:"qrc:/Images/chevron-up.svg"
                         }

                        // opacity: vbar.contentItem.opacity

                         MouseArea {
                             id: upButton
                             anchors.fill: parent

                             SmoothedAnimation {
                                 target: artikelList
                                 property: "contentY"
                                 running: upButton.pressed
                                 velocity: 2000
                                 to: 0
                             }

                          /*   onReleased: {
                                 if (artikelList.currentIndex > 0)
                                 {
                                     artikelList.currentIndex--;
                                     artikelList.positionViewAtIndex(artikelList.currentIndex,ListView.Beginning)
                                 }

                             }
                             */
                         }
                     }

                     Rectangle {
                         y: parent.height - height
                         width: parent.width
                         height: 25
                         color: downButton.pressed ? "lightblue" : "transparent"
                    //     opacity: vbar.contentItem.opacity
                        Image
                        {
                            anchors.fill: parent
                            source:"qrc:/Images/chevron-down.svg"
                        }
                         MouseArea {
                             id: downButton
                             anchors.fill: parent

                             SmoothedAnimation {
                                 target: artikelList
                                 property: "contentY"
                                 running: downButton.pressed
                                 to: artikelList.contentHeight - artikelList.height
                                 velocity: 2000
                             }


                        /*     onReleased: {

                                 if (artikelList.currentIndex < artikelList.count-1)
                                 {
                                     artikelList.currentIndex++;
                                     artikelList.positionViewAtIndex(artikelList.currentIndex,ListView.Beginning)
                                 }

                            }
                            */
                         }
                     }
        }
    }

/*
    ApplicationWindow {
        id: window
        width: 400
        height: 400
        visible: true

        artikelList {
            id: artikelList

            model: 100
            anchors.fill: parent

            ScrollBar.vertical: ScrollBar {
                id: vbar

                topPadding: 16 + 2
                bottomPadding: 16 + 2


            }

            delegate: ItemDelegate {
                text: modelData
                width: parent.width
            }
        }
    }

 /*   Loader
    {
        id: editElement
        sourceComponent: editArtikel
        active: false
    }

    Component
    {
        id: editArtikel
        ArtikelWriter
        {
             id: artikeleditor
           // visible: false
        }
    }
*/

}
