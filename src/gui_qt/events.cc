/****************************************************************************
 *      events.cc: custom events to enable thread communication to the UI
 *      This is part of the libYafaRay-Gui package
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

#include "gui_qt/events.h"

BEGIN_YAFARAY_GUI

QtGuiUpdateEvent::QtGuiUpdateEvent(const QRect &rect, bool full_update)
		: QEvent(static_cast<QEvent::Type>(GuiUpdate)), rect_(rect), full_update_(full_update)
{
}

QtNotifyViewEvent::QtNotifyViewEvent(const std::string &view_name)
		: QEvent(static_cast<QEvent::Type>(NotifyView)), view_name_(view_name)
{
}

QtNotifyLayerEvent::QtNotifyLayerEvent(const std::string &internal_layer_name, const std::string &exported_layer_name, int width, int height, int exported_channels)
		: QEvent(static_cast<QEvent::Type>(NotifyLayer)), internal_layer_name_(internal_layer_name), exported_layer_name_(exported_layer_name), width_(width), height_(height), exported_channels_(exported_channels)
{
}

QtPutPixelEvent::QtPutPixelEvent(const QPoint &point, const QColor &color)
		: QEvent(static_cast<QEvent::Type>(PutPixel)), point_(point), color_(color)
{
}

QtFlushEvent::QtFlushEvent()
		: QEvent(static_cast<QEvent::Type>(Flush))
{
}

QtFlushAreaEvent::QtFlushAreaEvent(int area_id, const QRect &rect)
		: QEvent(static_cast<QEvent::Type>(FlushArea)), area_id_(area_id), rect_(rect)
{
}

QtHighlightAreaEvent::QtHighlightAreaEvent(int area_id, const QRect &rect)
		: QEvent(static_cast<QEvent::Type>(HighlightArea)), area_id_(area_id), rect_(rect)
{
}

QtProgressUpdateEvent::QtProgressUpdateEvent(int current_steps, int min_steps, int max_steps)
		: QEvent(static_cast<QEvent::Type>(ProgressUpdate)), current_steps_(current_steps), min_steps_(min_steps), max_steps_(max_steps)
{
}

QtProgressUpdateTagEvent::QtProgressUpdateTagEvent(const char *tag)
		: QEvent(static_cast<QEvent::Type>(ProgressUpdateTag)), tag_(tag)
{
}

QtLogAppendEvent::QtLogAppendEvent(const LogEntry &log_entry)
		: QEvent(static_cast<QEvent::Type>(LogAppend)), log_entry_(log_entry)
{
}

END_YAFARAY_GUI
