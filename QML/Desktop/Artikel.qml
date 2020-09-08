import QtQuick 2.0
import QtQuick.Controls 2.12
Item
{
    id: artikelDisplay

    width: 600
    height: showColumn.height+20

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
    property bool isNewOne: false

    signal editButtonPressed();
    signal deleteButtonPressed();
    signal nextPressed()
    signal previousPressed()


    function startFocus()
    {
        magazinArea.focus = true;
    }


    Column
    {
        id: showColumn
        spacing: 4
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
                spacing: 4
                anchors.fill: parent
                IconWithText
                {
                    id: magazinArea
                    text: artikelDisplay.zeitschrift
                    iconSource: "qrc:/Images/magazin.svg" //"png"
                    toolTip: qsTr("Magazin")
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{artikelDisplay.zeitschriftEdit(newText)}
                    onNextPressed: {yearArea.focus = true}
                    onPreviousPressed: { schlagworte.focus = true} //artikelDisplay.previousPressed()}

                }
                IconWithText
                {
                    id: yearArea
                    text: (artikelDisplay.jahrgang==0)?"":artikelDisplay.jahrgang
                    iconSource: "qrc:/Images/year.svg"//.png"
                    toolTip: qsTr("Jahr")
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{ artikelDisplay.jahrgangEdit(newText)}
                    onNextPressed: {editionArea.focus = true}
                    onPreviousPressed: {magazinArea.focus = true}
                 }

                IconWithText
                {
                   id: editionArea
                   text: (artikelDisplay.ausgabe==0)?"":artikelDisplay.ausgabe
                   iconSource: "qrc:/Images/edition.svg"  //.png"
                   toolTip: qsTr("Ausgabe")
                   readOnly: artikelDisplay.readOnlyMode
                   onTextWasEdited:{ artikelDisplay.ausgabeEdit(newText)}
                   onNextPressed: {pageArea.focus = true}
                   onPreviousPressed: {yearArea.focus = true}
                }
                IconWithText
                {
                   id:pageArea
                   text: (artikelDisplay.seite==0)?"":artikelDisplay.seite
                   iconSource: "qrc:/Images/page.svg"  //.png"
                   toolTip: qsTr("Seite")
                   readOnly: artikelDisplay.readOnlyMode
                   onTextWasEdited:{ artikelDisplay.seiteEdit(newText)}
                   onNextPressed: {rubrikArea.focus = true}
                   onPreviousPressed: {editionArea.focus = true}
                }
                IconWithText
                {
                   id: rubrikArea
                   text: artikelDisplay.rubrik
                   iconSource: "qrc:/Images/rubrik.svg" //.png"
                   toolTip: qsTr("Rubrik")
                   readOnly: artikelDisplay.readOnlyMode
                   onTextWasEdited:{ artikelDisplay.rubrikEdit(newText)}
                   onNextPressed: {countryArea.focus = true}
                   onPreviousPressed: {pageArea.focus = true}
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
                id: countryArea
                text: artikelDisplay.land
                iconSource:  "qrc:/Images/land.svg" //png"
                toolTip: qsTr("Land")
                readOnly: artikelDisplay.readOnlyMode
                onTextWasEdited:{ artikelDisplay.landEdit(newText)}
                onNextPressed: {authorArea.focus = true}
                onPreviousPressed: {rubrikArea.focus = true}
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
               spacing: 4
               IconWithText
                {
                    id: authorArea
                     height: showColumn.basicHeight
                    text: artikelDisplay.author
                    iconSource:  "qrc:/Images/writer.svg" //.png"
                    toolTip: qsTr("Text von")

                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{ artikelDisplay.authorEdit(newText)}
                    onNextPressed: {photoArea.focus = true}
                    onPreviousPressed: {countryArea.focus = true}
                }
               IconWithText
                {
                    id: photoArea
                     height: showColumn.basicHeight
                    text: artikelDisplay.fotos
                    iconSource:  "qrc:/Images/foto.svg" //.png"
                    toolTip: qsTr("Fotos von")
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{ artikelDisplay.fotosEdit(newText)}
                    onNextPressed: {kurzText.focus = true}
                    onPreviousPressed: {authorArea.focus = true}

                }
             }
        }
        Item
        {
            id: headline
            width: parent.width

            height:showColumn.basicHeight + 20
          /*  IconWithText
            {

            }
*/
            Item //Row
            {
              // anchors.fill: parent
               height: headline.height-10
               width: parent.width
               anchors.verticalCenter: parent.verticalCenter
             //  spacing: 4

                IconWithText//DisplayText
                {
                    id: kurzText
                    height: parent.height
                  //  width: contentWidth //+10
                    //anchors.fill: parent
                    additionToFont: 5
                    font_weight: Font.DemiBold
                   // font.bold: true
            //        property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                    text: artikelDisplay.kurztext //+trenner+artikelDisplay.ueberschrift
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{ artikelDisplay.kurztextEdit(newText)}
                    onNextPressed: {ueberschrift.focus = true}
                    onPreviousPressed: {photoArea.focus = true}

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
                    anchors.left: kurzText.right

                }

                IconWithText //DisplayText
                {
                  id: ueberschrift
                  height: parent.height
               //   width: contentWidth //+10
                  additionToFont: 5
                  font_weight: Font.DemiBold
                 // font.bold: true
                //  property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                  text: /*artikelDisplay.kurztext+trenner+*/artikelDisplay.ueberschrift
                  readOnly: artikelDisplay.readOnlyMode
                  onTextWasEdited:{ artikelDisplay.ueberschriftEdit(newText)}
                  onNextPressed: {zusammenfassung.focus = true}
                  onPreviousPressed: {kurzText.focus = true}
                  anchors.left: trenner.right

                }
            }

        }
         Item
        {
            id: detail
            width: parent.width
            height: zusammenfassung.height > schlagworte.height?zusammenfassung.height:schlagworte.height
           Row
           {
            anchors.fill: parent
            BackgroundElement
            {
                id: zusammenfassung_bg
                height: parent.height
                        //-6
                width: parent.width/2-6
                DisplayText
                {
                    id: zusammenfassung
                    height: zusammenfassung.contentHeight + 20


                    width: parent.width-6
                  //  anchors.centerIn: parent
                    text: artikelDisplay.zusammenfassung
                    wrapMode: Text.Wrap
                    verticalAlignment: Text.AlignTop
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 2
                     clip: true
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{ artikelDisplay.zusammenfassungEdit(newText)}
                    onNextPressed: {schlagworte.focus = true}
                    onPreviousPressed: {ueberschrift.focus = true}

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
                height: parent.height //-6
                width: parent.width/2-6

                DisplayText
                {
                    id: schlagworte
                    height: schlagworte.contentHeight + 20 //parent.height-6
                    width: parent.width-6
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 2

                  //  anchors.centerIn: parent
                     text: artikelDisplay.stichworte
                    wrapMode: Text.Wrap
                    verticalAlignment: Text.AlignTop

                    clip: true
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{ artikelDisplay.stichworteEdit(newText)}
                    onPreviousPressed: {zusammenfassung.focus = true}
                    onNextPressed: {magazinArea.focus = true}//artikelDisplay.nextPressed()}
                  }
              }
           }

        }


    }
    Button
    {
        id: editButton
        text: "Edit"
        anchors.right: parent.right
        visible:  artikelDisplay.readOnlyMode
        onClicked:  editButtonPressed();
    }
    Button
    {
        id: deleteButton
        text: "Delete"
        anchors.right: parent.right
        anchors.top: editButton.bottom
        anchors.topMargin: 10
        visible:  artikelDisplay.readOnlyMode
        onClicked:  deleteButtonPressed();

    }

}
