import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1


Item {
    default property int motro_id: 0

    Layout.preferredWidth: width
    Layout.preferredHeight: height

    ColumnLayout {
        RowLayout {
            Switch {
                onClicked: { checked: !checked }
            }
            Label {
                text: "Motor #"

                Layout.alignment: Qt.AlignVCenter
            }
            Label {
                text: parent.parent.parent.motro_id

                Layout.alignment: Qt.AlignVCenter
            }
        }
        ComboBox {
            model: ListModel {
                ListElement { text: "Forward" }
                ListElement { text: "Stop" }
                ListElement { text: "Backward" }
            }
        }
    }
}
