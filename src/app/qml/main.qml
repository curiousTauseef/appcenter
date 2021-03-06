/****************************************************************************
 * This file is part of App Center.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0 as FluidControls
import Liri.AppCenter 1.0 as AppCenter

FluidControls.ApplicationWindow {
    title: qsTr("App Center")

    width: 800
    height: 600
    visible: true

    Material.primary: Material.Blue
    Material.accent: Material.Blue

    AppCenter.SoftwareManager {
        id: softwareManager

        onSourceAddFailed: snackBar.open(errorMessage)

        Component.onCompleted: softwareManager.initialize()
    }

    AddSourceDialog {
        id: addSourceDialog
        onFailed: snackBar.open(errorMessage)
    }

    FluidControls.SnackBar {
        id: snackBar
    }

    initialPage: FluidControls.TabbedPage {
        title: qsTr("App Center")

        actions: [
            FluidControls.Action {
                icon.source: FluidControls.Utils.iconUrl("content/add")
                text: qsTr("Add source")
                toolTip: qsTr("Add a new source")
                onTriggered: addSourceDialog.open()
            },
            FluidControls.Action {
                icon.source: FluidControls.Utils.iconUrl("navigation/refresh")
                text: qsTr("Check for updates")
                toolTip: qsTr("Check for updates")
                onTriggered: softwareManager.checkForUpdates()
            },
            FluidControls.Action {
                icon.source: FluidControls.Utils.iconUrl("action/search")
                text: qsTr("Search")
                toolTip: qsTr("Search apps")
            }
        ]

        AllAppsTab {}
        InstalledAppsTab {}
        UpdatesTab {}
        SourcesTab {}
    }
}
