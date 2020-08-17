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
        Rectangle
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

    }

    ListView
    {
        width: parent.width
        height: parent.height
        model: cArtikelList
        delegate: artikelComponent
    }

}
