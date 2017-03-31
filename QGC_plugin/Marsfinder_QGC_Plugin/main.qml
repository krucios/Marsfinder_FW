/*
import QtQuick 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1024
    height: 768
    title: qsTr("Marsfinder")

    ColumnLayout {
        spacing: 10
        width: parent.width

        RowLayout {
            id: motors

            spacing: 5
            width: parent.width
            height: 120

            Layout.preferredWidth: width
            Layout.preferredHeight: height

            property int motor_cnt: 8
            property int col_width: (width / motor_cnt) - 5

            MotorCtrl { motro_id: 0; width: parent.col_width; height: parent.height }
            MotorCtrl { motro_id: 1; width: parent.col_width; height: parent.height }
            MotorCtrl { motro_id: 2; width: parent.col_width; height: parent.height }
            MotorCtrl { motro_id: 3; width: parent.col_width; height: parent.height }
            MotorCtrl { motro_id: 4; width: parent.col_width; height: parent.height }
            MotorCtrl { motro_id: 5; width: parent.col_width; height: parent.height }
            MotorCtrl { motro_id: 6; width: parent.col_width; height: parent.height }
            MotorCtrl { motro_id: 7; width: parent.col_width; height: parent.height }
        }

        Column {
            id: move_ctrl_grid

            width: parent.width
            height: move_ctrl.moveControlH * 2 + spacing * 1

            Layout.preferredWidth: width
            Layout.preferredHeight: height

            Grid {
                id: move_ctrl

                property int moveControlH: 50
                property int moveControlW: 50

                width: moveControlW * 3 + spacing * 2
                height: moveControlH * 2 + spacing * 1

                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom

                columns: 3
                spacing: 2

                Rectangle {
                    color: "gray"
                    width: parent.moveControlW
                    height: parent.moveControlH
                }
                Button { // forward
                    width: parent.moveControlW
                    height: parent.moveControlH
                    text: "\u2191"
                }
                Rectangle {
                    color: "gray"
                    width: parent.moveControlW
                    height: parent.moveControlH
                }
                Button { // left
                    width: parent.moveControlW
                    height: parent.moveControlH
                    text: "\u21ba"
                }
                Button { // back
                    width: parent.moveControlW
                    height: parent.moveControlH
                    text: "\u2193"
                }
                Button { // right
                    width: parent.moveControlW
                    height: parent.moveControlH
                    text: "\u21bb"
                }
            }
        }
    }
}
*/

import QtQuick 2.6
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.5

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Demo App")

    function openFile(fileUrl) {
        var request = new XMLHttpRequest();
        request.open("GET", fileUrl, false);
        request.send(null);
        return request.responseText;
    }

    function saveFile(fileUrl, text) {
        var request = new XMLHttpRequest();
        request.open("PUT", fileUrl, false);
        request.send(text);
        return request.status;
    }

    FileDialog {
        id: openFileDialog
        nameFilters: ["Text files (*.txt)", "All files (*)"]
        onAccepted: textEdit.text = openFile(openFileDialog.fileUrl)
    }

    FileDialog {
        id: saveFileDialog
        selectExisting: false
        nameFilters: ["Text files (*.txt)", "All files (*)"]
        onAccepted: saveFile(saveFileDialog.fileUrl, textEdit.text)
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: openFileDialog.open()
            }
            MenuItem {
                text: qsTr("&Save")
                onTriggered: saveFileDialog.open()
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    TextArea {
        id: textEdit
        anchors.fill: parent
        text:
            "Lorem ipsum dolor sit amet, consectetur adipisicing elit, " +
            "sed do eiusmod tempor incididunt ut labore et dolore magna " +
            "aliqua. Ut enim ad minim veniam, quis nostrud exercitation " +
            "ullamco laboris nisi ut aliquip ex ea commodo cosnsequat. ";
    }
}
