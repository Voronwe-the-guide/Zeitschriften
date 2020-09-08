import QtQuick 2.0
import QtQuick.Controls 2.9
import QtQuick.Layouts 1.3
Item
{
    id: artikelListDisplay
    width: 480
    height: 800
    property int fontSize: 20

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
        //    artikelList.positionViewAtIndex(0,ListView.Beginning);
            artikelList.positionViewAtBeginning()
            console.log("Go to 0");
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
               Rectangle
               {
                   id: artikelSeperator
                   anchors.top: artikelDisplay.bottom
                   width: parent.width
                   height: 5
                   color: "black"
               }

        }
    }



    ListView
    {
       id: artikelList
        width: parent.width-20
        height: parent.height
        x: 20
        model: cArtikelList
        delegate: artikelComponent
        onCountChanged:
        {
            artikelList.positionViewAtBeginning()
        }
        Tracer{}

        flickableDirection: Flickable.VerticalFlick
         boundsBehavior: Flickable.StopAtBounds
         Layout.fillWidth: true
          Layout.fillHeight: true

        ScrollBar.vertical: ScrollBar { width: 30}
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
