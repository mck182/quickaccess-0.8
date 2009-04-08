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

#ifndef PluginWidget_HEADER
#define PluginWidget_HEADER

#include "pluginmodel.h"

#include "ui_pluginwidgetbase.h"

class PluginWidget : public QWidget, private Ui::PluginWidgetBase
{
  Q_OBJECT
  public:
    PluginWidget(QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    virtual ~PluginWidget();
    
    QStringList activePlugins() const;
    void setActivePlugins(const QStringList &list);
    
  public slots:
    void toggle(const QModelIndex &);
    
  private:
    PluginModel *m_model;
  
};


#endif //PluginWidget_HEADER
