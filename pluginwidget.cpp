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

#include <KFileItemDelegate>
// #include <KDebug>

#include "pluginwidget.h"

PluginWidget::PluginWidget(QWidget* parent, Qt::WindowFlags fl)
  :QWidget(parent, fl)
{
  setupUi(this);
  //show();
  m_model = new PluginModel(this);
  KFileItemDelegate *delegate = new KFileItemDelegate(this);
  availableView->setModel(m_model);
  availableView->setItemDelegate(delegate);
  connect(availableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(toggle(const QModelIndex &)));
  
}

PluginWidget::~PluginWidget()
{
}

QStringList PluginWidget::activePlugins() const
{
  QStringList list;
  for(int i = 0; i < m_model->rowCount(); ++i) {
    if(m_model->plugin(i)->active)
      list << m_model->plugin(i)->name;
  }
  return list;
}

void PluginWidget::setActivePlugins(const QStringList &list)
{
  for(int i = 0; i < m_model->rowCount(); ++i) {
    for(int j = 0; j < list.count(); ++j) {
      if(m_model->plugin(i)->name == list.at(j)) {
	m_model->plugin(i)->active = true;
      }
    }
  }
  availableView->viewport()->update();
}

void PluginWidget::toggle(const QModelIndex &index)
{
  Plugin *plugin = m_model->plugin(index);
  plugin->active = !plugin->active;
  availableView->update(index);
}

#include "pluginwidget.moc"
