import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

TextEdit //Field //Input//Edit
{
    id: textdisplay
    signal nextPressed()
    signal previousPressed()
    signal textWasEdited(var newText)
    property string oldText;
    property int additionToFont: 0
    property string textToDisplay:""
    font.pixelSize: 15 + additionToFont
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignLeft
    inputMethodHints: Qt.ImhNoPredictiveText
   textFormat: TextEdit.AutoText //Text.StyledText
   wrapMode: Text.NoWrap
    readOnly: true
    selectByMouse: true
 //   backgroundVisible: false
    textMargin: 0


  /*      style: TextAreaStyle {
            textColor: "#333"
            selectionColor: "steelblue"
            selectedTextColor: "#eee"
            backgroundColor: "#eee"

        }
*/
 //   setTabStopDistance: 0
 //   text: textToDisplay

   KeyNavigation.priority: KeyNavigation.BeforeItem
 //  KeyNavigation.tab: {console.log("Tab pressed"); textdisplay.focus= false;tabPressed()}
  //  KeyNavigation.backtab: tabPressed()
//    KeyNavigation.tab: { tabPressed()}

   Keys.onTabPressed:
   {
       console.log("Tab2 pressed");
      // textDisplay.focus= false;
        textdisplay.nextPressed();
   }
   Keys.onBacktabPressed:
   {
       console.log("Tab2 pressed");
      // textDisplay.focus= false;
        textdisplay.previousPressed();

   }

   Keys.onReturnPressed:
   {
       console.log("Tab2 pressed");
       textDisplay.focus= false;
        textdisplay.nextPressed();

   }

  /*  Keys.onPressed:
    {
      if (event.key === Qt.LeftArrow) {textDisplay.focus= false;  tabPressed(); console.log("Tab pressed");}

    }
*/
    onTextChanged:
    {
        if (focus)
        {
            textWasEdited(text);
            console.log("Send Text edit");
        }
    }

    Rectangle
    {
        anchors.fill: parent
        color: "transparent"
        border.color: "red"
        visible: parent.focus
    }

 /*   onFocusChanged:
    {
        if (focus)
        {
            oldText = text;
            console.log("Focus true for "+text);
        }
        else
        {
            console.log("Focus false for "+text);
            if (text != oldText)
            {
                textWasEdited(text);
                console.log("Send Text edit");
            }

        }
    }
*/
}



