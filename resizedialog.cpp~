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

//KDE

//Qt
#include <QMouseEvent>
#include <QCoreApplication>

//Plasma
#include <Plasma/Theme>


#include "resizedialog.h"

class ResizeDialogPrivate
{
  public:
    enum ResizeType {
      Left = 1,
      TopLeft = 2,
      Top = 3,
      TopRight = 4,
      Right = 5,
      BottomRight = 6,
      Bottom = 7,
      BottomLeft = 8,
      NoResize = 9
    };
    
    
    ResizeDialogPrivate();
    ~ResizeDialogPrivate();
    
    Qt::CursorShape cursorShape(const QPoint &);
    ResizeType resizeType(const QPoint &);
    void changeSize();
    void setUpChildren(const QObjectList &objectList);

    ResizeDialog *q;
    ResizeType resize;
    int resizeTimerID;
  
};



ResizeDialog::ResizeDialog(QWidget *parent, Qt::WindowFlags f)
  :Plasma::Dialog(parent, f)
  ,d(new ResizeDialogPrivate)
{
  d->q = this;
  setMouseTracking(true);
  connect(Plasma::Theme::defaultTheme(), SIGNAL(themeChanged()), SLOT(updateColors()));
  updateColors();
}

ResizeDialog::~ResizeDialog()
{
  delete d;
}

void ResizeDialog::updateColors()
{
  QPalette pal = palette();
  pal.setColor(QPalette::Text, Plasma::Theme::defaultTheme()->color( Plasma::Theme::TextColor ));
  pal.setColor(QPalette::WindowText, Plasma::Theme::defaultTheme()->color( Plasma::Theme::TextColor ));
  pal.setColor(QPalette::Base, Qt::transparent);
  pal.setColor(QPalette::Window, Qt::transparent);
  //pal.setColor(QPalette::Button, Qt::transparent);
  pal.setColor(QPalette::ButtonText, Plasma::Theme::defaultTheme()->color( Plasma::Theme::TextColor ));
  setPalette(pal);
}

bool ResizeDialog::eventFilter(QObject *object, QEvent *event)
{
  if(d->resize != ResizeDialogPrivate::NoResize) {
    if(event->type() == QEvent::MouseButtonRelease || event->type() == QEvent::MouseMove ||
       event->type() == QEvent::Enter) {
      QCoreApplication::sendEvent(this, event);
      return true;
    }
  }

  if( event->type() == QEvent::MouseMove ) {
    QCoreApplication::sendEvent(this, event);
  }
  return Plasma::Dialog::eventFilter(object, event);
}

void ResizeDialog::childEvent(QChildEvent *event)
{
  d->setUpChildren(QObjectList() << event->child());
  Plasma::Dialog::childEvent(event);
}

void ResizeDialog::hideEvent (QHideEvent *event)
{
  d->resize = ResizeDialogPrivate::NoResize;
  Plasma::Dialog::hideEvent( event );
}

void ResizeDialog::mouseMoveEvent(QMouseEvent *event)
{
  if(d->resize == ResizeDialogPrivate::NoResize) {
    setCursor(d->cursorShape(event->pos()));
  }
  Plasma::Dialog::mouseMoveEvent(event);
}

void ResizeDialog::mousePressEvent(QMouseEvent *event)
{
  d->resize = d->resizeType(event->pos());
  if(d->resize != ResizeDialogPrivate::NoResize) {
    d->resizeTimerID = startTimer(100);
  }
  
  Dialog::mousePressEvent(event);
}

void ResizeDialog::mouseReleaseEvent(QMouseEvent *event)
{
  if(d->resize != ResizeDialogPrivate::NoResize) {
    killTimer(d->resizeTimerID);
    d->changeSize();
    d->resize = ResizeDialogPrivate::NoResize;
  }
  Dialog::mouseReleaseEvent(event);
}

void ResizeDialog::timerEvent(QTimerEvent *event)
{
  if(event->timerId() == d->resizeTimerID) {
    d->changeSize();
  }
}

ResizeDialogPrivate::ResizeDialogPrivate()
  :resize(NoResize)
  {
  
}

ResizeDialogPrivate::~ResizeDialogPrivate()
{
}

Qt::CursorShape ResizeDialogPrivate::cursorShape(const QPoint &point)
{
  ResizeType type = resizeType(point);
  
  switch (type) {
    case NoResize:
      return Qt::ArrowCursor;
    case Left:
    case Right:
      return Qt::SizeHorCursor;
    case Top:
    case Bottom:
      return Qt::SizeVerCursor;
    case TopLeft:
    case BottomRight:
      return Qt::SizeFDiagCursor;
    case TopRight:
    case BottomLeft:
      return Qt::SizeBDiagCursor;
    default:
      return Qt::ArrowCursor;
  }
  
}

ResizeDialogPrivate::ResizeType ResizeDialogPrivate::resizeType(const QPoint &point)
{
  if(!q->rect().contains(point)) {
    return NoResize;
  }
  
  int top, left, right, bottom;
  q->getContentsMargins(&left, &top, &right, &bottom);
  
  QRect l(0, top, left, q->height() - top - bottom);
  if(l.contains(point)) {
    return Left;
  }
  
  QRect r(q->width() - right, top, right, q->height() - top - bottom);
  if(r.contains(point)) {
    return Right;
  }
  
  QRect t(left, 0, q->width() - left - right, top);
  if(t.contains(point)) {
    return Top;
  }
  
  QRect b(left, q->height() - bottom, q->width() - left - right, bottom );
  if(b.contains(point)) {
    return Bottom;
  }
  
  QRect topleft(0, 0, left, top);
  if(topleft.contains(point)) {
    return TopLeft;
  }
  
  QRect bottomright(q->width() - right, q->height() - bottom, right, bottom);
  if(bottomright.contains(point)) {
    return BottomRight;
  }
  
  QRect topright(q->width() - right, 0, right, top);
  if(topright.contains(point)) {
    return TopRight;
  }
  
  QRect bottomleft(0, q->height() - bottom, left, bottom);
  if(bottomleft.contains(point)) {
    return BottomLeft;
  }
  return NoResize;

}

void ResizeDialogPrivate::changeSize()
{
  QPoint cursorPosition = q->mapFromGlobal(QCursor::pos());
  
  int newX = q->x();
  int newY = q->y();
  int newWidth = q->width();
  int newHeight = q->height();
  
  switch (resize) {
    case Left:
      newWidth = qMax( q->width() - cursorPosition.x(), q->minimumSizeHint().width() );
      newX +=  + q->width() - newWidth;
      break;
      
    case Right:
      newWidth = qMax( cursorPosition.x(), q->minimumSizeHint().width() );
      break;
      
    case Top:
      newHeight = qMax( q->height() - cursorPosition.y(), q->minimumSizeHint().height() );
      newY += q->height() - newHeight;
      break;
      
    case Bottom:
      newHeight = qMax( cursorPosition.y(), q->minimumSizeHint().height() );
      break;
      
    case TopLeft:
      newWidth = qMax( q->width() - cursorPosition.x(), q->minimumSizeHint().width() );
      newHeight = qMax( q->height() - cursorPosition.y(), q->minimumSizeHint().height() );
      newX += q->width() - newWidth;
      newY += q->height() - newHeight;
      break;
      
    case BottomRight:
      newWidth = qMax( cursorPosition.x(), q->minimumSizeHint().width() );
      newHeight = qMax( cursorPosition.y(), q->minimumSizeHint().height() );
      break;
      
    case TopRight:
      newWidth = qMax( cursorPosition.x(), q->minimumSizeHint().width() );
      newHeight = qMax( q->height() - cursorPosition.y(), q->minimumSizeHint().height() );
      newY += q->height() - newHeight;
      break;

    case BottomLeft:
      newWidth = qMax( q->width() - cursorPosition.x(), q->minimumSizeHint().width() );
      newHeight = qMax( cursorPosition.y(), q->minimumSizeHint().height() );
      newX += q->width() - newWidth;
      break;
      
    default:
      break;
      
  }
  q->setGeometry(newX, newY, newWidth, newHeight);
}

void ResizeDialogPrivate::setUpChildren(const QObjectList &objectList)
{
  QObject *object;
  foreach(object, objectList) {
    if(object->isWidgetType()) {
      qobject_cast<QWidget*>(object)->setMouseTracking(true);
    }
    object->installEventFilter(q);
    QObjectList list = object->children();
    if(!list.isEmpty()) {
      setUpChildren(list);
    }
  }
}


#include "resizedialog.moc"
