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


    MessageDialog{
        id:about
        width: 400
        height: 600
        title: qsTr("About")
        text:qsTr("本截图软件由重庆师范大学软件工程系李梦雪、梁淑贞、张宝丹开发。\n")
    }
}
