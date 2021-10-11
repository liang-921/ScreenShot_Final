import QtQuick 2.0

Item {
    id: messageBox
    width: msgBox.width
    height: msgBox.height
    anchors {
        horizontalCenter: parent.horizontalCenter
    }
    //提示框内容
    property alias text: msg.text
    property bool show: false
    property string type: "info"
    visible: show
    //执行定时器
    function openTimer() {
        timerId.start()
        messageBox.y = 80
    }
    Behavior on y {
        NumberAnimation {
            duration: 100
        }
    }
    Timer {
        id: timerId
        interval: 1000
        repeat: false
        onTriggered: {
            messageBox.y = 50
            timerHide.start()
        }
    }
    Timer {
        id: timerHide
        interval: 300
        repeat: false
        onTriggered: {
            show = false
        }
    }
    Rectangle {
        id: msgBox
        clip: true
        width:140
        height: 50
        color:  type=== "info" ? "#fdf6ec" : type=== "success"?"#f0f9eb" : "#fef0f0"
        border.color:type=== "info" ? "#faecd8" : type=== "success" ? "#e1f3d8" : "#fde2e2"
        radius: 5
        Image {
            id: img
            source: type
                    === "info" ? "qrc:./icons/rect.png" : type
                                 === "success" ? "qrc:./icons/true.png" : "qrc:./icons/clear.png"
            width: 24
            height: 24
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 15
            }
        }
        Text {
            id: msg
            color: type=== "info" ? "#e6a23c" : type=== "success" ? "#67c23a" : "#f56c6c"
            font.pixelSize: 16
            anchors {
                verticalCenter: img.verticalCenter
                left: img.right
                leftMargin: 10
            }
        }
    }
}
