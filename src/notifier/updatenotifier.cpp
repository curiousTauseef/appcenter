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

#include <LiriAppCenter/SoftwareResource>

#include "updatenotifier.h"

UpdateNotifier::UpdateNotifier(QObject *parent)
    : QObject(parent)
{
    m_softwareManager = new AppCenter::SoftwareManager(this);
    connect(m_softwareManager, &AppCenter::SoftwareManager::updatesAvailable, this,
            &UpdateNotifier::updatesAvailable);
    m_softwareManager->initialize();
}

void UpdateNotifier::checkForUpdates()
{
    m_softwareManager->checkForUpdates();
}

void UpdateNotifier::updatesAvailable(uint count)
{
    if (count == 0)
        return;

    Notification *notification = new Notification(this);
    notification->setApplicationName(QLatin1String("App Center"));
    notification->setApplicationIcon(QLatin1String("software-store"));
    notification->setSummary(tr("Updates available"));
    notification->setBody(updatesSummary());
    notification->setActions(QStringList(tr("Install updates")));
    notification->send();
}

QString UpdateNotifier::updatesSummary()
{
    QVector<AppCenter::SoftwareResource *> updates = m_softwareManager->updates();
    int updatesCount = updates.size();

    if (updatesCount == 0) {
        return tr("No updates are available");
    } else if (updatesCount == 1) {
        return tr("%1 is ready to update").arg(updates.at(0)->name());
    } else if (updatesCount == 2) {
        return tr("%1 and %2 are ready to update").arg(updates.at(0)->name()).arg(updates.at(1)->name());
    } else if (updatesCount == 3) {
        return tr("%1, %2, and one other app are ready to update").arg(updates.at(0)->name()).arg(updates.at(1)->name());
    } else {
        int otherCount = updatesCount - 2;
        return tr("%1, %2, and %3 other apps are ready to update").arg(updates.at(0)->name()).arg(updates.at(1)->name()).arg(otherCount);
    }
}
