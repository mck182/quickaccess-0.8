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

#ifndef Settings_HEADER
#define Settings_HEADER

#include <QObject>

#include <KUrl>
#include <KConfigGroup>
#include <KDirModel>

#include "itemview.h"

class Settings : public QObject
{
  Q_OBJECT
  public:
    
    enum SettingsType {
      IconName = 0,
      IconSize = 1,
      Preview = 2,
      ShowHiddenFiles = 3,
      ShowOnlyDirs = 4,
      Filter = 5,
      CustomLabel = 6,
      Url = 7,
      ToolTips = 8,
      ViewMode = 9,
      Sorting = 10,
      All = 11,
      SingleClickNav = 12,
      DolphinSorting = 13
    };
    
    Settings(QObject *parent = 0);
    ~Settings();
    
    void setIconName(const QString &name);
    QString iconName() const;
    
    void setIconSize(const int &size);
    int iconSize() const;
    
    void setShowPreviews(bool show);
    bool showPreviews();
    
    void setShowHiddenFiles(bool show);
    bool showHiddenFiles();
    
    void setShowOnlyDirs(bool show);
    bool showOnlyDirs();
    
    void setFilter(const QString &filter);
    QString filter() const;
    
    void setCustomLabel(const QString &label);
    QString customLabel() const;
    
    void setShowCustomLabel(bool show);
    bool showCustomLabel();
    
    void setUrl(const KUrl &url);
    KUrl url() const;
    
    void setPreviewPlugins(const QStringList &list); //list should be sorted
    QStringList previewPlugins() const;
    
    void setShowToolTips(bool show);
    bool showToolTips();
    
    void setViewMode(ItemView::ViewMode mode);
    ItemView::ViewMode viewMode();
    
    void setAllowNavigation(bool allow);
    bool allowNavigation();
    
    void setSingleClickNavigation(bool allow);
    bool singleClickNavigation();

    void setEnableDolphinSorting(bool allow);
    bool enableDolphinSorting();
    
    void setSortOrder(Qt::SortOrder order);
    Qt::SortOrder sortOrder();
    
    void setSortColumn(KDirModel::ModelColumns column);
    KDirModel::ModelColumns sortColumn();
    
    bool needsSaving();
    
    void saveSettings(KConfigGroup *cg);
    void readSettings(KConfigGroup *cg);
      
  signals:
    void settingsChanged(Settings::SettingsType type);
    
  private:
    
    QString m_iconName;
    int m_iconSize;
    //QSize m_dialogSize;
    bool m_showPreviews;
    bool m_showHiddenFiles;
    bool m_showOnlyDirs;
    QString m_filter;
    QString m_customLabel;
    bool m_showCustomLabel;
    KUrl m_url;
    bool m_showToolTips;
    bool m_needsSaving;
    QStringList m_previewPlugins;
    ItemView::ViewMode m_viewMode;
    bool m_allowNavigation;
    bool m_singleClickNavigation;
    bool m_enableDolphinSorting;
    Qt::SortOrder m_sortOrder;
    KDirModel::ModelColumns m_sortColumn;
  
};

#endif //Settings_HEADER
