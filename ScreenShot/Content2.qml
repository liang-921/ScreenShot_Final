import QtQuick 2.15
import QtQuick.Controls 1.4 as QQC
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.3
import qml.Controls 1.0

Item {

    id: content2

    property alias paint1: paint

    property alias img_paint:img
    property bool counter: false
    //设置画笔颜色，画笔粗细
    property string painterColor: "red"

    //设置文字颜色，文字粗细
    property string textpaintColor: "black"

    //设置剪切后的图片位置
    property int rectX: 0
    property int rectY: 0

    //剪切矩形的大小
    property int rectWidth: img.width
    property int rectHeight: img.height

    //记录剪切次数，目的是将第一次的矩形大小与位置传递
    property int rectClick: 0

    //撤销是判断最近一次操作是否是裁剪
    property bool isCut: false

    function selectImage() {
        img.source = arguments[0]
        console.log("来源是：" + img.source)
    }

    //重新设置img的大小、位置
    function reUpdate() {
        paint.destroyRect()
        rectX = 0
        rectY = 0
        rectWidth = img.width
        rectHeight = img.height
        rectClick=0
    }

    //根据undo或clear取重新设置img特定的大小、位置
    function backImg() {
        rectX = arguments[0].x
        rectY = arguments[0].y
        rectWidth = arguments[0].width
        rectHeight = arguments[0].height
    }


    //左边编辑栏
    Column {
        id: leftside

        height: parent.height

        Grid {

            id: grid

            padding: 15
            spacing: 15
            columns: 2

            //裁剪图片
            Button{
                id:shotImg
                width: 40
                height: 40
                iconSource: "qrc:/icons/cut.png"
                onClicked: {
                    cutImgConfirm.visible = true
                    cutImage.visible = true
                    rectClick++
                    //第一次裁剪之前需要将最开始的图片大小位置传递
                    if (rectClick == 1) {
                        paint.sendRectNumber(0, 0, img.width, img.height)
                    }
                    //剪切操作，向painteditem里的m_sequence里push_back(6)
                    paint.pressCutSequence()
                    shotImg.visible = false
                }
            }

            Button{
                id:cutImgConfirm
                width: 40
                height: 40
                visible: false
                Text{
                    anchors.centerIn: parent
                    text: qsTr("OK")
                }
                onClicked: {
                    shotImg.visible = true
                    //获取剪切矩形的位置、大小
                    cutImage.cut()
                    //传递剪切矩形的位置、大小
                    paint.sendRectNumber(rectX, rectY, rectWidth,
                                         rectHeight)
                    cutImgConfirm.visible = false
                    cutImage.visible = false
                }
            }

            //画笔
            Button {
                id: painter

                width: 40
                height: 40
                iconSource: "qrc:/icons/paint.png"
                onClicked: {
                    paint.enabled = true
                    paint.flag = 5
                }
            }

            //文本
            Button {
                id: text

                width: 40
                height: 40
                iconSource: "qrc:/icons/draw-text.png"
                onClicked: {
                    paint.enabled = true
                    console.log("1")
                    paint.flag = 1
                    textedit.focus=true
                }
            }

            //画框
            Button {
                id: drawframe
                iconSource: "qrc:/icons/rectangle.png"

                width: 40
                height: 40
                menu: Menu {
                    MenuItem {
                        action: Action {
                            text: qsTr("Rectangle")
                            iconSource: "qrc:/icons/rectangle.png"
                            onTriggered: {
                                drawframe.iconSource = iconSource
                                paint.enabled = true
                                paint.flag = 3
                            }
                        }
                    }
                    MenuItem {
                        action: Action {
                            text: qsTr("circle")
                            iconSource: "qrc:/icons/draw-ellipse.png"
                            onTriggered: {
                                drawframe.iconSource = iconSource
                                paint.enabled = true
                                console.log("2")
                                paint.flag = 2
                            }
                        }
                    }

                    MenuItem {
                        text: qsTr("Line(L)")
                        iconSource: "qrc:/icons/line.png"
                        onTriggered: {
                            drawframe.iconSource = iconSource
                            paint.enabled = true
                            paint.flag = 4
                        }
                    }
                }
            }

            //马赛克
            Button{
                id:btn_mosaic
                iconSource: "qrc:/icons/mosaic.png"
                width: 40
                height: 40
                onClicked: {
                    filter.mosaic()
                }
            }

            //滤镜
            Button{
                id:btn_filter
                iconSource: "qrc:/icons/filter.png"
                width: 40
                height: 40
                onClicked: {
                    filter.show()
                }
            }

            //撤销
            Button{
                id:undo
                iconSource: "qrc:/icons/revoke.png"
                width: 40
                height: 40

                onClicked: {
                    isCut = paint.isdoCut("undo")
                    paint.undo()
                    if (isCut) {
                        backImg(paint.undo_backRect("undo"))
                    }
                }

            }

            //清除
            Button{
                id:clear
                iconSource: "qrc:/icons/clear.png"
                width: 40
                height: 40
                onClicked: {
                    isCut=paint.isdoCut("clear")
                    paint.clear()
                    if(isCut){
                    backImg(paint.undo_backRect("clear"))
                    }
                    cutImage.cutreUpdate(img.width, img.height)
                }
            }
        }

        //画笔颜色选择
        Row {
            id: selectColor

            padding: 10

            Image {
                source: "qrc:/icons/color.png"
            }

            ColorDialog {
                id: colordialog
                onAccepted: {
                    rect.color = color
                    painterColor = color
                }
            }

            QQC.Button {
                id: colorbutton
                width: 80
                height: 30

                Rectangle {
                    id: rect
                    width: colorbutton.width - 20
                    height: colorbutton.height - 10
                    anchors.centerIn: colorbutton
                    color: painterColor
                }
                onClicked: {
                    colordialog.open()
                }
            }
        }

        //画笔宽度3
        Row {
            id: width

            padding: 10
            Image {
                width: 24
                height: 24
                source: "qrc:/icons/width.png"
            }
            QQC.SpinBox {
                id: paintSpinBox
                width: colorbutton.width
                height: 30
                minimumValue: 1
                maximumValue: 32
                //                decimals : 3
                activeFocusOnPress: false
            }
        }

        //文字颜色选择
        Row {
            id: textcolor

            padding: 10

            Image {
                source: "qrc:/icons/textcolor.png"
            }

            ColorDialog {
                id: textcolordialog
                onAccepted: {
                    rect1.color = color
                    textpaintColor = color
                    console.log(textcolor)
                }
            }

            QQC.Button {
                id: textcolorbutton
                width: 80
                height: 30

                Rectangle {
                    id: rect1
                    width: colorbutton.width - 20
                    height: colorbutton.height - 10
                    anchors.centerIn: textcolorbutton
                    color: textpaintColor
                }
                onClicked: {
                    textcolordialog.open()
                }
            }
        }

        //字号大小
        Row {
            id: fontsize

            padding: 10
            Image {
                width: 24
                height: 24
                source: "qrc:/icons/fontsize.png"
            }
            QQC.SpinBox {
                id: fontSpinBox
                width: colorbutton.width
                height: colorbutton.height
                activeFocusOnPress: false
                stepSize: 10
                minimumValue: 10
                maximumValue: 320
            }
        }
    }

    //右边显示的图像
    ScrollView {
        id: scrollview
        x: leftside.x + leftside.width + 20
        width: content2.width - leftside.width - 20
        height: content2.height
        focus: true

        contentItem: Rectangle {
            id: rec
            width: rectWidth
            height: rectHeight
            clip: true
            Image {
                id: img
                cache: false
                fillMode: Image.PreserveAspectFit
                x: rectX
                y: rectY
                source: "image://screen"
//                source: "file:///tmp/1.jpg"
                TextEdit {
                    id: textedit
                    x: paint.printPoint.x
                    y: paint.printPoint.y
                    focus: false
                    //设置键盘事件
                    Keys.onPressed: {
                        if(event.modifiers===Qt.ControlModifier&&event.key===Qt.Key_Z){
                            console.log("ctrl+z键盘事件被触发")
                            isCut = paint.isdoCut()
                            paint.undo()
                            if (isCut) {
                                backImg(paint.undo_backRect("undo"))
                            }
                        }else{
                            event.accepted=false
                        }
                    }

                    //                    height: paint.rectLength
                    //将其设置为paint.textEdit的原因是避免上次编辑造成的影响
                    text: paint.textEdit
                    font.pixelSize: paint.textFont
                    color: textpaintColor
                    onTextChanged: {
                        if (paint.flag == 1) {
                            textedit.focus = true
                            console.log("setTextEdit")
                            console.log(textedit.text)
                            paint.settextEdit(textedit.text)
                            textedit.visible = true
                        }
                        console.log("qml中文字区域的长度是："+textedit.width)
                    }
                    //当字体颜色改变时
                    onColorChanged: {
                        if (paint.flag === 1) {
                            paint.setTextColor(color)
                        }
                    }
                    //当字体的大小改变时
                    onFontChanged: {
                        if (paint.flag ===1) {
                            paint.setTextFont(textedit.font.pixelSize)
                        }
                    }

                    visible: false
                }

                //涂鸦类
                APaintedItem {
                    id: paint
                    anchors.fill: img
                    enabled: false
                    penColor: painterColor
                    penWidth: paintSpinBox.value
                    textColor: textpaintColor
                    textFont: fontSpinBox.value
                    onClearSignal: {
                        console.log("clearsignal")
                        textedit.text = ""
                        //                        paint.settextEdit(textedit.text)
                    }
                    onUndoSignal: {
                        textedit.text = ""
                    }
                }
                CutImageRect {
                    id: cutImage
                    imgWidth: img.width
                    imgHeight: img.height
                    visible: false
                }
            }

            Connections {
                target: capture
                function onCallImgChanged(){

                    img.source = ""
                    img.source = "image://screen?id="+counter

                    //每次截取新的图片都需要将之前所裁剪矩形（图片）设置成当前图片的大小
                    reUpdate()
                    //重新设置裁剪框的大小
                    cutImage.cutreUpdate(img.width, img.height)
                }
            }
        }
    }
}
