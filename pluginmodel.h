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

#ifndef PluginModel_HEADER
#define PluginModel_HEADER

#include <QAbstractListModel>	

class PluginModelPrivate;

class Plugin
{
  public:
    Plugin() :active(false) {}
    ~Plugin() {}
    
    QString name;
    QString prettyName;
    bool active;
    //QIcon mimeIcon;  
};

class PluginModel : public QAbstractListModel
{
  Q_OBJECT
  public:
    PluginModel(QObject *parent = 0);
    ~PluginModel();
    
    Plugin* plugin(const QModelIndex &index);
    Plugin* plugin(int row);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
  
  private:
    PluginModelPrivate * const d;
};



#endif //PluginModel_HEADER
