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

//#include <QPainterPath>
#include <QPainter>

#include <cmath>

#include "effects.h"

namespace Effects
{

QPainterPath overlayPath(const QRect &rect)
{
  QPainterPath path(QPoint(rect.left(), rect.top()));
  path.lineTo(rect.left(), rect.top() + rect.height() * 1/2);
  path.cubicTo(rect.center(), rect.center(), QPoint(rect.left() + rect.width(), rect.top() + rect.height() * 1/2));
  path.lineTo(rect.left() + rect.width(), rect.top());
  path.lineTo(rect.left(), rect.top());
  return path;
}

void drawOverlay(QPainter *painter, const QRect &rect)
{
  painter->save();
  QLinearGradient gradient(rect.center().x(), rect.top(),
			   rect.center().x(), rect.bottom());
    
  gradient.setColorAt(0, QColor(255,255,255, 100));
  gradient.setColorAt(1, QColor(255,255,255, 0));
  QBrush brush(gradient);
  painter->fillRect(rect, brush);
  //painter->fillPath(Effects::overlayPath(rect), brush);
  painter->restore();
}

} //namespace Effects




