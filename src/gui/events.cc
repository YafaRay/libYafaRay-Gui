/****************************************************************************
 *      events.cc: custom events to enable thread communication to the UI
 *      This is part of the libYafaRay-Gui-Qt package
 *      Copyright (C) 2009 Gustavo Pichorim Boiko
 *      Copyright (C) 2009 Rodrigo Placencia Vazquez
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "gui/events.h"

BEGIN_YAFARAY_GUI_QT

GuiUpdateEvent::GuiUpdateEvent(const QRect &rect, bool full_update)
	: QEvent((QEvent::Type)GuiUpdate), rect_(rect), full_update_(full_update)
{
}

PutPixelEvent::PutPixelEvent(const QPoint &point, const QColor &color)
		: QEvent((QEvent::Type)PutPixel), point_(point), color_(color)
{
}

AreaHighlightEvent::AreaHighlightEvent(int area_number, const QRect &rect)
	: QEvent((QEvent::Type)AreaHighlight), area_number_(area_number), rect_(rect)
{
}

ProgressUpdateEvent::ProgressUpdateEvent(int current_steps, int min_steps, int max_steps)
	: QEvent((QEvent::Type)ProgressUpdate), current_steps_(current_steps), min_steps_(min_steps), max_steps_(max_steps)
{
}

ProgressUpdateTagEvent::ProgressUpdateTagEvent(const char *tag)
	: QEvent((QEvent::Type)ProgressUpdateTag), tag_(tag)
{
}

END_YAFARAY_GUI_QT