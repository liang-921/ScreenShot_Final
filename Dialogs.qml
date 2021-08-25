import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    property alias fileOpenDialog: fileOpen
    property alias fileSaveDialog: fileSave

    function openFileDialog() { fileOpen.open(); }
    function saveFileDialog() { fileSave.open(); }

    FileDialog{
        id:fileOpen
        title:"Open A picture"
        folder: shortcuts.pictures
        nameFilters: [ "Image files (*.png *.jpeg *.jpg)" ]
    }

    FileDialog{
        id:fileSave
        title:"Save A picture"
        folder: shortcuts.pictures
        nameFilters: [ "Image files (*.png *.jpeg *.jpg)" ]
    }
}
