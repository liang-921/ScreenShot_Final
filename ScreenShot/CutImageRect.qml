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

    //clear后恢复最开始剪切矩形的大小，位置
    function cutreUpdate() {
        cutrect.x = 0
        cutrect.y = 0
        cutrect.width = arguments[0]
        cutrect.height = arguments[1]
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
