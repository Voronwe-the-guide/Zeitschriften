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

   /*     Rectangle
        {
           color: "lightblue"
            id: artikelDisplay
            width: artikelListDisplay.width
            height: zusammenfassungDisplay.height + searchInfoDisplay.height + shortInfoDisplay.height
            Item
            {
                id: searchInfoDisplay
                width: parent.width
                height: jahrDisplay.contentHeight+fontSize/2
                property int fontSize: artikelListDisplay.fontSize //+ 5
                TextEdit
                {
                    id: jahrDisplay
                    width: parent.width/3
                    height: parent.height
                    text: model.jahr
                    font.pixelSize: parent.fontSize
                }
                TextEdit
                {
                    id: ausgabeDisplay
                    width: parent.width/3
                    height: parent.height
                    anchors.left: jahrDisplay.right
                    text: model.ausgabe
                    font.pixelSize: parent.fontSize
                }
                TextEdit
                {
                    id: seiteDisplay
                    width: parent.width/3
                    height: parent.height
                    anchors.left: ausgabeDisplay.right
                    text:  zusammenfassungDisplay.height+" > "+zusammenfassungDisplay.contentHeight//model.seite
                    font.pixelSize: parent.fontSize

                }


            }
            Rectangle
            {
                color: "red"
                id: shortInfoDisplay
                width: parent.width
                height: kurzTextDisplay.contentHeight+fontSize/2
                 anchors.top:searchInfoDisplay.bottom
                 property int fontSize: artikelListDisplay.fontSize //+ 10
                TextEdit
                {
                    id: kurzTextDisplay
                    width: parent.width*1/3
                    height: parent.height
                    anchors.left: jahrDisplay.right
                    text: model.kurztext
                    font.pixelSize:  parent.fontSize
                }
                TextEdit
                {
                    id: ueberschriftDisplay
                    width: parent.width*2/3
                    height: parent.height
                    anchors.left:kurzTextDisplay.right
                    text: model.ueberschrift
                    font.pixelSize:  parent.fontSize
                }

            }
            TextArea
            {
                id: zusammenfassungDisplay
                width: parent.width
                height: zusammenfassungDisplay.contentHeight+artikelListDisplay.fontSize//>50?zusammenfassungDisplay.contentHeight:50  //parent.height-shortInfoDisplay.height-searchInfoDisplay.height
                anchors.top: shortInfoDisplay.bottom
                text: model.zusammenfassung
                font.pixelSize: artikelListDisplay.fontSize
                wrapMode: TextEdit.Wrap
                Tracer{}
            }
        }

        */


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
