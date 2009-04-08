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

#include "itemview.h"

#include <QPainter>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QScrollBar>
#include <qmath.h>
#include <QTimeLine>
#include <QToolTip>
#include <QTimer>
#include <QApplication>

#include <KFileItemDelegate>
#include <KGlobalSettings>
#include <KIcon>
#include <KFileItem>
#include <konq_popupmenu.h>
#include <KBookmarkManager>
#include <kdirsortfilterproxymodel.h>
#include <konq_operations.h>
#include <KConfigGroup>

#include <KDebug>

#include "dirmodel.h"
#include "effects.h"

class ItemView::Private
{
  public:
    Private(ItemView *view);
    ~Private();
    
    void drawBackArrow(QPainter *painter, QStyle::State state) const;
    QRect backArrowRect() const;
    void updateScrollBarRange();
    QPainterPath trianglePath(qreal width = 5, qreal height = 10) const;
    
  public:
    ItemView * const q;
    bool backArrowHover;
    int itemsPerRow; 
    QPersistentModelIndex previousRootIndex;
    QPersistentModelIndex hoveredIndex;
    QPersistentModelIndex watchedIndexForEnter;
    ItemView::ViewMode viewMode;
    QSize gridSize;
    QTimeLine *animationTimeLine;
    QTimer *dragEnterTimer;
    qreal animationTime;
    bool showToolTips;
    bool goBack;
    QRect rubberBand;
    QPoint pressedPos;
    QTimeLine *scrollTimeLine;
    int scrollBarValue;
    int wheelScrollLines;
  
  private:

};



ItemView::ItemView(QWidget *parent)
  :QAbstractItemView(parent)
  ,d(new Private(this))
{
  setMouseTracking(true);
  setAutoScroll(true);
  setDragDropMode(QAbstractItemView::DragDrop);
  
  setEditTriggers(QAbstractItemView::NoEditTriggers);
  
  setFrameShadow(QFrame::Plain);
  
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  
  connect(d->animationTimeLine, SIGNAL(valueChanged(qreal)), this, SLOT(updateAnimation(qreal)));
  connect(d->animationTimeLine, SIGNAL(finished()), this, SLOT(timeLineFinished()));
  connect(d->dragEnterTimer , SIGNAL(timeout()), this, SLOT(dragEnter()));
  
  connect(d->scrollTimeLine, SIGNAL(valueChanged(qreal)), this, SLOT(updateScrollAnimation(qreal)));
  connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrollBarValueChanged(int)));
  
  connect(KGlobalSettings::self(), SIGNAL(settingsChanged(int)), this, SLOT(wheelScrollLinesChanged(int)));
  wheelScrollLinesChanged(KGlobalSettings::SETTINGS_MOUSE);
  
}

ItemView::~ItemView()
{
  delete d;
}

void ItemView::setViewMode(ItemView::ViewMode mode)
{
  if(d->viewMode != mode) {
    d->viewMode = mode;
  }
}

ItemView::ViewMode ItemView::viewMode() const
{
  return d->viewMode;
}

void ItemView::setShowToolTips(bool show)
{
  d->showToolTips = show;
}

bool ItemView::showToolTips()
{
  return d->showToolTips;
}

QRect ItemView::visualRect(const QModelIndex &index) const
{
  if(!index.isValid()) {
    return QRect();
  }

  int topOffset = 0;
  int leftOffset = 0;
  int width = d->gridSize.width();
  
  int backArrowWidth = d->backArrowRect().width() + BACK_ARROW_SPACING;
  
  if(model()->parent(index) != QModelIndex()) {
    if(viewMode() == ItemView::ListMode) {
      width -= backArrowWidth;
    }
    leftOffset += backArrowWidth;
  }

  topOffset -= verticalOffset();
  leftOffset -= horizontalOffset();

  
  int indexRow = index.row() / d->itemsPerRow;

  int indexColumn = index.row() % d->itemsPerRow;
  

  topOffset += indexRow * d->gridSize.height();
  leftOffset += indexColumn * d->gridSize.width();
  
  
  QRect itemRect(leftOffset, topOffset, width , d->gridSize.height());
  return itemRect;
}

void ItemView::setIconSize(const QSize &size)
{
  QAbstractItemView::setIconSize(size);
}

QModelIndex ItemView::indexAt(const QPoint& point) const
{
  if(rootIndex() != QModelIndex() && d->backArrowRect().contains(point)){
    return QModelIndex();
  }
  
  int topOffset = 0 - verticalOffset();
  int leftOffset = 0 - horizontalOffset();
  if(rootIndex() != QModelIndex()) {
    leftOffset += BACK_ARROW_WIDTH;
  }
    
  int rowIndex = (point.y() - topOffset) / d->gridSize.height();
  int columnIndex = (point.x() - leftOffset) / d->gridSize.width();
    
  if(columnIndex >= d->itemsPerRow) return QModelIndex();
    
  int row = rowIndex * d->itemsPerRow + columnIndex;

  
  if(row < model()->rowCount(rootIndex())) {
    return model()->index(row, 0, rootIndex());
  } else {
    return QModelIndex();
  }
}

void ItemView::scrollTo(const QModelIndex& index , ScrollHint hint)
{
  if (!index.isValid()) {
    return;
  }

  QRect itemRect = visualRect(index);
  
  if (itemRect.isValid() && hint == EnsureVisible) {
    d->scrollBarValue = verticalScrollBar()->value();
    if (itemRect.top() < 0) {
      d->scrollBarValue += itemRect.top();

    } else if (itemRect.bottom() > viewport()->height()) {
      d->scrollBarValue +=  itemRect.bottom() - viewport()->height();

    }
    if(d->scrollTimeLine->state() == QTimeLine::Running) {
      d->scrollTimeLine->stop();
    }
    d->scrollTimeLine->setFrameRange(verticalScrollBar()->value(), d->scrollBarValue);
    d->scrollTimeLine->start();
  }
}

int ItemView::horizontalOffset() const
{
  return horizontalScrollBar()->value();
}

int ItemView::verticalOffset() const
{
  return verticalScrollBar()->value();
}

QModelIndex ItemView::moveCursor(CursorAction cursorAction,Qt::KeyboardModifiers modifiers)
{
  Q_UNUSED(modifiers);
  QModelIndex index = currentIndex();
  switch (cursorAction) {
    case MoveUp:
      if (viewMode() == ItemView::IconMode) {
	index = model()->index(index.row() - d->itemsPerRow, 0, rootIndex());
      } else {
	index = model()->index(index.row() - 1, 0, rootIndex());
      }
      setCurrentIndex(index);
      break;
    case MoveDown:
      if (viewMode() == ItemView::IconMode) {
	index = model()->index(index.row() + d->itemsPerRow, 0, rootIndex());
      } else {
	index = model()->index(index.row() + 1, 0, rootIndex());
      }
      setCurrentIndex(index);
      break;
    case MoveLeft:
      if (viewMode() == ItemView::IconMode) {
	index = model()->index(index.row() - 1, 0, rootIndex());
	setCurrentIndex(index);
      }
      break;
    case MoveRight:
      if (viewMode() == ItemView::IconMode) {
	index = model()->index(index.row() + 1, 0, rootIndex());
	setCurrentIndex(index);
      }
      break;
    default:
      // Do nothing
      break;
  }

  // clear the hovered index
  update(d->hoveredIndex);
  d->hoveredIndex = index;

  return index;
}

void ItemView::setSelection(const QRect& rect , QItemSelectionModel::SelectionFlags flags)
{
  QItemSelection selection;
  for(int i = 0; i < model()->rowCount(rootIndex()); i++) {
    if(!visualRect(model()->index(i, 0, rootIndex())).intersects(rect)) continue;
    
    int start = i;
    int end = i;

    while (i < model()->rowCount(rootIndex()) && visualRect(model()->index(i, 0, rootIndex())).intersects(rect)) {
      end = i++;
    }
    selection.select(model()->index(start, 0, rootIndex()), model()->index(end, 0, rootIndex()));
  }
   
  selectionModel()->select(selection,flags);
}

bool ItemView::isIndexHidden(const QModelIndex&) const
{
  return false;
}

QRegion ItemView::visualRegionForSelection(const QItemSelection& selection) const
{
  QRegion region;
  foreach(const QModelIndex& index , selection.indexes()) {
      region |= visualRect(index);
  }
  return region;
}

void ItemView::startDrag(Qt::DropActions supportedActions) 
{
  QDrag *drag = new QDrag(this);
  QMimeData *mimeData = model()->mimeData(selectionModel()->selectedIndexes());
  
  if (!mimeData || mimeData->text().isNull()) {
    return;
  }

  drag->setMimeData(mimeData);


  QModelIndexList list = selectionModel()->selectedIndexes();
  
  if(list.isEmpty()) {
    return;
  }

  QModelIndex idx = list.first();


  QIcon icon = idx.data(Qt::DecorationRole).value<QIcon>();
  drag->setPixmap(icon.pixmap(IconSize(KIconLoader::Desktop)));

  drag->exec(supportedActions);
  QAbstractItemView::startDrag(supportedActions);
}

void ItemView::dragMoveEvent(QDragMoveEvent *event)
{

  if( event->pos().y() < autoScrollMargin() ) {
    QAbstractItemView::dragMoveEvent(event);
    if(verticalScrollBar()->value() != verticalScrollBar()->minimum()) {
      return;//avoid entering a folder while the itemview scrolls
    }
  } else if( viewport()->height() - event->pos().y() < autoScrollMargin() ){
    QAbstractItemView::dragMoveEvent(event);
    if(verticalScrollBar()->value() != verticalScrollBar()->maximum()) {
      return;//avoid entering a folder while the itemview scrolls
    }

  }


  QModelIndex indexUnderMouse = indexAt(event->pos());
  

  if(indexUnderMouse.isValid()) {
    d->goBack = false;

    if(model()->hasChildren(indexUnderMouse)) {

      QModelIndex index = d->hoveredIndex;
      d->hoveredIndex = indexUnderMouse;
      update(d->hoveredIndex);
      update(index);

      if(d->watchedIndexForEnter != indexUnderMouse) {
	d->watchedIndexForEnter = indexUnderMouse;
	d->dragEnterTimer->start(DRAG_ENTER_TIME);
      }

    } else { 

      d->watchedIndexForEnter = QModelIndex();

    }

  } else if (d->backArrowRect().contains(event->pos()) && rootIndex() != QModelIndex()) {
    
    d->watchedIndexForEnter = QModelIndex();
    
    if(!d->goBack) {
      d->goBack = true;
      d->dragEnterTimer->start(DRAG_ENTER_TIME);
    }

  } else {
    d->watchedIndexForEnter = QModelIndex();
    d->dragEnterTimer->stop();
    d->goBack = false;
  }

  event->accept();
}

void ItemView::dragEnterEvent(QDragEnterEvent *event)
{
  event->setAccepted(event->mimeData()->hasUrls());
  setState(QAbstractItemView::DraggingState);
}

void ItemView::scrollBarValueChanged(int value)
{
  if(d->scrollTimeLine->state() != QTimeLine::Running) {
    d->scrollBarValue = value;
  }
}

void ItemView::wheelScrollLinesChanged(int category)
{
  if(category != KGlobalSettings::SETTINGS_MOUSE) return;
  
  KConfig config("kdeglobals");
  KConfigGroup group = config.group("KDE");
  d->wheelScrollLines = group.readEntry("WheelScrollLines", 3);  
}

void ItemView::dropEvent(QDropEvent *event)
{
  d->dragEnterTimer->stop();
  KDirSortFilterProxyModel *proxyModel = static_cast<KDirSortFilterProxyModel*>( model());
  DirModel *model = static_cast<DirModel*>(proxyModel->sourceModel());
  KFileItem item = model->itemForIndex(proxyModel->mapToSource(rootIndex()));


  QDropEvent ev(mapToGlobal(event->pos()), event->dropAction(), event->mimeData(),
		event->mouseButtons(), event->keyboardModifiers());

  KonqOperations::doDrop(item, item.url(), &ev, this);
}

bool ItemView::viewportEvent(QEvent *event)
{
  if(event->type() == QEvent::ToolTip && d->showToolTips) {
    QHelpEvent *helpEvent = dynamic_cast<QHelpEvent*>(event);
    QModelIndex index = indexAt(helpEvent->pos());
    if(!index.isValid() || index == rootIndex()) {
      return false;
    }
    KDirSortFilterProxyModel *proxyModel = dynamic_cast<KDirSortFilterProxyModel*>(model());
    DirModel *model = dynamic_cast<DirModel*>(proxyModel->sourceModel());
    KFileItem item = model->itemForIndex(proxyModel->mapToSource(index));
    QToolTip::showText(mapToGlobal(helpEvent->pos()), item.getToolTipText(), this, visualRect(index));
    return true;
  }
  return QAbstractItemView::viewportEvent(event);

}

void ItemView::contextMenuEvent( QContextMenuEvent *event)
{ 
  QModelIndex index = indexAt(mapFromParent(event->pos()));
  if(!index.isValid() || index == rootIndex()){
    return;
  }

  QModelIndexList list = selectionModel()->selectedIndexes();
  
  if(list.isEmpty()) {
    return;
  }

  KFileItemList items;
  foreach(const QModelIndex &i, list) {
    KFileItem selectedItem = i.data(KDirModel::FileItemRole).value<KFileItem>();
    if(!selectedItem.isNull()) {
      items.append(selectedItem);
    }
  }

  KParts::BrowserExtension::PopupFlags flags = 
         KParts::BrowserExtension::ShowUrlOperations | KParts::BrowserExtension::ShowProperties;

  // Use the Dolphin setting for showing the "Copy To" and "Move To" actions
  KConfig dolphin("dolphinrc");
  if (KConfigGroup(&dolphin, "General").readEntry("ShowCopyMoveMenu", false)) {
      flags |= KParts::BrowserExtension::ShowUrlOperations;
  }

  KActionCollection coll(this);
  
  KDirSortFilterProxyModel *proxyModel = dynamic_cast<KDirSortFilterProxyModel*>(model());
  DirModel *model = dynamic_cast<DirModel*>(proxyModel->sourceModel());
  KFileItem item = model->itemForIndex(proxyModel->mapToSource(index));

  KonqPopupMenu *contextMenu = new KonqPopupMenu(items, item.url() , coll,  0 ,
                                                   KonqPopupMenu::ShowNewWindow, flags, this,
                                                   KBookmarkManager::userBookmarksManager());
  
  if(contextMenu->exec(event->globalPos()) != 0){
    qobject_cast<QWidget*>(parent())->hide();
  }
  delete contextMenu;
}

void ItemView::open(const QModelIndex &index)
{
  const Qt::KeyboardModifiers modifier = QApplication::keyboardModifiers();
  if(modifier == Qt::ShiftModifier || modifier == Qt::ControlModifier) {
    return;
  }
  
  if (model()->canFetchMore(index)) {
    model()->fetchMore(index);
  }
  
  if(model()->hasChildren(index)) {
    d->previousRootIndex = rootIndex();
    setRootIndex(index);
    setCurrentIndex(model()->index(0,0, index));
    if(d->animationTimeLine->state() == QTimeLine::Running) {
      d->animationTimeLine->stop();
      d->animationTimeLine->setDirection(QTimeLine::Backward);
    }
    d->animationTimeLine->start();
  }
  selectionModel()->clearSelection();
  emit signal_open(index);
}

void ItemView::updateAnimation(qreal value)
{
  d->animationTime = value;
  viewport()->update();
}

void ItemView::timeLineFinished()
{
  d->animationTimeLine->toggleDirection();
  if(d->animationTimeLine->direction() ==  QTimeLine::Forward) {
    d->animationTimeLine->start();
  }
}

void ItemView::updateScrollAnimation(qreal value)
{
  Q_UNUSED(value);
  verticalScrollBar()->setValue(d->scrollTimeLine->currentFrame());
}

void ItemView::paintEvent(QPaintEvent *event)
{  
  relayout();//TODO put that in place where it is not called that often but often enough

  QPainter painter(viewport());
  painter.setRenderHints(QPainter::Antialiasing);
  QStyle::State state = 0;
  if(d->backArrowHover) {
    state |= QStyle::State_MouseOver;
  }

  if(d->animationTimeLine->state() == QTimeLine::Running) {
    if(d->animationTimeLine->direction() == QTimeLine::Backward) { // Fade out
      painter.save();
      painter.setOpacity(d->animationTime);
      paintItems(painter, event, d->previousRootIndex);
      painter.restore();
      
      //draw backarrow
      painter.save();    
      if(rootIndex() == QModelIndex()){
	painter.setOpacity(d->animationTime);
	d->drawBackArrow(&painter, state);
      } else if(d->previousRootIndex == QModelIndex()) {
	//do nothing
      } else { //don't fade
	d->drawBackArrow(&painter, state);
      }
      painter.restore();
    } else { //QTimeLine::Forward Fade in
      painter.save();
      painter.setOpacity(d->animationTime);
      paintItems(painter, event, rootIndex());
      painter.restore();
      
      //draw backarrow
      painter.save();
           
      if(rootIndex() == QModelIndex()){
	//do nothing
      } else if(d->previousRootIndex == QModelIndex()) {
	painter.setOpacity(d->animationTime);
	d->drawBackArrow(&painter, state);
      } else { //don't fade
	d->drawBackArrow(&painter, state);
      }
      painter.restore();
    }
  } else { //NotRunning
    paintItems(painter, event, rootIndex());
    
    //draw the rubberband
    if (d->rubberBand.isValid()) {
      QStyleOptionRubberBand opt;
      opt.rect   = d->rubberBand;
      opt.shape  = QRubberBand::Rectangle;
      opt.opaque = false;

      style()->drawControl(QStyle::CE_RubberBand, &opt, &painter);
    }
    
    //draw backarrow    
    if(rootIndex() != QModelIndex()){
      d->drawBackArrow(&painter, state);
    }
  }
}
  

void ItemView::paintItems(QPainter &painter, QPaintEvent *event, const QModelIndex &root)
{
  painter.save();
  const int rows = model()->rowCount(root);

  for (int i = 0; i < rows; ++i) {
    QModelIndex index = model()->index(i, 0, root);
    
    QStyleOptionViewItemV4 option = viewOptions();
    
    option.decorationSize = iconSize();
    option.displayAlignment = Qt::AlignHCenter;
    option.textElideMode = Qt::ElideRight;

    if(viewMode() == ItemView::ListMode) {
      option.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;
      option.decorationPosition  = QStyleOptionViewItem::Left;
    } else {
      option.features = QStyleOptionViewItemV2::WrapText;
      option.displayAlignment = Qt::AlignCenter;
      option.decorationPosition  = QStyleOptionViewItem::Top;
    }
    option.rect = visualRect(index);

    // only draw items intersecting the region of the widget
    // being updated
    if (!event->rect().intersects(option.rect)) {
       continue;
     }

    if (selectionModel()->isSelected(index)) {
      option.state |= QStyle::State_Selected;
    }

    if (index == d->hoveredIndex) {
      option.state |= QStyle::State_MouseOver;
    }

    if (index == currentIndex()) {
      option.state |= QStyle::State_HasFocus;
    }

    itemDelegate(index)->paint(&painter,option,index);
  }
  painter.restore();
}

void ItemView::relayout()
{
  if(viewMode() == ItemView::IconMode) {
    d->gridSize.setWidth(qMax(iconSize().width() + 10, fontMetrics().width("wwwwwwwwwww")));
    d->gridSize.setHeight(iconSize().height() + 10 + fontMetrics().height()*2);
  } else { // ItemView::ListMode
    d->gridSize.setWidth(viewport()->width());
    d->gridSize.setHeight(qMax(iconSize().height(), fontMetrics().height()));
  }
  d->itemsPerRow = viewport()->width() / d->gridSize.width();
  if(d->itemsPerRow == 0) d->itemsPerRow = 1; //force one column

  d->updateScrollBarRange();
}

void ItemView::dragEnter()
{
  if(state() != QAbstractItemView::DraggingState) {
    d->goBack = false;
    d->watchedIndexForEnter = QModelIndex();
    return;
  }
  
  QPoint pos = mapFromGlobal(QCursor::pos());
  if(d->goBack) {
    
    if(d->backArrowRect().contains(pos)) {
      open(rootIndex().parent());
    }

  } else if(d->watchedIndexForEnter == indexAt(pos)) {
    open(d->watchedIndexForEnter);
  }
  d->watchedIndexForEnter = QModelIndex();
  d->goBack = false;
}

void ItemView::resizeEvent(QResizeEvent *event)
{
  viewport()->update();
  QAbstractItemView::resizeEvent(event);
}

void ItemView::mouseMoveEvent(QMouseEvent *event)
{
  if(event->buttons() &= Qt::LeftButton && state() == QAbstractItemView::DragSelectingState) {
    d->rubberBand = QRect(d->pressedPos, event->pos()).normalized();
    setSelection(d->rubberBand, QItemSelectionModel::ClearAndSelect);
    viewport()->update();
    QAbstractItemView::mouseMoveEvent(event);
    return;
  }
  
  bool mouseOverBackArrow = d->backArrowRect().contains(event->pos());

  if (mouseOverBackArrow != d->backArrowHover) {
    d->backArrowHover = mouseOverBackArrow;
    setDirtyRegion(d->backArrowRect());
  }
  QModelIndex index = indexAt(event->pos());
  d->hoveredIndex = index;
  update(index);
  QAbstractItemView::mouseMoveEvent(event);
}

void ItemView::mousePressEvent(QMouseEvent *event)
{
  if(!indexAt(event->pos()).isValid() && event->button() == Qt::LeftButton) {
    d->pressedPos = event->pos();
    setState(QAbstractItemView::DragSelectingState);
  } else {
    d->pressedPos = QPoint();
  }
  QAbstractItemView::mousePressEvent(event);
    
}

void ItemView::mouseReleaseEvent(QMouseEvent *event)
{
  if(d->rubberBand.isValid()) {
    viewport()->update(d->rubberBand);
    d->rubberBand = QRect();
    d->pressedPos = QPoint();
    setState(QAbstractItemView::NoState);
  }
  
  if(d->backArrowRect().contains(event->pos()) && rootIndex() != QModelIndex()) {
    open(rootIndex().parent());
  }
  QAbstractItemView::mouseReleaseEvent(event);
}

void ItemView::wheelEvent(QWheelEvent *event)
{
  if(event->orientation() != Qt::Vertical) {
    QAbstractItemView::wheelEvent(event);
    return;
  }
    
  int degrees = event->delta() / 8;
  int steps = degrees / 15;
  steps *= d->wheelScrollLines;
  
  d->scrollBarValue -= steps * verticalScrollBar()->singleStep();
  if(d->scrollBarValue < verticalScrollBar()->minimum()) d->scrollBarValue = verticalScrollBar()->minimum();
  if(d->scrollBarValue > verticalScrollBar()->maximum()) d->scrollBarValue = verticalScrollBar()->maximum();
  
  if(d->scrollTimeLine->state() == QTimeLine::Running) {
    d->scrollTimeLine->stop();
  }
  d->scrollTimeLine->setFrameRange(verticalScrollBar()->value(), d->scrollBarValue);
  d->scrollTimeLine->start();
}

void ItemView::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Backspace) {
    if(rootIndex().isValid()) {
      open(model()->parent(rootIndex()));
    }
  } else if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
    open(currentIndex());
  } else { 
    QAbstractItemView::keyPressEvent(event);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////PRIVATE///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ItemView::Private::Private(ItemView *view)
  :q(view)
  ,backArrowHover(false)
  ,itemsPerRow(1)
  ,animationTimeLine(new QTimeLine())
  ,dragEnterTimer(new QTimer())
  ,showToolTips(false)
  ,goBack(false)
  ,scrollTimeLine(new QTimeLine())
  ,scrollBarValue(0)

{
  dragEnterTimer->setSingleShot(true);
  animationTimeLine->setDuration(ANIMATION_TIME);
  animationTimeLine->setDirection(QTimeLine::Backward);
  scrollTimeLine->setDuration(ANIMATION_TIME);
}

ItemView::Private::~Private()
{
  delete animationTimeLine;
  delete dragEnterTimer;  
  delete scrollTimeLine;
}

void ItemView::Private::drawBackArrow(QPainter *painter, QStyle::State state) const
{
  painter->save();
  painter->setOpacity(painter->opacity() * 0.5);
  if (state & QStyle::State_MouseOver) {
    painter->setBrush(q->palette().highlight());
  } else {
    painter->setBrush(q->palette().mid());
  }

  QRect rect = backArrowRect();

  // background
  painter->setPen(Qt::NoPen);
  painter->drawRect(rect);

  painter->setPen(QPen(q->palette().dark(), 0));
  painter->drawLine (rect.topRight() + QPointF(0.5, 0),
		     rect.bottomRight() + QPointF(0.5, 0));

     
  painter->setPen(Qt::NoPen);

  if (state & QStyle::State_MouseOver) {
    painter->setBrush(q->palette().highlightedText());
  } else {
    painter->setBrush(q->palette().light());
  }
  painter->translate(rect.center());
  
  painter->drawPath(trianglePath());
  painter->resetTransform();

  painter->restore();
  
}

QRect ItemView::Private::backArrowRect() const
{
  return QRect(0, 0, BACK_ARROW_WIDTH, q->viewport()->height());
}

void ItemView::Private::updateScrollBarRange()
{
  int childCount = q->model()->rowCount(q->rootIndex());
  int pageSize = q->viewport()->height();
  
  int rowHeight = gridSize.height();
  int rows = qCeil((qreal)childCount / (qreal)itemsPerRow);
  
  q->verticalScrollBar()->setRange(0, (rowHeight * rows) - pageSize);
  q->verticalScrollBar()->setPageStep(pageSize);
  q->verticalScrollBar()->setSingleStep(rowHeight);
}

QPainterPath ItemView::Private::trianglePath(qreal width, qreal height) const
{
  QPainterPath path(QPointF(-width/2,0.0));
  path.lineTo(width,-height/2);
  path.lineTo(width,height/2);
  path.lineTo(-width/2,0.0);

  return path;
}


#include "itemview.moc"

