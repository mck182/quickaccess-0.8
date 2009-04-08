/***************************************************************************
 *   Copyright (C) 2008 by Mark Herbert <wirrkpf@googlemail.com>           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#include <kio/previewjob.h>
#include <KIcon>

#include <QMimeData>

#include "pluginmodel.h"

class PluginModelPrivate
{
  public:
    PluginModelPrivate();
    ~PluginModelPrivate();
    
    QList<Plugin*> pluginList;
  
};

PluginModel::PluginModel(QObject *parent)
  :QAbstractListModel(parent)
  ,d(new PluginModelPrivate())
{
  
}

PluginModel::~PluginModel()
{
  delete d;
}

Plugin* PluginModel::plugin(const QModelIndex &index)
{
  return d->pluginList.at(index.row());
}

Plugin* PluginModel::plugin(int row)
{
  return d->pluginList.at(row);
}

int PluginModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return d->pluginList.count();
}

QVariant PluginModel::data(const QModelIndex &index, int role)const
{
  switch(role) {
    case Qt::DisplayRole:
      return d->pluginList.at(index.row())->prettyName;
    case Qt::DecorationRole:
      if(d->pluginList.at(index.row())->active) return KIcon("dialog-ok");
      return KIcon("dialog-cancel");
    default:
      return QVariant();
  }
}

Qt::ItemFlags PluginModel::flags(const QModelIndex &index) const
{
  Qt::ItemFlags flags = Qt::ItemIsEnabled;
  if(index.isValid()) {
    return flags;
  } 
  return Qt::ItemIsUserCheckable | flags;
}

QModelIndex PluginModel::index(int row, int column, const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  
  if (row < 0 || column != 0)
    return QModelIndex();

  if (row >= d->pluginList.count()) return QModelIndex();

  return createIndex(row, 0, d->pluginList.at(row));
}

///////////PRIVATE////////////////////////////////////
PluginModelPrivate::PluginModelPrivate()
{
  QStringList list = KIO::PreviewJob::availablePlugins();
  for (int i = 0; i < list.size(); ++i) {
    QString name = list.at(i);
    Plugin *plugin = new Plugin();
    plugin->name = name;
    plugin->prettyName = name.remove("thumbnail");
    pluginList.append(plugin);
  }
  
}

PluginModelPrivate::~PluginModelPrivate()
{
  qDeleteAll(pluginList);
}
