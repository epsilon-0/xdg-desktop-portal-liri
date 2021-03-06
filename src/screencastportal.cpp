// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-FileCopyrightText: 2018 Red Hat, Inc
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QGuiApplication>

#include "screencastportal.h"
#include "session.h"
#include "logging_p.h"
#include "waylandintegration.h"

// Read the specifications here:
// https://github.com/flatpak/xdg-desktop-portal/blob/master/data/org.freedesktop.impl.portal.ScreenCast.xml

ScreenCastPortal::ScreenCastPortal(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
}

uint ScreenCastPortal::version() const
{
    return 1;
}

uint ScreenCastPortal::AvailableSourceTypes() const
{
    return Monitor;
}

uint ScreenCastPortal::CreateSession(const QDBusObjectPath &handle,
                                     const QDBusObjectPath &session_handle,
                                     const QString &app_id,
                                     const QVariantMap &options,
                                     QVariantMap &results)
{
    qCDebug(lcScreenCast) << "CreateSession called with parameters:";
    qCDebug(lcScreenCast) << "    handle: " << handle.path();
    qCDebug(lcScreenCast) << "    session_handle: " << session_handle.path();
    qCDebug(lcScreenCast) << "    app_id: " << app_id;
    qCDebug(lcScreenCast) << "    options: " << options;

#ifdef SCREENCAST_ENABLED
    if (m_lastSession) {
        qCWarning(lcScreenCast, "Another screen cast session is running");
        return 2;
    }

    auto *session = Session::createSession(Session::ScreenCast, app_id, session_handle.path(), this);
    if (!session)
        return 2;

    m_lastSession = session;

    return 0;
#else
    qCWarning(lcScreenCast, "Screen cast is not supported");
    return 1;
#endif
}

uint ScreenCastPortal::SelectSources(const QDBusObjectPath &handle,
                                     const QDBusObjectPath &session_handle,
                                     const QString &app_id,
                                     const QVariantMap &options,
                                     QVariantMap &results)
{
    Q_UNUSED(results)

    qCDebug(lcScreenCast) << "SelectSource called with parameters:";
    qCDebug(lcScreenCast) << "    handle: " << handle.path();
    qCDebug(lcScreenCast) << "    session_handle: " << session_handle.path();
    qCDebug(lcScreenCast) << "    app_id: " << app_id;
    qCDebug(lcScreenCast) << "    options: " << options;

#ifdef SCREENCAST_ENABLED
    SourceType types = Monitor;

    auto *session = qobject_cast<ScreenCastSession*>(Session::getSession(session_handle.path()));
    if (!session) {
        qCWarning(lcScreenCast, "Cannot select sources for screen cast: session %s doesn't exist",
                  qPrintable(session_handle.path()));
        return 2;
    }

    if (options.contains(QStringLiteral("multiple")))
        session->setHasMultipleSources(options.value(QStringLiteral("multiple")).toBool());
    if (options.contains(QStringLiteral("types")))
        types = static_cast<SourceType>(options.value(QStringLiteral("types")).toUInt());

    if (types == Window) {
        qCWarning(lcScreenCast, "Screen cast of a window is not implemented");
        return 2;
    }

    // TODO: Remote desktop

    return 0;
#else
    qCWarning(lcScreenCast, "Screen cast is not supported");
    return 1;
#endif
}

uint ScreenCastPortal::Start(const QDBusObjectPath &handle,
                             const QDBusObjectPath &session_handle,
                             const QString &app_id,
                             const QString &parent_window,
                             const QVariantMap &options,
                             QVariantMap &results)
{
    qCDebug(lcScreenCast) << "Start called with parameters:";
    qCDebug(lcScreenCast) << "    handle: " << handle.path();
    qCDebug(lcScreenCast) << "    session_handle: " << session_handle.path();
    qCDebug(lcScreenCast) << "    app_id: " << app_id;
    qCDebug(lcScreenCast) << "    parent_window: " << parent_window;
    qCDebug(lcScreenCast) << "    options: " << options;

#ifdef SCREENCAST_ENABLED
    auto *session = qobject_cast<ScreenCastSession *>(Session::getSession(session_handle.path()));
    if (!session) {
        qCWarning(lcScreenCast, "Cannot start screen cast: session %s doesn't exist",
                  qPrintable(session_handle.path()));
        return 2;
    }

    // TODO: Choose the screen from a window
    QScreen *selectedScreen = QGuiApplication::primaryScreen();

    // Stop streaming when session is closed
    connect(session, &Session::closed, this, [this, selectedScreen] {
        m_lastSession = nullptr;
        WaylandIntegration::instance()->stopStreaming(selectedScreen);
    });

    // Start streaming
    if (!WaylandIntegration::instance()->startStreaming(selectedScreen))
        return 2;

    // Return the streams
    QVariant streams = WaylandIntegration::instance()->streams();
    if (!streams.isValid()) {
        qCWarning(lcScreenCast, "PipeWire stream is not ready");
        return 2;
    }
    results.insert(QStringLiteral("streams"), streams);

    return 0;
#else
    Q_UNUSED(results)
    qCWarning(lcScreenCast, "Screen cast is not supported");
    return 1;
#endif
}
