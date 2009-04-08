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

#ifndef ItemView_HEADER
#define ItemView_HEADER

#include <QAbstractItemView>

static const int BACK_ARROW_WIDTH = 16;
static const int BACK_ARROW_SPACING = 5;
static const int ANIMATION_TIME = 100;
static const int DRAG_ENTER_TIME = 1000;

class ItemView : public QAbstractItemView
{
  Q_OBJECT
  public:
    enum ViewMode{
      ListMode = 0,
      IconMode = 1      
    };
    

    ItemView(QWidget *parent = 0);
    ~ItemView();
    
    void setViewMode(ItemView::ViewMode mode);
    ItemView::ViewMode viewMode() const;
    void setShowToolTips(bool show);
    bool showToolTips();
    
    //QAbstractItemView
    QRect visualRect(const QModelIndex &index) const;
    void setIconSize(const QSize &size);
    QModelIndex indexAt(const QPoint& point) const;
    void scrollTo(const QModelIndex& index, ScrollHint hint = EnsureVisible);
    
  public slots:
    void open(const QModelIndex &index = QModelIndex());
    void updateAnimation(qreal);
    void timeLineFinished();
    void updateScrollAnimation(qreal);
    
  signals:
    void signal_open(const QModelIndex &);

  protected:
    //QWidget
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    
    //QAbstractItemView
    int horizontalOffset() const;
    int verticalOffset() const;
    QModelIndex moveCursor(CursorAction cursorAction,Qt::KeyboardModifiers modifiers);
    void setSelection(const QRect& rect , QItemSelectionModel::SelectionFlags flags);
    bool isIndexHidden(const QModelIndex& index) const;
    QRegion visualRegionForSelection(const QItemSelection& selection) const;
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);
    void dragMoveEvent(QDragMoveEvent *event);
    bool viewportEvent(QEvent *event);
    
    //QAbstractScrollArea
    void contextMenuEvent( QContextMenuEvent *event);
    
  private:
    void paintItems(QPainter &painter, QPaintEvent *event, const QModelIndex &index);
    void relayout();
    
  private slots:
    void dragEnter();
    void scrollBarValueChanged(int value);
    void wheelScrollLinesChanged(int category);
  
  private:
    class Private;
    Private * const d;
};

#endif //ItemView_HEADER
