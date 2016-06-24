import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground
{
    Label
    {
        id: label
        anchors.centerIn: parent
        text: stepcounter.steps
        color: Theme.secondaryHighlightColor
        font.bold: true
        font.pixelSize: Theme.fontSizeExtraLarge
    }

    onStatusChanged:
    {
        coverStatus = status
    }
}


