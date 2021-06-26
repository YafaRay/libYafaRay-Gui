#pragma once
/****************************************************************************
 *      events.h: custom events to enable thread communication to the UI
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

#ifndef YAFARAY_EVENTS_H
#define YAFARAY_EVENTS_H

#include "common/yafaray_gui_qt_common.h"
#include <QEvent>
#include <QRect>
#include <QString>

BEGIN_YAFARAY_GUI_QT

enum CustomEvents
{
	GuiUpdate = QEvent::User,
	GuiAreaHighlite,
	ProgressUpdate,
	ProgressUpdateTag
};

// this event is just to trigger an update in a widget from
// outside the main thread
class GuiUpdateEvent : public QEvent
{
	public:
		explicit GuiUpdateEvent(const QRect &rect, bool full_update = false);
		QRect rect() const { return m_rect_; }
		bool fullUpdate() const { return m_full_; }
	private:
		QRect m_rect_;
		bool m_full_;
};

class GuiAreaHighliteEvent : public QEvent
{
	public:
		explicit GuiAreaHighliteEvent(const QRect &rect);
		QRect rect() const { return m_rect_; }
	private:
		QRect m_rect_;
};

class ProgressUpdateEvent : public QEvent
{
	public:
		explicit ProgressUpdateEvent(int progress, int min = -1, int max = -1);
		int progress() const { return m_progress_; }
		int min() const { return m_min_; }
		int max() const { return m_max_; }
	private:
		int m_progress_;
		int m_min_;
		int m_max_;
};

class ProgressUpdateTagEvent : public QEvent
{
	public:
		explicit ProgressUpdateTagEvent(const char *tag);
		const QString &tag() const { return m_tag_; }
		QString &tag() { return m_tag_; }
	private:
		QString m_tag_;
};

END_YAFARAY_GUI_QT

#endif
