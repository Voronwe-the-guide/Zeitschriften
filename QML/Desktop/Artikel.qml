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
    property string language:""
    signal languageEdit(var newText)


    property string notizen:""
    signal notizenEdit(var newText)

    property bool zeitschriftValid: true;
    property bool jahrValid: true;
    property bool ausgabeValid: true;
    property bool seiteValid: true;


   // property bool hasGPS: false
    property string coordinates:""

    property bool readOnlyMode: true
    property bool isNewOne: false

    signal editButtonPressed();
    signal deleteButtonPressed();
    signal nextPressed()
    signal previousPressed()


    function startFocus()
    {
        magazinArea.focus = true; //.setFocus(true);
    }


    Column
    {
        id: showColumn
        spacing: 4
        width: parent.width
        height: allgemeineInfo.height + headline.height + detail.height + textInfo.height
        property int basicHeight: 25
        Item
        {
            id: allgemeineInfo
            width: parent.width
            height: showColumn.basicHeight
            z:10

            Row
            {
                spacing: 4
                anchors.fill: parent
                IconWithText
                {
                    id: magazinArea
                    text: artikelDisplay.zeitschrift
                    iconSource: "qrc:/Images/magazin.svg" //"png"
                    toolTip: qsTr("Name des Magazins")
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{artikelDisplay.zeitschriftEdit(newText)}
                    onNextPressed: {yearArea.focus = true} //setFocus(true)}
                    onPreviousPressed: { schlagworte.focus = true}//setFocus(true)} //artikelDisplay.previousPressed()}
                    hasValidData: artikelDisplay.zeitschriftValid
                    onReturnPressed:
                    {
                          if ( zeitschriftListDisplay.elementCount > 0)
                          {
            //
                               magazinArea.text = cZeitschriftenList.getElementFromDisplay(0);
                           //   console.log("Text: "+magazinArea.text)
                               artikelDisplay.zeitschriftEdit(magazinArea.text)
                          }
                      }
                      onArrowDownPressed:
                      {
                         // if (rubrikList.count>0)
                          if (zeitschriftListDisplay.elementCount > 0)
                          {
                             // rubrikList.focus = true;
                             zeitschriftListDisplay.setFocus(true);
                               magazinArea.focus = false;
                          }
                      }

                      onFocusChanged:
                      {
                         // console.log("Focus = "+focus);
                      }
                      PullDownFile
                      {
                          id: zeitschriftListDisplay
                          width: 150
                          height: 150
                          border.color: "black"
                          anchors.top: parent.bottom
                          listModel: cZeitschriftNameList
                       //   z: 10
                          visible: (!artikelDisplay.readOnlyMode) && (magazinArea.hasFocus || zeitschriftListDisplay.hasFocus)
                       onJumpedOut: {magazinArea.focus = true; /*rubrikDisplay.setFocus(false); */}
                       onTextSelected:
                       {
                          // rubrikArea.focus = false;
                          //  console.log("Text selected: "+text);
                           magazinArea.text = text
                           artikelDisplay.zeitschriftEdit(magazinArea.text);
                           magazinArea.focus = true;

                         //  rubrikDisplay.setFocus(false);

                       }
                      }

                }
                IconWithText
                {
                    id: yearArea
                    text: (artikelDisplay.jahrgang==0)?"":artikelDisplay.jahrgang
                    iconSource: "qrc:/Images/year.svg"//.png"
                    toolTip: qsTr("Erscheinungsjahr")
                    readOnly: artikelDisplay.readOnlyMode
                    onTextWasEdited:{ artikelDisplay.jahrgangEdit(newText)}
                    onNextPressed: {editionArea.focus = true}
                    onPreviousPressed: {magazinArea.focus = true}
                    hasValidData:  artikelDisplay.jahrValid
                 }

                IconWithText
                {
                   id: editionArea
                   text: (artikelDisplay.ausgabe==0)?"":artikelDisplay.ausgabe
                   iconSource: "qrc:/Images/edition.svg"  //.png"
                   toolTip: qsTr("Ausgabe im Jahr")
                   readOnly: artikelDisplay.readOnlyMode
                   onTextWasEdited:{ artikelDisplay.ausgabeEdit(newText)}
                   onNextPressed: {pageArea.focus = true}
                   onPreviousPressed: {yearArea.focus = true}
                   hasValidData: artikelDisplay.ausgabeValid
                }
                IconWithText
                {
                   id:pageArea
                   text: (artikelDisplay.seite==0)?"":artikelDisplay.seite
                   iconSource: "qrc:/Images/page.svg"  //.png"
                   toolTip: qsTr("Seite des Artikels")
                   readOnly: artikelDisplay.readOnlyMode
                   onTextWasEdited:{ artikelDisplay.seiteEdit(newText)}
                   onNextPressed: {rubrikArea.focus = true}
                   onPreviousPressed: {editionArea.focus = true}
                   hasValidData:  artikelDisplay.seiteValid
                }
                IconWithText
                {
                   id: rubrikArea
                   text: artikelDisplay.rubrik
                   iconSource: "qrc:/Images/rubrik.svg" //.png"
                   toolTip: qsTr("Rubrik - unterschiedlich für Magazine")
                   readOnly: artikelDisplay.readOnlyMode
                   onTextWasEdited:{ artikelDisplay.rubrikEdit(newText)}
                   onNextPressed: {languageArea.focus = true}
                   onPreviousPressed: {pageArea.focus = true}

                 onReturnPressed:
                   {
                       if (rubrikDisplay.elementCount > 0)
                       {
         //
                            rubrikArea.text = cRubrikList.getElementFromDisplay(0);
                         //  console.log("Text: "+rubrikArea.text)
                            artikelDisplay.rubrikEdit(rubrikArea.text)
                       }
                   }
                   onArrowDownPressed:
                   {
                      // if (rubrikList.count>0)
                       if (rubrikDisplay.elementCount > 0)
                       {
                          // rubrikList.focus = true;
                           rubrikDisplay.setFocus(true);
                            rubrikArea.focus = false;
                       }
                   }

                   onFocusChanged:
                   {
                     //  console.log("Focus = "+focus);
                   }
                   PullDownFile
                   {
                       id: rubrikDisplay
                       width: 150
                       height: 150
                       border.color: "black"
                       anchors.top: parent.bottom
                       listModel: cRubrikList
                    //   z: 10
                       visible: (!artikelDisplay.readOnlyMode) && (rubrikArea.hasFocus || rubrikDisplay.hasFocus)
                    onJumpedOut: {rubrikArea.focus = true; /*rubrikDisplay.setFocus(false); */}
                    onTextSelected:
                    {
                       // rubrikArea.focus = false;
                      //   console.log("Text selected: "+text);
                        rubrikArea.text = text
                        artikelDisplay.rubrikEdit(rubrikArea.text);
                        rubrikArea.focus = true;

                      //  rubrikDisplay.setFocus(false);

                    }
                   }

                /*   Rectangle
                   {
                       id: rubrikDisplay
                       width: 150
                       height: 150
                       border.color: "black"
                       anchors.top: parent.bottom
                    //   z: 10
                       visible: (!artikelDisplay.readOnlyMode) && (rubrikArea.hasFocus || rubrikList.focus)

                       Component
                       {
                           id: rubrikCompent
                           Item
                           {
                               width: rubrikDisplay.width
                               height: rubrikArea.height
                               Text
                               {
                                   id: rubrikText
                                   anchors.fill: parent
                                   text: model.element
                                   font.pixelSize:18
                               }
                               MouseArea
                               {
                                   anchors.fill: parent
                                   onClicked:
                                   {
                                       rubrikArea.text = rubrikText.text;
                                       rubrikList.currentIndex = model.index;
                                       rubrikArea.focus = true;
                                       artikelDisplay.rubrikEdit(rubrikArea.text);
                                   }

                               }
                           }
                       }

                       ListView
                       {
                           id: rubrikList
                           anchors.fill: parent
                           model: cRubrikList
                           delegate: rubrikCompent
                           focus: false
                           clip: true
                           highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                           Keys.onEscapePressed: rubrikArea.focus = true;
                           Keys.onUpPressed:
                           {
                               if (rubrikList.currentIndex == 0)
                               {
                                   rubrikArea.focus = true;
                               }
                               else
                               {
                                   rubrikList.currentIndex --;
                               }
                           }
                           Keys.onReturnPressed:
                           {
                              // console.log("Enter pressed");
                               rubrikArea.text = cRubrikList.getElementFromDisplay(rubrikList.currentIndex);
                                rubrikArea.focus = true;
                                artikelDisplay.rubrikEdit(rubrikArea.text);
                           }


                       }
                   }
                   */
                }
                IconWithText
                {
                   id: gpsArea
                   text: artikelDisplay.coordinates
                   iconSource: "qrc:/Images/flag.svg" //.png"
                   toolTip: qsTr("Koordinaten: Werden in Karte gesetzt")
                   readOnly: true //artikelDisplay.readOnlyMode
                 //  onTextWasEdited:{ artikelDisplay.rubrikEdit(newText)}
                 //  onNextPressed: {countryArea.focus = true}
                 //  onPreviousPressed: {pageArea.focus = true}
                }
            }
        }
   /*     Item
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
*/
        Item
        {
            id: textInfo
            width: parent.width
            height: authorArea.height // + photoArea.height
      //      z: 5
            Row
            {
               anchors.fill: parent
               spacing: 4

               IconWithText
               {
                   id: languageArea
                   text: artikelDisplay.language
                   iconSource:  "qrc:/Images/language.svg" //png"
                   toolTip: qsTr("Artikelsprache")
                   readOnly: artikelDisplay.readOnlyMode
                   onTextWasEdited:{ artikelDisplay.languageEdit(newText)}
                   onNextPressed: {countryArea.focus = true}
                   onPreviousPressed: {rubrikArea.focus = true}
               }
               IconWithText
               {
                   id: countryArea
                   text: artikelDisplay.land
                   iconSource:  "qrc:/Images/land.svg" //png"
                   toolTip: qsTr("Land - Verschiedene Eingaben möglich")
                   readOnly: artikelDisplay.readOnlyMode
                   onTextWasEdited:{ artikelDisplay.landEdit(newText)}
                   onNextPressed: {authorArea.focus = true}
                   onPreviousPressed: {languageArea.focus = true}
               }


            IconWithText
                {
                    id: authorArea
                     height: showColumn.basicHeight
                    text: artikelDisplay.author
                    iconSource:  "qrc:/Images/writer.svg" //.png"
                    toolTip: qsTr("Text von: Nachname, Vorname - Verschiedene Autoren durch ; separieren")

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
                    toolTip: qsTr("Fotos von: Nachname, Vorname - Verschiedene Fotografen durch ; separieren")
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
        //    z:4

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
                    toolTip: qsTr("Einführungstext der Überschrift")

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
                  toolTip: qsTr("Hauptüberschrift")

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
                DisplayText_MultiLine
                {
                    id: zusammenfassung
                    height: zusammenfassung.contentHeight + 20
                    toolTip: qsTr("Zusammenfassung des Textes")


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

                DisplayText_MultiLine
                {
                    id: schlagworte
                    height: schlagworte.contentHeight + 20 //parent.height-6
                    width: parent.width-6
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 2
                    toolTip: qsTr("Schlagworte zur Suche")


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

    BackgroundElement
    {
        id: notesArea
        height: 100
        width: 100
        anchors.right: editButton.left
        anchors.rightMargin: 20
        color: "lightyellow"
        DisplayText_MultiLine
        {
            id: notes
            height: parent.height-6
             width: parent.width-6
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 2
            toolTip: qsTr("Notizen zum Artikel")

          //  anchors.centerIn: parent
             text: artikelDisplay.notizen
            wrapMode: Text.Wrap
            verticalAlignment: Text.AlignTop

            clip: true
            readOnly: artikelDisplay.readOnlyMode
            onTextWasEdited:{ artikelDisplay.notizenEdit(newText)}
      //      onPreviousPressed: {zusammenfassung.focus = true}
      //      onNextPressed: {magazinArea.focus = true}//artikelDisplay.nextPressed()}

        }
    }

}
