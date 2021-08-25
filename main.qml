import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow{
    id: appRoot
    title: qsTr("Screen-Shot")
    width: 900; height: 480;
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
        //height: 40
        RowLayout{
            id:row
            width:parent.width

            RowLayout{
                id:row1
                Layout.alignment: Qt.AlignLeft
                Button{
                    Layout.preferredWidth: 100
                    text:qsTr("帮助(H)")
                    iconName: "system-help"
                    menu:Menu{
                         MenuItem{
                             text: qsTr("这是什么？");
                             iconName: "help-about"
                             shortcut: "Ctrl+H"
                         }
                    }
                }
                Button{
                    iconName: "document-open"
                    text: qsTr("打开本地图片")
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
                    iconName: "applications-graphics"
                    text: qsTr("注释")
                    onClicked: {
                        if(btn.text==="注释"){
                            btn_1.enabled=false
                            btn_2.enabled=false
                            btn_4.enabled=false
                            btn_3.enabled=true
                            content1.visible=false
                            content2.visible=true
                            btn.text="注释完成"

                        }else{

                            btn.text="注释"
                            btn_1.enabled=true
                            btn_2.enabled=true
                            btn_3.enabled=true
                            btn_4.enabled=true
                            content2.paint1.clear()
                            content1.visible=true
                            content2.visible=false
                        }
                    }
                }
                Button{
                    id:btn_1
                    iconName: "system-search"
                    text: qsTr("工具")
                    menu:Menu{
                        id:menu_2
                        MenuItem{
                            text:qsTr("打开默认截图文件夹")
                            iconName:"document-open"
//                            onTriggered: {
//                                dialogs1.openFileDialog()
//                            }
                        }
                        MenuItem{
                            text:qsTr("打印(P)")
                            iconName: "document-print"
                            shortcut: "Ctrl+P"
                        }
                    }
                }
                Button{
                    id:btn_2
                    iconName: "emblem-shared"
                    text: qsTr("导出")
                    menu:Menu{
                        Menu{
                            title:qsTr("分享")
                            iconName:"document-save"
                            MenuItem{
                                text:qsTr("Imgur")
                                iconName:"applications-science"
                            }
                            MenuItem{
                                text:qsTr("通过电子邮件发送...")
                                iconName:"mail-unread"
                            }
                            MenuItem{
                                text:qsTr("发送到设备")
                                iconName:"phone"
                            }
                        }
                        MenuItem{
                            text:qsTr("更多在线服务")
                        }
                    }
                }
                Button{
                    id:btn_4
                    iconName: "edit-copy"
                    text: qsTr("复制到剪贴板")
                }
                Button{
                    id:btn_3
                    text:qsTr("保存")
                    iconName:"document-save"
                    menu:Menu{
                        id:menu_4
                        MenuItem{
                            text:qsTr("保存")
                            iconName:"document-save"
                            shortcut: "Ctrl+S"
                            onTriggered:{
                                btn_3.text = text
                                btn_3.iconName = iconName
                                dialogs1.fileSaveDialog.selectExisting=false;
                                dialogs1.saveFileDialog()
                            }
                        }
                        MenuItem{
                            text:qsTr("另存为")
                            iconName: "document-save-as"
                            shortcut: "Ctrl+Shift+S"
                            onTriggered:{
                                dialogs1.fileSaveDialog.selectExisting=false;
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
}
