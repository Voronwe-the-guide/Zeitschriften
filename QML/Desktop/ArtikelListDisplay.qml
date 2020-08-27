import QtQuick 2.0
import QtQuick.Controls 2.9
Item
{
    id: artikelListDisplay
    width: 480
    height: 800
    property int fontSize: 20
    Component
    {
        id: artikelComponent
        Item
        {
            id: showArtikel
            width: parent.width
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

    }

}
