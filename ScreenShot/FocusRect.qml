import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    property alias containsMouse: mouse.containsMouse

    //设置默认鼠标类型
    property int mouseStyle: Qt.ArrowCursor
    //列举鼠标在各个不同方位的类型
    readonly property int mouseLeftTop: Qt.SizeFDiagCursor
    readonly property int mouseTop: Qt.SizeVerCursor
    readonly property int mouseRightTop: Qt.SizeBDiagCursor
    readonly property int mouseLeft: Qt.SizeHorCursor
    readonly property int mouseRight: Qt.SizeHorCursor
    readonly property int mouseLeftBottom: Qt.SizeBDiagCursor
    readonly property int mouseBottom: Qt.SizeVerCursor
    readonly property int mouseRightBottom: Qt.SizeFDiagCursor

    //设置焦点矩形的长、宽
    property real rectWidth: 20
    property real rectHeight: 20

    //设置改变位置的信号
    signal posChange(int x,int y)

    //设置焦点矩形的隐式长、宽
    implicitWidth: 20
    implicitHeight: 20

    Rectangle{
        width:rectWidth
        height: rectHeight
        color: "grey"
        MouseArea{
            id:mouse
            anchors.fill: parent
            hoverEnabled: true
            property real pointMouseX: 0
            property real pointMouseY: 0
            onContainsMouseChanged: {
                if(containsMouse){
                    cursorShape=mouseStyle
                }else{
                    cursorShape=Qt.ArrowCursor
                }
            }

            onPressedChanged: {
                if(containsMouse){
                    pointMouseX=mouseX
                    pointMouseY=mouseY
                }
            }
            onPositionChanged: {
                if(pressed){
                    posChange(mouseX-pointMouseX,mouseY-pointMouseY)
                }
            }
        }
    }
}
