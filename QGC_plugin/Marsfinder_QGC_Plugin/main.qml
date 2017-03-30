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
