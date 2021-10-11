import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    property alias fileOpenDialog: fileOpen
    property alias fileSaveDialog: fileSave
    property alias aboutDialog: about

    function openFileDialog() { fileOpen.open(); }
    function saveFileDialog() { fileSave.open(); }
    function openAboutDialog()  {about.open()}

    FileDialog{
        id:fileOpen
        title:"Open A Picture"
        folder: shortcuts.pictures
        nameFilters: [ "Image files (*.png *.jpeg *.jpg)" ]
    }

    FileDialog{
        id:fileSave
        title:"Save A Picture"
        folder: shortcuts.pictures
        nameFilters: [ "Image files (*.png *.jpeg *.jpg)"]
    }

    Dialog{
        id:about
        width: 400
        height: 600
        title: qsTr("About")
//        contentItem:

//            Column{
//            Rectangle{
//                id:rec
//                width: about.width
//                height: 80
//                Row{

//                    spacing: 30
////                    anchors.horizontalCenter: rec
//                    Image{
//                        id:img
//                        source: "./icons/logo.png"
//                        height: 60
//                        width: 60
//                    }
//                    Text {
//                        id: logo
//                        text: qsTr("麒麟截屏")
//                        font.pixelSize: 30
//                    }

//                }
//            }

//            TabBar {
//                id: bar
//                width: about.width
//                Repeater {
//                    model: ["First", "Second", "Third", "Fourth"]

//                    TabButton {
//                        text: modelData
//                        width: Math.max(100, bar.width / 4)
////                        background: Rectangle {
////                            color: "grey"
////                        }
//                    }
//                }
//            }
//        }

    }
}
