/****************************************************************************
 * This file is part of Liri.
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

#ifndef APPCHOOSERPORTAL_H
#define APPCHOOSERPORTAL_H

#include <QDBusAbstractAdaptor>
#include <QDBusObjectPath>

class AppsModel;

class AppChooserPortal : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.impl.portal.AppChooser")
public:
    explicit AppChooserPortal(QObject *parent);

public Q_SLOTS:
    quint32 ChooseApplication(const QDBusObjectPath &handle,
                              const QString &app_id,
                              const QString &parent_window,
                              const QStringList &choices,
                              const QVariantMap &options,
                              QVariantMap &results);
    void UpdateChoices(const QDBusObjectPath &handle,
                       const QStringList &choices);

private:
    AppsModel *m_appsModel = nullptr;
};

#endif // APPCHOOSERPORTAL_H
