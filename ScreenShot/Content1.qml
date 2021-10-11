import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

Item {
    id: content

    //暂时展示
    signal tempDisplay()

    property bool counter: false

    onTempDisplay: {
        console.log("信号处理")
        //        img.source="file:///tmp/1.jpg"
        img.source = "image://screen?id="+counter
        console.log(img.source)
    }

    function selectImage(){
        img.source = arguments[0]
        console.log("来源是：" + img.source)
    }

    Image {
        id: img
        width: parent.width - rec2.width
        height: parent.height
        anchors.left: parent.left
        anchors.right: rec2.left
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        //指定是否应该缓存图像。默认值为true。当处理大图像时，将cache设置为false是很有用的，以确保它们不会以牺牲小的“ui元素”图像为代价进行缓存。
        cache: false
        //        source: "file:///tmp/1.jpg"
        source: "image://screen"
        fillMode: Image.PreserveAspectFit
    }

    Connections {
        target: capture
        function onCallImgChanged() {
            counter=!counter
            //img.source = ""
            img.source = "image://screen?id="+counter
        }
    }

    Rectangle {
        id: rec2
        width: 250
        height: parent.height
        anchors.right: parent.right
        ColumnLayout {
            id: column1
            x: 0
            y: 0
            width: 250
            height: 289
            implicitHeight: 150
            RowLayout {
                id: row
                Layout.margins: 5
                Text {
                    text: qsTr("截取方式")
                    font.pixelSize: 16
                }
            }
            RowLayout {
                id: row1
                width: 187
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Label {
                    id: lab_1
                    text: qsTr("区域：")
                }
                ComboBox {
                    id: cbb
                    model: ListModel {
                        id: model
                        ListElement {
                            text: "全屏截取"
                        }
                        ListElement {
                            text: "矩形截取"
                        }
                        ListElement{
                            text: "不规则截取"
                        }
                        ListElement {
                            text: "活动窗口截取"
                        }
                        ListElement{
                            text:"连续截取"
                        }
                        ListElement{
                            text:"钉在桌面"
                        }
                        ListElement{
                            text:"长截图"
                        }
                    }
                }
            }
            RowLayout {
                id: row2
                Layout.fillHeight: false
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                Label {
                    id: lab_2
                    text: qsTr("延迟： ")
                }
                SpinBox {
                    id: spinBox
                    minimumValue: 0
                    suffix: "秒"
                    decimals: 0
                    stepSize: 1
                }
                CheckBox {
                    id: checkBox
                    text: "点击时"
                    onCheckedChanged: {
                        if (checkBox.checked) {
                            spinBox.enabled = false
                        } else {
                            spinBox.enabled = true
                        }
                    }
                }
            }
            RowLayout {
                id: row3
                Layout.margins: 5
                Text {
                    text: qsTr("选项")
                    font.pixelSize: 16
                }
            }
            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                CheckBox {
                    id:check_2
                    text: "隐藏当前窗口"
                }
                CheckBox {
                    text: "手动保存或复制后退出"
                }
            }
        }
        Button {
            id:shotBtn
            x: 75
            y: 369
            width: 100
            height: 50
//            anchors.verticalCenter: rec2
            anchors.bottom: parent.bottom
            checked: false
            rotation: 0
            anchors.bottomMargin: 61
            text:qsTr("截取屏幕")
            iconSource: "./icons/logo.png"
            Shortcut{
                sequence: "Ctrl+Print"
                onActivated: shotBtn.clicked()
            }
//            style:ButtonStyle{
//                background: Rectangle {
//                    anchors.fill: parent
//                    border.width: control.activeFocus ? 2 : 1
//                        Image {
//                            id: icons
//                            source: "./icons/logo.png"
//                        }
//                        Text{
//                            anchors.left: icons
//                            anchors.centerIn:parent
//                            font.pixelSize:20
//                            text:qsTr("截取屏幕")
//                        }
//                    radius: 4
//                    gradient: Gradient {
//                        GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
//                        GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
//                    }
//                }
//            }

            onClicked: {
                countDown.start()
            }
        }
    }

    Timer{
        id:timer
        //triggered即使在触发一次之后回调也会保持与信号的连接。
        //这意味着如果再次使用该延迟功能，定时器将再次触发所有连接的回调。所以你应该在触发后断开回调。
        function setTimeout(cb, delayTime) {
            timer.interval = delayTime;
            timer.repeat = false;
            timer.triggered.connect(cb);
            timer.triggered.connect(function release () {
                timer.triggered.disconnect(cb); // This is important
                timer.triggered.disconnect(release); // This is important as well
            });
            timer.start();
        }

    }

    Timer {
        id: countDown
        interval: 1000
        repeat: true
        triggeredOnStart: true

        onTriggered: {
            console.log(spinBox.value)
            spinBox.value -= 1
            if(spinBox.value < 1 && cbb.currentText === "全屏截取"){
                countDown.stop()
                if(check_2.checked == true){
                    appRoot.hide()
                    timer.setTimeout(function(){ capture.startFullScreen() },500)
                    timer.setTimeout(function(){ appRoot.show() },500)
                }else{
                    capture.startFullScreen()
                }

            } else if (spinBox.value < 1 && cbb.currentText === "矩形截取") {
                countDown.stop()
                if(check_2.checked == true){
                    appRoot.hide()
                    timer.setTimeout(function(){ capture.startRecCapture() },500)
                }else{
                    capture.startRecCapture()
                }
            }else if (spinBox.value < 1 && cbb.currentText === "不规则截取") {
                countDown.stop()
                if(check_2.checked == true){
                    appRoot.hide()
                    timer.setTimeout(function(){ capture.startFreeCapture() },500)
                }else{
                    capture.startFreeCapture()
                }
            }else if (spinBox.value < 1 && cbb.currentText === "连续截取") {
                countDown.stop()
                if(check_2.checked == true){
                    appRoot.hide()
                    timer.setTimeout(function(){ capture.startContinueCapture() },500)
                }else{
                    capture.startContinueCapture()
                }
            } else if(spinBox.value < 1 && cbb.currentText === "钉在桌面"){
                countDown.stop()
                if(check_2.checked == true){
                    appRoot.hide()
                    timer.setTimeout(function(){ capture.startNailCapture() },500)
                }else{
                    capture.startNailCapture()
                }
            } else if(spinBox.value < 1 && cbb.currentText === "活动窗口截取"){
                countDown.stop()
                if(check_2.checked == true){
                    appRoot.hide()
                    timer.setTimeout(function(){ capture.startActiveCapture() },500)
                }else{
                    capture.startActiveCapture()
                }
            }else if(spinBox.value < 1 && cbb.currentText === "长截图"){
                countDown.stop()
                if(check_2.checked == true){
                    appRoot.hide()
                    timer.setTimeout(function(){capture.captureLongPicture()} ,1000)
                }
            }
        }
    }

    Connections {
        target: capture
        function onFinishCapture(){
            appRoot.showNormal()
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

