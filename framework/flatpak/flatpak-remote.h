/****************************************************************************
 * This file is part of App Center.
 *
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
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

#ifndef REMOTE_H
#define REMOTE_H

#include "source.h"

#include <QObject>
#include <QString>

#include "base.h"

class Remote : public SoftwareSource
{
    Q_OBJECT

    Q_PROPERTY(QString name MEMBER m_name CONSTANT)
    Q_PROPERTY(QString title MEMBER m_title CONSTANT)
    Q_PROPERTY(QString url MEMBER m_url CONSTANT)

public:
    Remote(FlatpakRemote *remote, QObject *parent = nullptr) : SoftwareSource(parent)
    {
        m_name = flatpak_remote_get_name(remote);
        m_title = flatpak_remote_get_title(remote);
        m_url = flatpak_remote_get_url(remote);
    }

    QString m_name;
    QString m_title;
    QString m_url;
};

#endif // REMOTE_H