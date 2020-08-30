import QtQuick 2.0

TextEdit
{
    id: textdisplay
    signal textWasEdited(var newText)
    property string oldText;
    property int additionToFont: 0
    property string textToDisplay:""
    font.pixelSize: 15 + additionToFont
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignLeft
    textFormat: Text.StyledText
    readOnly: true
 //   text: textToDisplay

    onTextChanged:
    {
        if (focus)
        {
            textWasEdited(text);
            console.log("Send Text edit");
        }
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


