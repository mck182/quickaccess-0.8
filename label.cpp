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

#include "label.h"

#include <QPainter>
#include <QPaintEvent>
#include <QHBoxLayout>

#include <KIconLoader>
#include <KIcon>

#include <plasma/theme.h>

//#include <KDebug>

#include "effects.h"

Label::Label(Settings *settings, QWidget *parent)
  :QWidget(parent)
  ,m_settings(settings)
  ,m_openLabel(0)
  ,m_hoverTimeLine(0)
  ,m_hoverTime(0.0)
  ,m_pathLabel(0)
  ,m_iconLabel(0)
{
  m_openString = i18n("Open") + ": ";
  
  m_hoverTimeLine = new QTimeLine( 200, this );
  
  connect( m_hoverTimeLine, SIGNAL(valueChanged(qreal)), this, SLOT(animateHover(qreal)) );
 
  setContentsMargins(5, 5, 5, 5);
  
  QHBoxLayout *layout = new QHBoxLayout();
  layout->setSpacing(0);
  layout->setMargin(0);
  
  layout->addSpacing(2);
  
  m_openLabel = new QLabel(m_openString, this);
  m_openLabel->setFixedWidth(0);
  layout->addWidget(m_openLabel);  
  
  m_iconLabel = new QLabel( this );
  m_iconLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(m_iconLabel);
  
  m_pathLabel = new KSqueezedTextLabel(this);
  m_pathLabel->setAlignment( Qt::AlignCenter);
  m_pathLabel->setTextElideMode ( Qt::ElideLeft );
  layout->addWidget(m_pathLabel);

  layout->addSpacing(2);
  
  setLayout( layout );
    
}

Label::~Label()
{
  delete m_openLabel;
  delete m_hoverTimeLine;
  delete m_pathLabel;
  delete m_iconLabel;

}

void Label::setFileItem(const KFileItem &item)
{
  if(item.isNull()) return;
  
  if(!m_settings->showCustomLabel()){
    if(item.isLocalFile()) {
      m_pathLabel->setText(item.localPath());
    } else {
      m_pathLabel->setText(item.url().prettyUrl());
    }
  } else {
    QString label = item.url().prettyUrl();
    label.replace(m_settings->url().prettyUrl(), m_settings->customLabel());
    m_pathLabel->setText(label);
  }

  //TODO use the icon defined in the settings
  m_iconLabel->setPixmap(KIcon(item.iconName()).pixmap(KIconLoader::SizeSmallMedium, KIconLoader::SizeSmallMedium));
}

void Label::animateHover(qreal value)
{
  m_hoverTime = value;
  QFontMetrics fm(m_openLabel->font());
  m_openLabel->setFixedWidth(fm.width(m_openString) * m_hoverTime);
  update();
}

void Label::mouseReleaseEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton){
    emit clicked();
  }
  QWidget::mouseReleaseEvent(event);
}

void Label::mouseMoveEvent(QMouseEvent *event)
{
  if(m_hoverTime == 0 && m_hoverTimeLine->state() != QTimeLine::Running) {
    m_hoverTimeLine->setDirection(QTimeLine::Forward);
    m_hoverTimeLine->start();
  }
  QWidget::mouseMoveEvent(event);
  
}


void Label::enterEvent(QEvent *event)
{
  if (m_hoverTime > 0) 
    return;
  m_hoverTimeLine->setDirection( QTimeLine::Forward );
  if (m_hoverTimeLine->state() == QTimeLine::Running) {
    m_hoverTimeLine->stop();
  }
  m_hoverTimeLine->start();
  
  QWidget::enterEvent(event);
}

void Label::leaveEvent(QEvent *event)
{
  m_hoverTimeLine->setDirection( QTimeLine::Backward );
  if (m_hoverTimeLine->state() == QTimeLine::Running)
    m_hoverTimeLine->stop();
  m_hoverTimeLine->start();
  
  QWidget::leaveEvent(event);
}

void Label::paintEvent(QPaintEvent *event)
{
  
  QWidget::paintEvent(event);
  QPainter p(this);
  p.setClipRect(event->rect());
  p.setRenderHints(QPainter::Antialiasing);
  QPen pen;
  pen.setWidth(1);
  
  QColor color = palette().color(QPalette::Highlight);
  pen.setColor(color);
  
  const int x = contentsRect().left();
  const int y = contentsRect().top();
  const int width = contentsRect().width();
  const int height = contentsRect().height();
  const int radius = 3;

  
  p.setPen(pen);
  p.drawRoundedRect(contentsRect(), radius, radius);
  
  Effects::drawOverlay(&p, QRect(contentsRect().left() + 1, contentsRect().top() + 1,
				 contentsRect().width() - 2, contentsRect().height() - 2 ));
    color.setAlpha(color.alpha() / 2);
  for(int i = 1; i < x * m_hoverTime ; i++) {
    color.setAlpha(color.alpha() - 10*i);
    pen.setColor(color);
    p.setPen(pen);
    p.drawRoundedRect(QRect(x - i, y - i, width + 2*i, height + 2*i), radius, radius);
  }
  
  

}

