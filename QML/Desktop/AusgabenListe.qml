import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import "Helper"

Window
{
    id:ausgabenDisplay
    width: 900
    height: 900

    visible: true
    modality:Qt.ApplicationModal
    property bool readOnlyMode: false

    property int oldIndex: -1;
    onBeforeRendering:
    {
  //     cListenController.getListOfAusgaben()
    }

    function readList()
    {
        ausgabenList.focus = true
        cListenController.getListOfAusgaben()
        ausgabenList.currentIndex = oldIndex
        ausgabenList.positionViewAtIndex(oldIndex,ListView.Center)
        oldIndex = -1
    }

    function callEdit(listIndex,dbIndex)
    {
        oldIndex = ausgabenList.currentIndex;
        cAusgabeEditor.setForUpdate(dbIndex)
        var this_component = Qt.createComponent("AusgabeWriter.qml").createObject(ausgabenDisplay)// artikeleditor.visible = true;
        this_component.saveButtonPressed.connect(readList);
    }


    title: qsTr("Ausgaben Liste"+width+"/"+height)
    flags:  Qt.Window | Qt.WindowSystemMenuHint
            | Qt.WindowTitleHint | Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint
     |Qt.WindowCancelButtonHint
            | Qt.WindowMaximizeButtonHint// | Qt.WindowStaysOnTopHint


    Item {
        id: displayItem
        width: parent.width-20
        height: parent.height -20
        anchors.centerIn: parent

    Component
    {
        id: elementForList
        Rectangle
        {
            id: ausgabe
            width: displayItem.width-ausgabenList.scrollBarWidth
            height: 120
            color: model.index == ausgabenList.currentIndex?"lightblue":"#EBEBEB" //"lightblue"
            radius: 5
            clip: true
            MouseArea
            {
                anchors.fill: parent
                propagateComposedEvents: true

                onClicked:
                {
                   // ausgabe.color= "red"
                    ausgabenList.currentIndex = model.index
                    ausgabenList.positionViewAtIndex(model.index,ListView.Center)

                }
            }


            Row
            {

                anchors.fill: parent
             //   width: parent.width
             //   height: parent.height
                spacing: 10
                Image
                {
                    id: cover
                    height: parent.height
                    width: height/1.3//4142
                    source:  model.cover
                    fillMode: Image.PreserveAspectFit

                    Rectangle
                    {

                        id: coverRamen
                        anchors.fill: parent
                        color: "transparent"
                        border.color: "black"
                    }

                }

                Column
                {
                   id: ausgabeInfo
                    width: 500
                    height: parent.height
                    Row
                    {
                       id: titelRow
                        spacing: 10
                       width: parent.width
                       height: 30
                        IconWithText//DisplayText
                        {

                            id: zeitschrift
                            height: parent.height
                       //     width: 100 //parent.width

                          //  anchors.verticalCenter: parent.verticalCenter
                            anchors.bottom: parent.bottom
                            toolTip: qsTr("Name der Zeitschrift")
                            focus: true
                            hasValidData: cAusgabeEditor.zeitschriftValid
                            additionToFont: 5
                            font_weight: Font.DemiBold
                           //font.bold: true
                    //        property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                            text: model.zeitschrift //+trenner+artikelDisplay.ueberschrift
                            verticalAlignment: Text.AlignBottom
                            horizontalAlignment: Text.AlignLeft


                        }

                        IconWithText//DisplayText
                        {
                            id: untertitel

                           height: parent.height
                          //  width: parent.width
                            toolTip: qsTr("Slogan der Zeitschrift")
                            anchors.bottom: parent.bottom
                      //     anchors.verticalCenter: parent.verticalCenter
                           anchors.left: zeitschrift.right
                           verticalAlignment: Text.AlignBottom
//Tracer{}
                          //  additionToFont: 5
                          //  font_weight: Font.DemiBold
                           // font.bold: true
                    //        property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                            text: model.untertitel //+trenner+artikelDisplay.ueberschrift
                        }

                    }//End titleRow
                    Item {id: seperator; width: parent.width; height: 5}
                    Row
                    {
                        id: ausgabeRow
                        width: parent.width //  anchors.fill: parent
                          spacing: 4
                          height: 25
                          IconWithText
                          {
                              id: yearArea
                              text: ( model.jahr==0)?"":model.jahr
                              iconSource: "qrc:/Images/year.svg"//.png"
                              toolTip: qsTr("Erscheinungsjahr")
                           }

                          IconWithText
                          {
                             id: editionArea
                             text: (model.ausgabe==0)?"":model.ausgabe
                             iconSource: "qrc:/Images/edition.svg"  //.png"
                             toolTip: qsTr("Ausgabe im Jahr")
                           }
                          IconWithText
                          {
                             id:pageArea
                             text: (model.seitenzahl==0)?"":model.seitenzahl
                             iconSource: "qrc:/Images/seitenzahl.svg"  //.png"
                             toolTip: qsTr("Anzahl der Seiten")

                          }
                    }

                    Row
                    {
                      id: detailedInfo
                      width: parent.width //  anchors.fill: parent
                        spacing: 4
                        height: 25
                        IconWithText
                        {
                            id: preisArea
                            text:  model.preis// r==0)?"":cAusgabeEditor.jahr
                            iconSource: "qrc:/Images/preis.svg"//.png"
                            toolTip: qsTr("Preis")
                         }

                        IconWithText
                        {
                           id: waehrungArea
                           text: model.waehrung //.ausgabe==0)?"":cAusgabeEditor.ausgabe
                           iconSource: "qrc:/Images/waehrung.svg"  //.png"
                           toolTip: qsTr("Währung")

                        }
                        IconWithText
                        {
                           id:languageArea
                           text: model.sprache //eitenzahl==0)?"":cAusgabeEditor.seitenzahl
                           iconSource: "qrc:/Images/language.svg"  //.png"
                           toolTip: qsTr("Sprache")

                        }
                    }
                    Item {id: seperator2; width: parent.width; height: 5}

                    Row
                    {
                        id: redaktionInfo
                        width: parent.width //  anchors.fill: parent
                          spacing: 4
                          height: 25
                          IconWithText
                          {
                              id: redaktion
                              text:  model.chefredakteur// r==0)?"":cAusgabeEditor.jahr
                              iconSource: "qrc:/Images/writer.svg"  //.png"
                              toolTip: qsTr("Chefredaktion")
                          }

                    }
                }//End  ausgabeInfo

                Item
                {
                    id: notizen
                    height: parent.height
                    width:parent.width-cover.width-ausgabeInfo.width-editButton.width-40
                    DisplayText_MultiLine
                    {
                        id: notizenText
                        anchors.fill: parent
                        toolTip: qsTr("Notizen")


                      //  anchors.centerIn: parent
                         text: model.notizen
                        wrapMode: Text.Wrap
                        verticalAlignment: Text.AlignTop

                        clip: true
                        readOnly:true
                    }
                }
                Button
                {
                    id: editButton
                    text:"Edit"
                    onClicked:
                    {
                        ausgabenList.currentIndex = model.index
                        callEdit(model.index,model.dbIndex)
                    }
                }

            }


        }
    }

    ListView
    {
        id: ausgabenList
        focus: true
        anchors.fill: parent
        currentIndex: 0
        //columnSpacing: 1
        //rowSpacing: 1
        clip: true
        model: cAusgabenList
        delegate: elementForList
        spacing: 10
        property int scrollBarWidth: 30
        ScrollBar.vertical: ScrollVertical {width: scrollBarWidth}
        highlightFollowsCurrentItem : false
        preferredHighlightBegin: height / 2 - 100 // 100 being item height / 2
        preferredHighlightEnd: height / 2 + 100 // 100 being item height / 2
      //  highlightRangeMode: ListView.StrictlyEnforceRange

        Keys.onUpPressed:
        {
            if (ausgabenList.currentIndex>0)
            {
                ausgabenList.currentIndex--
                ausgabenList.positionViewAtIndex(ausgabenList.currentIndex,ListView.Center)
            }
        } // scrollBar.decrease()
        Keys.onDownPressed:
        {
            if (ausgabenList.currentIndex<ausgabenList.count)
            {
                ausgabenList.currentIndex++
                ausgabenList.positionViewAtIndex(ausgabenList.currentIndex,ListView.Center)
            }
        }
        Keys.onReturnPressed:
        {
            callEdit(ausgabenList.currentIndex,model.getDBIndex(ausgabenList.currentIndex))

        }

        // scrollBar.increase()





    }

    }
}
