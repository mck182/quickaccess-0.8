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

#ifndef QuickAccess_HEADER
#define QuickAccess_HEADER

//Plasma includes
#include <Plasma/Applet>
#include <plasma/widgets/iconwidget.h>

//locale includes
#include "popupdialog.h"
#include "ui_quickaccessConfig.h"
#include "pluginwidget.h"


class QuickAccess : public Plasma::Applet
{
  Q_OBJECT
  public:

    QuickAccess(QObject *parent, const QVariantList &args);
    ~QuickAccess();

    //Plasma::Applet
    void init();
  
  public slots:
    void applySettings(Settings::SettingsType);
    void toolTipAboutToShow();
    void toolTipHidden();
  
  protected:
    void createConfigurationInterface(KConfigDialog *parent);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void popupEvent(bool show);


  private slots:
    void slot_iconClicked();
    void slotDragEvent();
    void configAccepted();
    void showPreviewToggled(bool checked);
    void saveSettings();

  private:
    PopupDialog* dialog();
    
  private:
    Settings *m_settings;
    Plasma::IconWidget *m_icon;
    PopupDialog *m_dialog;
    QSize m_dialogSize;
    bool m_dragOver;
    Ui::QuickAccessConfig ui;
    PluginWidget *pluginWidget;
    QTimer *m_saveTimer;
};
 
K_EXPORT_PLASMA_APPLET(quickaccess, QuickAccess)
#endif
