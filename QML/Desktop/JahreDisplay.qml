import QtQuick 2.0

Item
{

    id: jahreDisplay
    width: 50
    height: 800
    property int fontSize: 20

    property int currentJahr: -1

    Component
    {
        id: jahrComponent
        Rectangle
        {
            width: parent.width
            height: 30
            border.color: "red"
            color: model.index === currentJahr?"lightblue":"transparent"
            radius: 5
            Text
            {
                id: jahr
                text: model.jahr
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: jahreDisplay.fontSize

            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    jahreDisplay.currentJahr = model.index;
                    console.log("Ausgaben request");
                    cArtikelList.deleteAll();
                    cAusgabenList.getAusgabenForJahr(model.jahr);
                }

            }
        }
    }

    ListView
    {
        width: parent.width
        height: parent.height
        model: cJahreList
        delegate: jahrComponent
    }

}
