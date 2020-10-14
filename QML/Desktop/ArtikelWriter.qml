import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import ZeitschriftLib 1.0
Window
{
    id: editWindow
    property int windowType: WindowNames.WINDOW_EDIT_ARTIKEL
    width:cSettings.getWindowSize(windowType).width // .mainWindowSize.width // .getWindowSize().width
    height:artikel.height+dialogButtons.height+map.height+30 // cSettings.getWindowSize(windowType).height //.mainWindowSize.height //.getWindowSize().height
    onWidthChanged: cSettings.setWindowWidth(windowType,width)
 //   onHeightChanged: cSettings.setWindowHeight(windowType,height)
    visible: true
    property bool isNewOne: false;
    modality:Qt.ApplicationModal

    signal nextButtonPressed();
    signal saveButtonPressed();
    signal cancelButtonPressed();

    onVisibilityChanged:
    {
        if (visible)
        {
            artikel.readOnlyMode = false;
            artikel.startFocus();
        }
        else
        {
            artikel.readOnlyMode = true;
        }
    }

   title: "Edit Artikel"
   flags:  Qt.Window | Qt.WindowSystemMenuHint
           | Qt.WindowTitleHint | Qt.WindowMinimizeButtonHint //| Qt.WindowCloseButtonHint
//      |Qt.WindowCancelButtonHint
           | Qt.WindowMaximizeButtonHint// | Qt.WindowStaysOnTopHint
   Column
   {
    height: parent.height
    width: parent.width
   DisplayMap
    {
        id: map
        width: parent.width
        height:300
        currentLat: cArtikelEditor.currentLat
        currentLong: cArtikelEditor.currentLong
         magazin_text: cArtikelEditor.zeitschrift
        jahr_text: cArtikelEditor.jahr
        ausgabe_text: cArtikelEditor.ausgabe
        seite_text: cArtikelEditor.seite

        onCoordinatePressed:
        {
          //  console.log("got coordinate"+latitude+"/"+longitude);
            cArtikelEditor.setCurrentCoordinate(latitude,longitude);
        }
    }


   MessageDialog
   {
       id: errorDialog
       width: 400
       height: 300
       title: qsTr("Fehler")
       icon: StandardIcon.Critical

       text:"Hello"
       visible: false
       modality: Qt.ApplicationModal
       onAccepted: {
         visible: false
        }
   }

   DialogButtonBox
   {
       id: dialogButtons
       signal nextPressed()
       signal previousPressed()


       function focusFromStart(){saveButton.focus = true}
       function focusFromEnd(){cancelButton.focus = true}

       Button {
           id: saveButton
           text: qsTr("Speichern")
             DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
             onClicked:
             {
                var retVal= cArtikelEditor.saveChangesInDB(isNewOne);
                 if (retVal)
                 {
                    editWindow.close()
                     editWindow.saveButtonPressed()
                 }
                 else //if (retVal == -1)
                 {
                     errorDialog.text = "Daten nicht korrekt!"
                     errorDialog.visible = true;
                   //  Qt.createComponent("MessageDisplay.qml").createObject(editWindow, {text:qsTr("Daten nicht korrekt!")})// artikeleditor.visible = true;

                 }
              /*   else if (retVal == -2)
                 {
                     errorDialog.text = "Ausgabe existiert schon!"
                     errorDialog.visible = true;
                  //   Qt.createComponent("MessageDisplay.qml").createObject(editWindow, {text:qsTr("Ausgabe existiert schon!")})// artikeleditor.visible = true;

                 }
                 */
             }
 //            Keys.onTabPressed:{cancelButton.focus = true;}
 //            Keys.onBacktabPressed:{dialogButtons.previousPressed()}
 //            Keys.onReturnPressed:{ cArtikelEditor.saveChangesInDB(); editWindow.close()}


         }
         Button {
             id: cancelButton
             text: qsTr("Cancel")
             DialogButtonBox.buttonRole: DialogButtonBox.DestructiveRole
             onClicked: {
                 editWindow.close()
                    editWindow.cancelButtonPressed()
             }
  //           Keys.onTabPressed:{dialogButtons.nextPressed()}
  //           Keys.onBacktabPressed: {saveButton.focus = true}
  //           Keys.onReturnPressed:{editWindow.close()}

         }

         Button
         {
             id: nextButton
             visible: editWindow.isNewOne
             text: qsTr("Speichern und Nächster")
             onClicked:
             {
                var retVal = cArtikelEditor.saveAndNext(isNewOne);
                if (retVal)
                {
                    editWindow.close();
                    editWindow.nextButtonPressed();
                }
                else
                {
                    errorDialog.text = "Daten nicht korrekt!"
                    errorDialog.visible = true;
                  //  Qt.createComponent("MessageDisplay.qml").createObject(editWindow, {text:qsTr("Daten nicht korrekt!")})// artikeleditor.visible = true;

                }

             }
         }

  /*     standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel
   //    position: DialogButtonBox.Footer
       onAccepted:{cArtikelEditor.saveChangesInDB(); editWindow.close()}
       onRejected: editWindow.close()
  */ }
      Artikel
      {

        //  id: artikelDisplay
          width: parent.width
         // anchors.top: map.bottom
          id: artikel
          isNewOne: editWindow.isNewOne
          readOnlyMode: false
          zeitschrift:cArtikelEditor.zeitschrift
          jahrgang:cArtikelEditor.jahr
          ausgabe:cArtikelEditor.ausgabe
          seite:cArtikelEditor.seite
          rubrik:cArtikelEditor.rubrik
          kurztext:cArtikelEditor.kurztext
          ueberschrift:cArtikelEditor.ueberschrift
          zusammenfassung:cArtikelEditor.zusammenfassung
          stichworte:cArtikelEditor.schlagworte
          author:cArtikelEditor.autor
          fotos:cArtikelEditor.fotos
          land:cArtikelEditor.land
          notizen: cArtikelEditor.notizen
          coordinates: cArtikelEditor.koordinaten
          language: cArtikelEditor.sprache

          zeitschriftValid: cArtikelEditor.zeitschriftValid;
          jahrValid: cArtikelEditor.jahrValid;
          ausgabeValid: cArtikelEditor.ausgabeValid;
          seiteValid: cArtikelEditor.seiteValid;
          Connections
          {
              target:cArtikelEditor
              function onArtikelDisplayUpdated()
              {
               //  console.log("Display updated");
                  artikel.zeitschrift = cArtikelEditor.getZeitschrift()
                  artikel.jahrgang=cArtikelEditor.getJahr()
                  artikel.ausgabe=cArtikelEditor.getAusgabe()
                  artikel.seite=cArtikelEditor.getSeite()
                  artikel.rubrik=cArtikelEditor.getRubrik()
                  artikel.kurztext=cArtikelEditor.getKurztext()
                  artikel.ueberschrift=cArtikelEditor.getUeberschrift()
                  artikel.zusammenfassung=cArtikelEditor.getZusammenfassung()
                  artikel.stichworte=cArtikelEditor.getSchlagworte()
                  artikel.author=cArtikelEditor.getAutor()
                  artikel.fotos=cArtikelEditor.getFotos()
                  artikel.land=cArtikelEditor.getLand()
                  artikel.notizen = cArtikelEditor.getNotizen()
                  artikel.coordinates = cArtikelEditor.getKoordinaten()
                  artikel.language = cArtikelEditor.getSprache()
              }
          }
          onZeitschriftEdit:{cArtikelEditor.setZeitschrift(newText)}
          onJahrgangEdit:{cArtikelEditor.setJahr(newText)}
          onAusgabeEdit:{cArtikelEditor.setAusgabe(newText)}
          onSeiteEdit:{cArtikelEditor.setSeite(newText)}
          onRubrikEdit:{cArtikelEditor.setRubrik(newText)}
          onKurztextEdit:{cArtikelEditor.setKurztext(newText)}
          onUeberschriftEdit:{cArtikelEditor.setUeberschrift(newText)}
          onZusammenfassungEdit:{cArtikelEditor.setZusammenfassung(newText)}
          onStichworteEdit:{cArtikelEditor.setSchlagworte(newText)}
          onAuthorEdit:{cArtikelEditor.setAutor(newText)}
          onFotosEdit:{cArtikelEditor.setFotos(newText)}
          onLandEdit:{cArtikelEditor.setLand(newText)}
          onNotizenEdit: {cArtikelEditor.setNotizen(newText)}
          onLanguageEdit: {cArtikelEditor.setSprache(newText)}

          onPreviousPressed: {dialogButtons.focusFromEnd()}
          onNextPressed: {dialogButtons.focusFromStart()}
       //   hasGPS: true
      }
}


//   standardButtons: StandardButton.Save | StandardButton.Cancel
}

