import QtQuick 2.0

Item
{

    id: ausgabenDisplay
    width: 50
    height: 800
    property int fontSize: 20

    property int currentAusgabe: -1

    Connections
    {
        target: cAusgabenList
        onListEmpty:
        {
            currentAusgabe = -1;
        }
    }

Tracer {}
    Component
    {
        id: ausgabeComponent
        Rectangle
        {
            width: parent.width
            height: 30
            border.color: "red"
            color: model.index === currentAusgabe?"lightblue":"transparent"
            radius: 5
            Text
            {
                id: ausgabe
                text: model.ausgabe
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: ausgabenDisplay.fontSize

            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    ausgabenDisplay.currentAusgabe = model.index;
                    console.log("Artikel request");
                    cArtikelList.getArtikelForAusgabe(model.jahr, model.ausgabe);

                }

            }


        }
    }

    ListView
    {
        width: parent.width
        height: parent.height
        model: cAusgabenList
        delegate: ausgabeComponent

        onCountChanged:
        {
            if (count == 0)
            {
                ausgabenDisplay.currentAusgabe = -1;
            }
        }
    }

}
