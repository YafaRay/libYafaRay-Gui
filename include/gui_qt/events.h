#pragma once
/****************************************************************************
 *      events.h: custom events to enable thread communication to the UI
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

#ifndef YAFARAY_GUI_QT_EVENTS_H
#define YAFARAY_GUI_QT_EVENTS_H

#include "common/yafaray_gui_common.h"
#include "common/log.h"
#include <QEvent>
#include <QRect>
#include <QString>
#include <QColor>

BEGIN_YAFARAY_GUI

enum QtCustomEvents
{
	GuiUpdate = QEvent::User,
	NotifyView,
	NotifyLayer,
	PutPixel,
	FlushArea,
	Flush,
	HighlightArea,
	HighlightPixel,
	ProgressUpdate,
	ProgressUpdateTag,
	LogAppend,
};

// this event is just to trigger an update in a widget from
// outside the main thread
class QtGuiUpdateEvent final : public QEvent
{
	public:
		explicit QtGuiUpdateEvent(const QRect &rect, bool full_update = false);
		QRect getRect() const { return rect_; }
		bool isFullUpdate() const { return full_update_; }

	private:
		QRect rect_;
		bool full_update_;
};

class QtNotifyViewEvent final  : public QEvent
{
	public:
		explicit QtNotifyViewEvent(const std::string &view_name);
		std::string getViewName() const { return view_name_; }

	private:
		std::string view_name_;
};

class QtNotifyLayerEvent final  : public QEvent
{
	public:
		explicit QtNotifyLayerEvent(const std::string &internal_layer_name, const std::string &exported_layer_name, int width, int height, int exported_channels);
		std::string getInternalLayerName() const { return internal_layer_name_; }
		std::string getExportedLayerName() const { return exported_layer_name_; }
		int getWidth() const { return width_; }
		int getHeight() const { return height_; }
		int getExportedChannels() const { return exported_channels_; }

	private:
		std::string internal_layer_name_;
		std::string exported_layer_name_;
		int width_;
		int height_;
		int exported_channels_;
};

class QtPutPixelEvent final  : public QEvent
{
	public:
		explicit QtPutPixelEvent(const QPoint &point, const QColor &color);
		QPoint getCoords() const { return point_; }
		QColor getColor() const { return color_; }

	private:
		QPoint point_;
		QColor color_;
};

class QtFlushEvent final  : public QEvent
{
	public:
		explicit QtFlushEvent();

	private:
};

class QtFlushAreaEvent final  : public QEvent
{
	public:
		explicit QtFlushAreaEvent(int area_id, const QRect &rect);
		QRect getRect() const { return rect_; }
		int getAreaId() const { return area_id_; }

	private:
		int area_id_ = -1;
		QRect rect_;
};

class QtHighlightAreaEvent final  : public QEvent
{
	public:
		explicit QtHighlightAreaEvent(int area_id, const QRect &rect);
		QRect getRect() const { return rect_; }
		int getAreaId() const { return area_id_; }

	private:
		int area_id_ = -1;
		QRect rect_;
};

class QtProgressUpdateEvent final  : public QEvent
{
	public:
		explicit QtProgressUpdateEvent(int current_steps, int min_steps = 0, int max_steps = 100);
		int getCurrentSteps() const { return current_steps_; }
		int getMinSteps() const { return min_steps_; }
		int getMaxSteps() const { return max_steps_; }

	private:
		int current_steps_;
		int min_steps_;
		int max_steps_;
};

class QtProgressUpdateTagEvent final  : public QEvent
{
	public:
		explicit QtProgressUpdateTagEvent(const char *tag);
		const QString &getTag() const { return tag_; }

	private:
		QString tag_;
};

class QtLogAppendEvent final  : public QEvent
{
	public:
		explicit QtLogAppendEvent(const LogEntry &log_entry);
		const LogEntry &getLogEntry() const { return log_entry_; }

	private:
		LogEntry log_entry_;
};

END_YAFARAY_GUI

#endif
