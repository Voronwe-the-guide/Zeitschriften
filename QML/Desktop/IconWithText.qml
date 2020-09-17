import QtQuick 2.15
import QtQuick.Controls 2.12
Item
{
    id: textArea
    height: parent.height
    width: displayRow.width
 //   focus: textDisplay.focus
    property string text:""
    property string iconSource:""
    property string toolTip:""
    property bool readOnly: true
    property int additionToFont: 0
    property int  font_weight: Font.Normal
    property bool hasValidData: true
//   activeFocusOnTab: true;
    signal textWasEdited(var newText)
    signal nextPressed()
    signal previousPressed()
    property bool hasFocus: textDisplay.focus

    function setFocus(toFocus)
    {
       // textDisplay.setFocus(toFocus);
    }

    Row
    {
      id: displayRow
       height: parent.height
       width: imageDisplay.width + textDisplay.width + seperator.width


       Image
       {
            id: imageDisplay
            height: parent.height*2/3
            width:  source==""?0:height
            anchors.verticalCenter: parent.verticalCenter
            source: textArea.iconSource
            MouseArea
            {
               id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {toolTip.showTip = true}
                onExited: {toolTip.showTip = false}

            }
       }
        Item
        {
            id: seperator
            height: parent.height
            width: 5
        }

        DisplayText
        {
            id: textDisplay
            height: parent.height
            width: (textDisplay.contentWidth+10)<50?50:textDisplay.contentWidth+10
            text: textArea.text
            readOnly: textArea.readOnly
            focus: textArea.focus
            onTextWasEdited:{ textArea.textWasEdited(newText)}
            onNextPressed: {textArea.nextPressed();}
            onPreviousPressed: {textArea.previousPressed();}
            additionToFont: textArea.additionToFont
            font.weight: textArea.font_weight
            hasValidData: textArea.hasValidData
        }
    }

    ToolTip
    {
      id: toolTip
        text: textArea.toolTip
       delay:200
       property bool showTip: false
       visible: text==""?false:showTip
    }

}
