import QtQuick 2.0

Item
{

    id: ausgabenDisplay
    width: 50
    height: visible?ausgabenListe.count* 30:0

    property int fontSize: 20

    property int currentAusgabe: -1

    Connections
    {
        target: cAusgabenList
        function onListEmpty()
        {
            currentAusgabe = -1;
        }
    }

    Component
    {
        id: ausgabeComponent
        Rectangle
        {
            id: ausgabeElement
            width: ausgabenDisplay.width
            height: 30

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
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked:
                {
                    if (mouse.button == Qt.RightButton)
                    {
                //        cAusgabeEditor.ZeitschriftForUpdate(model.dbIndex)
                //        Qt.createComponent("ZeitschriftWriter.qml").createObject(zeitschriftenDisplay)// artikeleditor.visible = true;
                    }
                    else
                    {
                        ausgabenDisplay.currentAusgabe = model.index;
                    //   console.log("Artikel request");
                        cListenController.getArtikelForAusgabe(model.zeitschrift,model.jahr, model.ausgabe);
                    }
                }
            }
        }
    }

    ListView
    {
       id: ausgabenListe
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
