// This is an example Custom Command Qml file. You have full access to the entire Qml language
// for creating any user interface you like. From the ui you can affect the following changes
// with respect to your vehicle:
//    1) Sending COMMAND_LONG commands out over mavlink using QGCButton control
//    2) Modifying parameters
//
// When developing custom Qml file implementations. You must restart QGroundControl to pick up
// the changes. You need to do this even if you select Clear Qml file. Not sure what at the this
// point. Qt must be caching the files somewhere.
// Arguments to CustomCommandWidgetController::sendCommand (Mavlink COMMAND_LONG)
//   command id
//   component id
//   confirmation
//   param 1-7

import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

import QGroundControl.Controls 1.0
import QGroundControl.FactSystem 1.0
import QGroundControl.FactControls 1.0
import QGroundControl.Controllers 1.0

FactPanel {
    id: panel
    focus: true
    
    property var qgcView: null // Temporary hack for broken QGC parameter validation implementation

    CustomCommandWidgetController { id: controller; factPanel: panel }

    // Your own custom changes start here - everything else above is always required

    Column {
        id: main_col
        focus: true
        spacing: 5

        property int dir_FB: 0
        property int dir_LR: 0

        property string direction_text: "Stop"

        Keys.onUpPressed: {
            if (dir_FB < 1) {
                dir_FB = dir_FB + 1
                // console.log('Up pressed: ' + dir_FB)
                if (dir_FB) {
                    direction_text = "Forward"
                    controller.sendCommand(31010,0, 0, 0, 0, 0, 0, 0, 0, 0) // Forward
                } else {
                    direction_text = "Stop"
                    controller.sendCommand(31010,0, 0, 4, 0, 0, 0, 0, 0, 0) // Stop
                }
            }
        }
        Keys.onDownPressed: {
            if (dir_FB > -1) {
                dir_FB = dir_FB - 1
                // console.log('Down pressed: ' + dir_FB)
                if (dir_FB == -1) {
                    direction_text = "Backward"
                    controller.sendCommand(31010,0, 0, 1, 0, 0, 0, 0, 0, 0) // Backward
                } else {
                    direction_text = "Stop"
                    controller.sendCommand(31010,0, 0, 4, 0, 0, 0, 0, 0, 0) // Stop
                }
            }

        }
        Keys.onLeftPressed: {
            if (dir_LR < 1) {
                dir_LR = dir_LR + 1
                // console.log('Left pressed: ' + dir_LR)
                if (dir_LR) {
                    direction_text = "Left"
                    controller.sendCommand(31010,0, 0, 2, 0, 0, 0, 0, 0, 0) // Left
                } else {
                    direction_text = "Stop"
                    controller.sendCommand(31010,0, 0, 4, 0, 0, 0, 0, 0, 0) // Stop
                }
            }

        }
        Keys.onRightPressed: {
            if (dir_LR > -1) {
                dir_LR = dir_LR - 1
                // console.log('Right pressed: ' + dir_LR)
                if (dir_LR == -1) {
                    direction_text = "Right"
                    controller.sendCommand(31010,0, 0, 3, 0, 0, 0, 0, 0, 0) // Right
                } else {
                    direction_text = "Stop"
                    controller.sendCommand(31010,0, 0, 4, 0, 0, 0, 0, 0, 0) // Stop
                }
            }

        }

        // The QGCButton control is provided by QGroundControl.Controls. It is a wrapper around
        // the standard Qml Button element which using the default QGC font and color palette.

        ColumnLayout {
            focus: true
            Label {
                text: "Direction: "
                color: "white"
            }

            Label {
                text: main_col.direction_text
                color: "white"
            }

            RowLayout {
                Button {
                    text: "FORWARD"
                    focus: true
                    onClicked: {
                        main_col.direction_text = "Forward"
                        controller.sendCommand(31010,0, 0, 0, 0, 0, 0, 0, 0, 0)
                    }
                }

                Button {
                    text: "Move for"
                    focus: true
                    onClicked: {
                        main_col.direction_text = "Forward"
                        controller.sendCommand(31011,0, 0, 0, forward_sb.value, 0, 0, 0, 0, 0)
                    }
                }

                SpinBox {
                    id: forward_sb
                    suffix: " sm"
                }
            }

            RowLayout {
                Button {
                    text: "BACKWARD"
                    focus: true
                    onClicked: {
                        main_col.direction_text = "Backward"
                        controller.sendCommand(31010,0, 0, 1, 0, 0, 0, 0, 0, 0)
                    }
                }

                Button {
                    text: "Move for"
                    focus: true
                    onClicked: {
                        main_col.direction_text = "Backward"
                        controller.sendCommand(31011,0, 0, 1, backward_sb.value, 0, 0, 0, 0, 0)
                    }
                }

                SpinBox {
                    id: backward_sb
                    suffix: " sm"
                }
            }

            RowLayout {
                Button {
                    text: "LEFT"
                    focus: true
                    onClicked: {
                        main_col.direction_text = "Left"
                        controller.sendCommand(31010,0, 0, 2, 0, 0, 0, 0, 0, 0)
                    }
                }

                Button {
                    text: "Move for"
                    focus: true
                    onClicked: {
                        main_col.direction_text = "Left"
                        controller.sendCommand(31011,0, 0, 2, left_sb.value, 0, 0, 0, 0, 0)
                    }
                }

                SpinBox {
                    id: left_sb
                    suffix: " sm"
                }
            }

            RowLayout {
                Button {
                    text: "RIGHT"
                    focus: true
                    onClicked: {
                        main_col.direction_text = "Right"
                        controller.sendCommand(31010,0, 0, 3, 0, 0, 0, 0, 0, 0)
                    }
                }

                Button {
                    text: "Move for"
                    focus: true
                    onClicked: {
                        main_col.direction_text = "Right"
                        controller.sendCommand(31011,0, 0, 3, right_sb.value, 0, 0, 0, 0, 0)
                    }
                }

                SpinBox {
                    id: right_sb
                    suffix: " sm"
                }
            }

            Button {
                text: "STOP"
                focus: true
                onClicked: {
                    main_col.direction_text = "Stop"
                    controller.sendCommand(31010,0, 0, 4, 0, 0, 0, 0, 0, 0)
                }
            }
        }
    }
}