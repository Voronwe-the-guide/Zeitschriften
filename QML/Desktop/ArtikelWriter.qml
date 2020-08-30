import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
Window
{
    id: editWindow
    width: 1000
    height: artikel.height+dialogButtons.height
    visible: true
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
           | Qt.WindowMaximizeButtonHint // | Qt.WindowStaysOnTopHint

   DialogButtonBox
   {
       id: dialogButtons
       standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel
   //    position: DialogButtonBox.Footer
       onAccepted:{cArtikelEditor.saveChangesInDB(); editWindow.close()}
       onRejected: editWindow.close()
   }
      Artikel
      {

          width: parent.width
          anchors.top: dialogButtons.bottom
          id: artikel
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
          Connections
          {
              target:cArtikelEditor
              onArtikelDisplayUpdated:
              {
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
              }
          }
          onZeitschriftEdit:{console.log("Zeitschrift edit to"+newText);cArtikelEditor.setZeitschrift(newText)}
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
       //   hasGPS: true
      }


//   standardButtons: StandardButton.Save | StandardButton.Cancel
}

