import QtQuick 2.0

Text
{
    id: textdisplay
    property int additionToFont: 0
    font.pixelSize: 15 + additionToFont
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignLeft
    textFormat: Text.StyledText

}


