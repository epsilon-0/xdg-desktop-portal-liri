// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.10
import QtQuick.Controls 2.3
import Fluid.Controls 1.0 as FluidControls
import io.liri.Portal 1.0

QuickDialog {
    id: dialog

    property alias subtitle: subtitleLabel.text
    property alias body: bodyLabel.text
    property bool modal: false
    property alias grantLabel: grantButton.text
    property alias denyLabel: denyButton.text

    width: page.implicitWidth
    height: page.implicitHeight

    visible: true

    Page {
        id: page

        anchors.left: parent.left
        anchors.top: parent.top

        header: FluidControls.DialogLabel {
            text: dialog.title
            padding: 24
        }

        Column {
            FluidControls.SubtitleLabel {
                id: subtitleLabel

                visible: text !== ""
            }

            FluidControls.BodyLabel {
                id: bodyLabel

                visible: text !== ""
            }
        }

        footer: DialogButtonBox {
            Button {
                id: denyButton

                text: qsTr("Deny")

                DialogButtonBox.buttonRole: DialogButtonBox.DestructiveRole

                onClicked: {
                    dialog.rejected();
                    dialog.close();
                }
            }

            Button {
                id: acceptButton

                text: qsTr("Accept")

                DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole

                onClicked: {
                    dialog.accepted();
                    dialog.close();
                }
            }
        }
    }
}
