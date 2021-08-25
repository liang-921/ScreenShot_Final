import QtQuick 2.0

Item {
    property real imgWidth
    property real imgHeight
    property alias borderWidth: cutborder.width
    property alias borderHeight: cutborder.height

    function cut(){
        content2.rectX=-cutrect.x
        content2.rectY=-cutrect.y
        content2.rectWidth=cutborder.width
        content2.rectHeight=cutborder.height
    }

    Rectangle{
        id:cutrect
        width: imgWidth
        height: imgHeight
        color: "transparent"
        RectMove{
            anchors.fill: parent
            target:parent
        }
        CutBorder{
            id:cutborder
            anchors.fill:parent
            target: parent
        }
    }
}
