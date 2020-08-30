import QtQuick 2.0
import QtQuick.Controls 2.12
Item
{
    id: artikelDisplay

    width: 600
    height: showColumn.height


    property string zeitschrift:""
    signal zeitschriftEdit(var newText)
    property string jahrgang:""
    signal jahrgangEdit(var  newText)
    property string ausgabe:""
    signal ausgabeEdit(var newText)
    property string seite: ""
    signal seiteEdit(var  newText)
    property string rubrik: ""
    signal rubrikEdit(var newText)
    property string kurztext: ""
    signal kurztextEdit(var  newText)
    property string ueberschrift: ""
    signal ueberschriftEdit(var newText)
    property string zusammenfassung: ""
    signal zusammenfassungEdit(var newText)
    property string stichworte:""
    signal stichworteEdit(var newText)
    property string author:""
    signal authorEdit(var newText)
    property string fotos:""
    signal fotosEdit(var newText)
    property string land:""
    signal landEdit(var newText)
    property bool   hasGPS: true

    property bool readOnlyMode: true

    signal editButtonPressed();

    function startFocus()
    {
        magazinArea.focus = true;
    }


    Column
    {
        id: showColumn
        width: parent.width
        height: allgemeineInfo.height + headline.height + detail.height + textInfo.height + countryInfo.height
        property int basicHeight: 25
        Item
        {
            id: allgemeineInfo
            width: parent.width
            height: showColumn.basicHeight
            Row
            {
                anchors.fill: parent
                IconWithText
                {
                    id: magazinArea
                    text: artikelDisplay.zeitschrift
                    iconSource: "qrc:/Images/magazin.svg" //"png"
                    toolTip: qsTr("Magazin")
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.zeitschriftEdit(newText)}

                }
                IconWithText
                {
                    id: yearArea
                    text: artikelDisplay.jahrgang
                    iconSource: "qrc:/Images/year.svg"//.png"
                    toolTip: qsTr("Jahr")
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.jahrgangEdit(newText)}
                 }

                IconWithText
                {
                   id: editionArea
                   text: artikelDisplay.ausgabe
                   iconSource: "qrc:/Images/edition.svg"  //.png"
                   toolTip: qsTr("Ausgabe")
                   readOnly: artikelDisplay.readOnlyMode
                   onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.ausgabeEdit(newText)}
                }
                IconWithText
                {
                   id:pageArea
                   text: artikelDisplay.seite
                   iconSource: "qrc:/Images/page.svg"  //.png"
                   toolTip: qsTr("Seite")
                   readOnly: artikelDisplay.readOnlyMode
                   onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.seiteEdit(newText)}
                }
                IconWithText
                {
                   id: rubrikArea
                   text: artikelDisplay.rubrik
                   iconSource: "qrc:/Images/rubrik.svg" //.png"
                   toolTip: qsTr("Rubrik")
                   readOnly: artikelDisplay.readOnlyMode
                   onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.rubrikEdit(newText)}
                }
            }
        }
        Item
        {
            id: countryInfo
            width: parent.width
            height: showColumn.basicHeight
            IconWithText
            {
                id: countyArea
                text: artikelDisplay.land
                iconSource:  "qrc:/Images/land.svg" //png"
                toolTip: qsTr("Land")
                readOnly: artikelDisplay.readOnlyMode
                onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.landEdit(newText)}
            }

        }

        Item
        {
            id: textInfo
            width: parent.width
            height: authorArea.height + photoArea.height
            Column
            {
               anchors.fill: parent
               IconWithText
                {
                    id: authorArea
                     height: showColumn.basicHeight
                    text: artikelDisplay.author
                    iconSource:  "qrc:/Images/writer.svg" //.png"
                    toolTip: qsTr("Text von")

                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.authorEdit(newText)}
                }
               IconWithText
                {
                    id: photoArea
                     height: showColumn.basicHeight
                    text: artikelDisplay.fotos
                    iconSource:  "qrc:/Images/foto.svg" //.png"
                    toolTip: qsTr("Fotos von")
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.fotosEdit(newText)}

                }
             }
        }
        Item
        {
            id: headline
            width: parent.width

            height:showColumn.basicHeight + 10
          /*  IconWithText
            {

            }
*/
            Row
            {
               anchors.fill: parent
                DisplayText
                {
                    id: kurzText
                    height: parent.height
                    width: contentWidth //+10
                    //anchors.fill: parent
                    additionToFont: 5
                    font.weight: Font.DemiBold
                   // font.bold: true
            //        property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                    text: artikelDisplay.kurztext //+trenner+artikelDisplay.ueberschrift
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.kurztextEdit(newText)}

                }
                DisplayText
                {
                    id: trenner
                    height: parent.height
                    width: visible?contentWidth:0

                    text: " - "
                    additionToFont: 5
                    font.weight: Font.DemiBold
                    visible: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))

                }

                DisplayText
                {
                  id: ueberschrift
                  height: parent.height
                  width: contentWidth //+10
                  additionToFont: 5
                  font.weight: Font.DemiBold
                 // font.bold: true
                //  property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                  text: /*artikelDisplay.kurztext+trenner+*/artikelDisplay.ueberschrift
                  readOnly: artikelDisplay.readOnlyMode
                  onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.ueberschriftEdit(newText)}
                }
            }

        }
         Item
        {
            id: detail
            width: parent.width
            height: zusammenfassung.height
           Row
           {
            anchors.fill: parent
            BackgroundElement
            {
                id: zusammenfassung_bg
                height: parent.height-6
                width: parent.width/2-6
                DisplayText
                {
                    id: zusammenfassung
                    height: zusammenfassung.contentHeight + 20


                    width: parent.width-6
                    anchors.centerIn: parent
                    text: artikelDisplay.zusammenfassung
                    wrapMode: Text.Wrap
                    verticalAlignment: Text.AlignTop
                    clip: true
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.zusammenfassungEdit(newText)}

                }
            }
            Item
            {
                height: parent.height
                width: 6
            }

            BackgroundElement
            {
                id: schlagworte_bg
                height: parent.height-6
                width: parent.width/2-6

                DisplayText
                {
                    id: schlagworte
                    height: parent.height-6
                    width: parent.width-6
                    anchors.centerIn: parent
                     text: artikelDisplay.stichworte
                    wrapMode: Text.Wrap
                    verticalAlignment: Text.AlignTop
                    clip: true
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{console.log("Artikel  edit to "+newText); artikelDisplay.stichworteEdit(newText)}
                  }
              }
           }

        }


    }
    Button
    {
        text: "Edit"
        anchors.right: parent.right
        visible:  artikelDisplay.readOnlyMode
        onClicked:  editButtonPressed();
    }

}
