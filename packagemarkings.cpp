/*
 * This file is part of mg-package-manager
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (C) 2013 Timo Hannukkala <timo.hannukkala@nomovok.com>
 *
 * Contact: Kyösti Ranto <kyosti.ranto@digia.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#include "packagemarkings.h"
#include <QDebug>

//#define PACKAGEMARKINGS_LOG   	


PackageMarkings::PackageMarkings(QObject *parent) :
    QObject(parent)
{
#ifdef PACKAGEMARKINGS_LOG   	
    qDebug() << Q_FUNC_INFO;	
#endif
	
}

void PackageMarkings::mark(Package *package, bool set)
{
//    qDebug() << Q_FUNC_INFO << package->name() << set;
#ifdef PACKAGEMARKINGS_LOG   	
    qDebug() << Q_FUNC_INFO;	
#endif

    package->mark(set);

    if (set) {
        if (!m_marked.contains(package)) {
            m_marked.append(package);
            emit changed();
        }
    } else {
        if (m_marked.removeAll(package))
            emit changed();
    }
}

void PackageMarkings::resetMarkings()
{
//    qDebug() << Q_FUNC_INFO;
#ifdef PACKAGEMARKINGS_LOG   	
    qDebug() << Q_FUNC_INFO;	
#endif

    if (m_marked.count() == 0)
        return;

    foreach (Package *package, m_marked) {
        package->mark(false);
    }

    m_marked.clear();

    emit changed();
}

int PackageMarkings::count()
{
#ifdef PACKAGEMARKINGS_LOG   	
    qDebug() << Q_FUNC_INFO;	
#endif
    return m_marked.count();
}

QList<Package*> PackageMarkings::packagesMarked()
{
#ifdef PACKAGEMARKINGS_LOG   	
    qDebug() << Q_FUNC_INFO;	
#endif
    return m_marked;
}
