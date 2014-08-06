/*
 * Copyright (C) 2014 Canonical Ltd
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

#include "generictimezonemodel.h"

#include <QDebug>

GenericTimeZoneModel::GenericTimeZoneModel(QObject *parent) :
    TimeZoneModel(parent)
{
}

QList<QVariant> GenericTimeZoneModel::results() const
{
    return m_results;
}

void GenericTimeZoneModel::setResults(const QList<QVariant> &results)
{
    if(m_results == results) {
        // Don't parse the results again if it is the same results being set again
        return;
    }

    // Change the results and emit the changed signal to let QML know
    m_results = results;
    emit resultsChanged();

    // Parse through results
    loadTimeZonesFromVariantList();
}

void GenericTimeZoneModel::loadTimeZonesFromVariantList()
{
    if(m_results.isEmpty()) {
        // Don't parse an empty results
        return;
    }

    // Let QML know model is being reset and rebuilt
    beginResetModel();

    m_timeZones.clear();

    TimeZone tz;

    /*
     Cycle through the u1db query model results and transfer them to the
     TimeZone list.
    */
    for (int i=0; i < m_results.size(); i++) {
        // Map query model results to timezone tz
        tz.cityName = m_results.value(i).toMap().value("city").toString();
        tz.country = m_results.value(i).toMap().value("country").toString();
        tz.timeZoneId = m_results.value(i).toMap().value("timezone").toString();

        m_timeZones.append(tz);

        // Clear tz before next iteration
        tz = TimeZone();
    }


    // Let QML know model is reusable again
   endResetModel();
}