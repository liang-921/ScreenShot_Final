import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow{
    id: appRoot
    title: qsTr("麒麟截屏")
    width: 900; height: 480;
    minimumHeight: 480;
    minimumWidth: 680;
    visible: true

    Content1 {
        id: content1
        anchors.fill: parent
    }

    Content2{
        id:content2
        anchors.fill: parent
        visible: false
    }

    statusBar:StatusBar{
        id: statusBar1
        height: row.height + 10

        RowLayout{
            id:row
            width:parent.width
            anchors.verticalCenter: parent.verticalCenter
            RowLayout{
                id:row1
                Layout.alignment: Qt.AlignLeft
                Button{
                    Layout.preferredWidth: 100
                    text:qsTr("帮助(H)")
                    iconName: "system-help"
                    iconSource: "./icons/help.png"
                    menu:Menu{
                        MenuItem{
                            id:btn_help
                            text: qsTr("这是什么?(?)");
                            iconName: "help-faq"
                            iconSource: "./icons/help.png"
                            shortcut: Shortcut{
                                sequence: "Ctrl+?"
                                onActivated: btn_help.triggered()
                            }
                            onTriggered: {
                                dialogs1.openaboutDialog()
                            }
                        }
                        MenuItem{
                            id:btn_error
                            text: qsTr("报告程序缺陷(Tab)...");
                            iconName: "help-contents"
                            iconSource: "./icons/face-sad.png"
                            shortcut: Shortcut{
                                sequence: "Ctrl+Tab"
                                onActivated: btn_error.triggered()
                            }
                            onTriggered: {
                            }
                        }
                        MenuItem{
                            id:btn_about
                            text: qsTr("关于麒麟截屏(H)");
                            iconName: "help-about"
                            iconSource: "./icons/logo.png"
                            shortcut: Shortcut{
                                sequence: "Ctrl+Shift+H"
                                onActivated: btn_about.triggered()
                            }
                            onTriggered: {
                                dialogs1.openAboutDialog()
                            }
                        }
                    }
                }
                Button{
                    id:btn_open
                    text: qsTr("打开本地图片(O)")
                    iconName: "document-open"
                    iconSource: "./icons/open.png"
                    Shortcut{
                        sequence: "Ctrl+O"
                        onActivated: btn_open.clicked()
                    }
                    onClicked: {
                        dialogs1.openFileDialog()
                    }
                }
            }

            RowLayout{
                id:row2
                Layout.alignment: Qt.AlignRight

                Button{
                    id:btn
                    iconSource: "./icons/edit.png"
                    iconName: "borderpainter"
                    text: qsTr("注释(E)")
                    Shortcut{
                        sequence: "Ctrl+E"
                        onActivated: btn.clicked()
                    }
                    onClicked: {
                        if(btn.text==="注释(E)"){
                            btn_1.enabled=false
                            btn_2.enabled=false
                            btn_4.enabled=false
                            btn_3.enabled=true
                            content1.visible=false
                            content2.visible=true
                            btn.text="注释完成"
//                            content2.img_paint.focus=true

                        }else{
                            //将修改过后的涂鸦内容保存
                            content2.paint1.save("file:///tmp/1.jpg")
                            content1.tempDisplay()
                            btn.text="注释(E)"
                            btn_1.enabled=true
                            btn_2.enabled=true
                            btn_3.enabled=true
                            btn_4.enabled=true
                            //                            content2.paint1.clear()
                            content1.visible=true
                            content2.visible=false
//                            content2.img_paint.focus=false
                        }
                    }
                }
                Button{
                    id:btn_1
                    text:qsTr("打印(P)")
                    iconName: "printer"
                    iconSource: "./icons/print.png"
                    Shortcut{
                        sequence: "Ctrl+P"
                        onActivated: btn_1.clicked()
                    }
                    onClicked: {
                        share.startPrinter()
                    }
                }

                Button{
                    id:btn_2
                    iconSource: "./icons/send.png"
                    iconName: "send-to-symbolic"
                    text: qsTr("导出")
                    menu:Menu{
                        Menu{
                            title:qsTr("分享")
                            //点击分享 图片会自动保存至剪贴板 然后分享

                            MenuItem{
                                id:btn_qq
                                text:qsTr("发送到QQ")
                                iconSource: "./icons/qq.png"
                                onTriggered: {
                                    capture.copytoClip()
                                    share.shareToQQ()
                                }
                            }
                            MenuItem{
                                text:qsTr("发送到微信")
                                iconSource: "./icons/wexin.png"
                                onTriggered: {
                                    capture.copytoClip()
                                    share.shareToWeChat()
                                }
                            }
                            MenuItem{
                                text:qsTr("通过电子邮件发送...")
                                iconSource: "./icons/mail.png"
                                onTriggered: {
                                    capture.copytoClip()
                                    share.sendMail()
                                }
                            }
                            MenuItem{
                                text:qsTr("发送到设备")
                                iconSource: "./icons/phone.png"
                            }
                        }
                        Menu{
                            title:qsTr("更多")
                            iconName:"./icons/recoder.png"
                            MenuItem{
                                id:btn_record
                                text:qsTr("全屏录制(R)")
                                iconSource: "./icons/recoder.png"
                                shortcut: Shortcut{
                                    sequence: "Ctrl+Shift+R"
                                    onActivated: btn_record.triggered()
                                }
                                onTriggered: {
                                    console.log("开始录屏")
                                    record.show()
                                    appRoot.hide()
                                }
                            }
                            MenuItem{
                                id:btn_areaRecord
                                text: qsTr("区域录屏(A)")
                                iconSource: "./icons/record.png"
                                shortcut: Shortcut{
                                    sequence: "Ctrl+Shift+A"
                                    onActivated: btn_areaRecord.triggered()
                                }
                                onTriggered: {
                                    record.startRecord()
                                    appRoot.hide()
                                }
                            }
                        }
                    }
                }
                Button{
                    id:btn_4
                    iconSource: "./icons/clip.png"
                    iconName: "edit-copy"
                    text: qsTr("复制到剪贴板(C)")
                    Shortcut{
                        sequence: "Ctrl+Shift+C"
                        onActivated: btn_4.clicked()
                    }
                    onClicked: {
                        capture.copytoClip();
                        $message({
                            "message":"复制成功！",
                            "type":"success",
                            "show":true
                        })
                    }
                }
                Button{
                    id:btn_3
                    text:qsTr("保存(S)")
                    iconName: "document-save"
                    iconSource:"./icons/document-save.png"
                    menu:Menu{
                        id:menu_4
                        MenuItem{
                            text:qsTr("保存(S)")
                            iconName:"document-save"
                            iconSource:"./icons/document-save.png"
                            shortcut:  Shortcut{
                                sequence: "Ctrl+S"
                                onActivated: save_as.triggered()
                            }
                            onTriggered:{
                                btn_3.text = text
                                btn_3.iconName = iconName
                                //dialogs1.fileSaveDialog.selectExisting=false;
                                //dialogs1.saveFileDialog()
                                //content2.paint1.save("")
                            }
                        }
                        MenuItem{
                            id:save_as
                            text:qsTr("另存为")
                            iconName:"document-save-as"
                            iconSource:"./icons/document-save-as.png"
                            shortcut: Shortcut{
                                sequence: "Ctrl+Shift+S"
                                onActivated: save_as.triggered()
                            }

                            onTriggered:{
                                dialogs1.fileSaveDialog.selectExisting=false
                                dialogs1.saveFileDialog()
                            }
                        }
                    }
                }
            }
        }
    }

    //打开 对话框导入图片 另存为对话框 保存图片
    Dialogs{
        id:dialogs1
        fileOpenDialog.onAccepted:{
            content1.selectImage(fileOpenDialog.fileUrl)
            content2.selectImage(fileOpenDialog.fileUrl)
        }
        fileSaveDialog.onAccepted:{
            content2.paint1.save(fileSaveDialog.fileUrl)
        }


    }

    Connections {
        target: record
        function onFinishRecord() {
            appRoot.show()
        }
    }

    Message{

           id:message
           anchors.centerIn: parent

       }

       function $message(data){
           if(data&&data.show){
               message.show=data.show
           }
           if(data&&data.message){
               message.text=data.message
           }
           if(data&&data.type){
               message.type=data.type
           }
           if(data&&data.type&&data.type!=='success'&&data.type!=='error'&&data.type!=='info'){
               return false
           }

           message.openTimer()  //调用Message组件下定时器方法
       }

}
