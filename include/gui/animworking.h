#pragma once
/****************************************************************************
 *      animworking.h: a widget to show something is being processed
 *      This is part of the libYafaRay-Gui-Qt package
 *      Copyright (C) 2009 Gustavo Pichorim Boiko
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


#ifndef YAFARAY_ANIMWORKING_H
#define YAFARAY_ANIMWORKING_H

#include "common/yafaray_gui_qt_common.h"
#include <QWidget>
#include <vector>

BEGIN_YAFARAY_GUI_QT

class AnimWorking final : public QWidget
{
		Q_OBJECT

	public:
		explicit AnimWorking(QWidget *parent = nullptr);

	private:
		void paintEvent(QPaintEvent *e) override;
		void timerEvent(QTimerEvent *e) override;

		std::vector<QPixmap> sprites_;
		size_t timer_act_frame_ = 0;
		int timer_id_ = -1;
		static const size_t timer_top_frame_ = 50;
};

END_YAFARAY_GUI_QT

#endif // YAFARAY_ANIMWORKING_H
