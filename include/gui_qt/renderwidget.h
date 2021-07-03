#pragma once
/****************************************************************************
 *      renderwidget.h: the widget for displaying the render output
 *      This is part of the libYafaRay-Gui package
 *      Copyright (C) 2008 Gustavo Pichorim Boiko
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

#ifndef YAFARAY_GUI_RENDERWIDGET_H
#define YAFARAY_GUI_RENDERWIDGET_H

#include "common/yafaray_gui_common.h"
#include "common/output.h"
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QMutex>

BEGIN_YAFARAY_GUI_QT

class QtRenderWidget final : public QLabel
{
		Q_OBJECT

	public:
		explicit QtRenderWidget(QScrollArea *parent = nullptr);
		void setup(const QSize &size);
		void setRenderBorderStart(const QPoint &start) { border_start_ = start; }
		void startRendering();
		bool isRendering() const { return rendering_; }
		void finishRendering();
		void setPixel(int x, int y, const QColor &color);
		void paintColorBuffer();
		void zoomIn(QPoint center);
		void zoomOut(QPoint center);
		bool event(QEvent *event) override;
		Output *output_ = nullptr;

	private:
		void initBuffers();
		void zoom(float zoom_factor, QPoint center);
		void paintEvent(QPaintEvent *event) override;
		void wheelEvent(QWheelEvent *event) override;
		void mousePressEvent(QMouseEvent *event) override;
		void mouseReleaseEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;

		bool rendering_ = true;
		bool panning_ = false;

		QPoint border_start_;
		QSize image_size_;
		float scale_factor_ = 1.f;

		QPoint pan_pos_;
		QPoint bar_pos_;
		QScrollArea *parent_ = nullptr;
		QScrollBar *h_bar_ = nullptr;
		QScrollBar *v_bar_ = nullptr;

		QPixmap pixmap_;
		QMutex buffer_mutex_;

		QImage color_buffer_;
		QImage *active_buffer_ = nullptr;
};

END_YAFARAY_GUI_QT

#endif //YAFARAY_GUI_RENDERWIDGET_H
