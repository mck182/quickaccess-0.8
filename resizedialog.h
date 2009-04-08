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

#ifndef ResizeDialog_HEADER
#define ResizeDialog_HEADER



//plasma
#include <Plasma/Dialog>

class ResizeDialogPrivate;

class ResizeDialog : public Plasma::Dialog
{
  Q_OBJECT
  public:
    
    explicit ResizeDialog(QWidget * parent = 0, Qt::WindowFlags f =  Qt::Window);
    virtual ~ResizeDialog();
    virtual bool eventFilter(QObject *object, QEvent *event);
    
    
  public slots:
    void updateColors();
    
  
  protected:
    //reimplemented from QObject
    virtual void childEvent(QChildEvent *event);
    
    //reimplemented from QWidget
    virtual void hideEvent ( QHideEvent * event );
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    
  
  private:
    ResizeDialogPrivate * const d;
};

#endif //ResizeDialog_HEADER
