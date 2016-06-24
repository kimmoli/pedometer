import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.pedometer 1.0

ApplicationWindow
{
    initialPage: Qt.resolvedUrl("pages/Pedometer.qml")
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: Orientation.All

    StepCounter
    {
        id: stepcounter
    }
}


