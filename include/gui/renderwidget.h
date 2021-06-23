/****************************************************************************
 *      renderwidget.h: the widget for displaying the render output
 *      This is part of the libYafaRay-Gui-Qt package
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

#ifndef YAFARAY_GUI_QT_RENDERWIDGET_H
#define YAFARAY_GUI_QT_RENDERWIDGET_H

#include "common/yafaray_gui_qt_common.h"
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QMutex>

BEGIN_YAFARAY_GUI_QT

class RenderWidget final : public QLabel
{
		Q_OBJECT

	public:
		explicit RenderWidget(QScrollArea *parent = nullptr, bool use_zbuffer = false);
		~RenderWidget() override;
		void setup(const QSize &s);
		void setRenderBorderStart(const QPoint &start) { border_start_ = start; }
		void startRendering();
		bool isRendering() const { return rendering_; }
		void finishRendering();
		void setPixel(int x, int y, QRgb color, QRgb alpha);
		void paintColorBuffer();
		void paintAlpha();
		void zoomIn(QPoint m_pos);
		void zoomOut(QPoint m_pos);
		bool event(QEvent *e) override;

	private:
		void initBuffers();
		void zoom(float f, QPoint m_pos);
		void paintEvent(QPaintEvent *e) override;
		void wheelEvent(QWheelEvent *evt) override;
		void mousePressEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;

		bool use_zbuf_;
		bool rendering_;
		bool panning_;

		QPoint border_start_;
		QSize image_size_;
		float scale_factor_;

		QPoint pan_pos_;
		QPoint bar_pos_;
		QScrollArea *owner_;
		QScrollBar *h_bar_;
		QScrollBar *v_bar_;

		QPixmap pix_;
		QMutex buffer_mutex_;

		QImage color_buffer_;
		QImage alpha_channel_;
		QImage *active_buffer_;
};

END_YAFARAY_GUI_QT

#endif //YAFARAY_GUI_QT_RENDERWIDGET_H
