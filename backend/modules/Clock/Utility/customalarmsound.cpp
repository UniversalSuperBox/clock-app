/*
 * Copyright (C) 2015 Canonical Ltd
 *
 * This file is part of Ubuntu Clock App
 *
 * Ubuntu Clock App is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * Ubuntu Clock App is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDir>
#include <QStandardPaths>

#include "customalarmsound.h"

CustomAlarmSound::CustomAlarmSound(QObject *parent):
    QObject(parent),
    m_customAlarmDir(QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first() + "/CustomSounds/")
{
}

QString CustomAlarmSound::alarmSoundDirectory() const
{
    return m_customAlarmDir;
}

void CustomAlarmSound::deleteAlarmSound(const QString &soundName)
{
    QDir dir(m_customAlarmDir);
    dir.remove(soundName);
}

void CustomAlarmSound::createAlarmSoundDirectory()
{
    QDir dir(m_customAlarmDir);

    if (dir.exists()) {
        return;
    }

    dir.mkpath(m_customAlarmDir);
}