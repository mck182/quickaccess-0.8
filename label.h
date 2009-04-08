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

#ifndef Label_HEADER
#define Label_HEADER


//Qt includes
#include <QWidget>
#include <QTimeLine>
#include <QLabel>

//KDE includes
#include <KSqueezedTextLabel>
#include <KFileItem>

//Plasma includes
#include <plasma/svg.h>

#include "settings.h"


//using namespace Plasma;

class Label : public QWidget
{
  Q_OBJECT
  public:
    Label(Settings *settings, QWidget *parent = 0);
    ~Label();
    
    void setFileItem(const KFileItem &);
    
  signals:
    void clicked();
    
    
  protected:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);



    
  private slots:
     void animateHover( qreal );
    
  private:
    
    Settings *m_settings;
    QLabel *m_openLabel;
    QTimeLine *m_hoverTimeLine;
    qreal m_hoverTime;
    KSqueezedTextLabel *m_pathLabel;
    QLabel *m_iconLabel;
    QString m_openString;


  
};

#endif
