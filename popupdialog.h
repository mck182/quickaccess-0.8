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

#ifndef PopupDialog_HEADER
#define PopupDialog_HEADER

#include <QListView>


#include <KAction>



//locale includes
#include "dirmodel.h"
#include "label.h"
#include "iconmanager.h"
#include "resizedialog.h"
#include "settings.h"

class KFileItemDelegate;
class ItemView;
class Button;

class PopupDialog : public ResizeDialog
{
  Q_OBJECT
  
  public:
    
    
    PopupDialog(Settings *settings, QWidget * parent = 0, Qt::WindowFlags f =  Qt::Window);
    ~PopupDialog();

    void setIconSize(int i);
    void setShowPreviews(bool show);
    void setShowHiddenFiles(bool show);
    void setShowOnlyDirs(bool show);
    void setFilter(const QString &filter);
    void setCustomLabel(const QString &label);
    void setShowOnlyIcons(bool onlyIcons);
    KFileItem startItem()
      { return m_start; }
      
    void checkDolphinSorting(const KUrl *dir);

  signals:
    void signal_hide();
  
  public slots:
    void applySettings(Settings::SettingsType);
    void dirListerCompleted();
    void setStartUrl(const KUrl &url);
    void slot_open(const QModelIndex &index);
    void open();
    void updateColors();


  protected:
    //reimplemented from QWidget
    virtual void hideEvent ( QHideEvent * event );

  private slots:
    void sortButtonClicked();
    void slot_sortingTriggered();
    
  private:
    void updateSorting();
    void toggleSingleClick();
    

  private:
    Settings *m_settings;
    Label *m_label;
    Button *m_backButton;
    Button *m_sortButton;
    KFileItem m_start;
    KFileItem m_current;
    ItemView *m_view;
    DirModel *m_model;
    KDirSortFilterProxyModel *m_proxyModel;
    IconManager *m_iconManager;
    KFileItemDelegate *m_delegate;
    QMenu *m_sortMenu;
    QActionGroup *m_sortGroup;
};

#endif
