import QtQuick 2.0

MouseArea{
    property var target     //设置该MouseArea的控制目标
    //记录鼠标按压时的坐标
    property real pointMouseX:0
    property real pointMouseY:0
    //判断目标是否需要移动
    property bool isMoved: false

    onPressed: {
        pointMouseX=mouseX
        pointMouseY=mouseY
    }

    //当鼠标在指定区域则进行相应的鼠标样式的改变
    onContainsMouseChanged: {
        if(containsMouse){
            cursorShape=Qt.SizeAllCursor
        }else{
            cursorShape=Qt.ArrowCursor
        }
    }

    onPositionChanged: {
        if(!isMoved && pressed && target){
            target.x+=mouseX-pointMouseX
            target.y+=mouseY-pointMouseY
        }
    }
}
