/****************************************************************************
 *      renderwidget.cc: a widget for displaying the rendering output
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

#include "gui_qt/renderwidget.h"
#include "gui_qt/events.h"
#include "common/image.h"
#include <QDebug>
#include <QApplication>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>

BEGIN_YAFARAY_GUI_QT

/*=====================================
/	RenderWidget implementation
/=====================================*/

QtRenderWidget::QtRenderWidget(QScrollArea *parent): QLabel(static_cast<QWidget *>(parent)), parent_(parent), h_bar_(parent_->horizontalScrollBar()), v_bar_(parent_->verticalScrollBar())
{
	setScaledContents(true);
}

void QtRenderWidget::setup(const QSize &size)
{
	image_size_ = size;
	initBuffers();
	QPalette palette;
	palette.setColor(QPalette::Background, QColor(0, 0, 0, 0));
	setPalette(palette);
}

void QtRenderWidget::initBuffers()
{
	color_buffer_ = QImage(image_size_, QImage::Format_ARGB32);
	color_buffer_.fill(QColor(0, 0, 0, 0));
	resize(image_size_);
	active_buffer_ = &color_buffer_;
	pixmap_ = QPixmap::fromImage(*active_buffer_);
	setPixmap(pixmap_);
}

void QtRenderWidget::startRendering()
{
	rendering_ = true;
	scale_factor_ = 1.f;
	initBuffers();
}

void QtRenderWidget::finishRendering()
{
	rendering_ = false;
	pixmap_ = QPixmap::fromImage(*active_buffer_);
	setPixmap(pixmap_);
	update();
}

void QtRenderWidget::setPixel(int x, int y, const QColor &color)
{
	const int ix = x + border_start_.x();
	const int iy = y + border_start_.y();
	color_buffer_.setPixelColor(ix, iy, color);
}

void QtRenderWidget::paintColorBuffer()
{
	buffer_mutex_.lock();
	pixmap_ = QPixmap::fromImage(color_buffer_);
	setPixmap(pixmap_);
	active_buffer_ = &color_buffer_;
	buffer_mutex_.unlock();
	if(!rendering_) zoom(1.f, QPoint(0, 0));
}

void QtRenderWidget::zoom(float zoom_factor, QPoint center)
{
	scale_factor_ *= zoom_factor;
	const QSize new_size = scale_factor_ * active_buffer_->size();
	resize(new_size);
	pixmap_ = QPixmap::fromImage(active_buffer_->scaled(new_size));
	update(parent_->viewport()->geometry());
	const QPoint m = (center * zoom_factor) - center;
	const int dh = h_bar_->value() + (m.x());
	const int dv = v_bar_->value() + (m.y());
	h_bar_->setValue(dh);
	v_bar_->setValue(dv);
}

void QtRenderWidget::zoomIn(QPoint center)
{
	if(scale_factor_ > 5.f) return;
	zoom(1.25f, center);
}

void QtRenderWidget::zoomOut(QPoint center)
{
	if(scale_factor_ < 0.2f) return;
	zoom(0.8f, center);
}

bool QtRenderWidget::event(QEvent *event)
{
	if(event->type() == static_cast<QEvent::Type>(GuiUpdate) && rendering_)
	{
		const auto ge = static_cast<QtGuiUpdateEvent *>(event);
		ge->accept();
		if(ge->isFullUpdate())
		{
			buffer_mutex_.lock();
			QPainter p(&pixmap_);
			p.drawImage(QPoint(0, 0), *active_buffer_);
			buffer_mutex_.unlock();
			update();
		}
		else
		{
			buffer_mutex_.lock();
			QPainter p(&pixmap_);
			p.drawImage(ge->getRect(), *active_buffer_, ge->getRect());
			buffer_mutex_.unlock();
			update(ge->getRect());
		}
		return true;
	}
	else if(event->type() == static_cast<QEvent::Type>(PutPixel))
	{
		const auto ge = static_cast<QtPutPixelEvent *>(event);
		ge->accept();
		buffer_mutex_.lock();
		const auto coords = ge->getCoords();
		setPixel(coords.x(), coords.y(), ge->getColor());
		buffer_mutex_.unlock();
		update();
		return true;
	}
	else if(event->type() == static_cast<QEvent::Type>(Flush))
	{
		const auto ge = static_cast<QtFlushEvent *>(event);
		ge->accept();
		buffer_mutex_.lock();
		const int width = static_cast<int>(output_->images_collection_.getWidth());
		const int height = static_cast<int>(output_->images_collection_.getHeight());
		for(int x = 0; x < width; ++x)
		{
			for(int y = 0; y < height; ++y)
			{
				const RgbaFloat col = output_->images_collection_.getColor("view_1", "combined", x, y);
				const QColor qcol { col.getR8Bit(), col.getG8Bit(), col.getB8Bit(), col.getA8Bit() };
				setPixel(x, y, qcol);
			}
		}
		buffer_mutex_.unlock();
		update();
		return true;
	}
	else if(event->type() == static_cast<QEvent::Type>(FlushArea))
	{
		const auto ge = static_cast<QtFlushAreaEvent *>(event);
		ge->accept();
		buffer_mutex_.lock();
		int x_0, x_1, y_0, y_1;
		ge->getRect().getCoords(&x_0, &y_0, &x_1, &y_1);
		for(int x = x_0; x < x_1; ++x)
		{
			for(int y = y_0; y < y_1; ++y)
			{
				const RgbaFloat col = output_->images_collection_.getColor("view_1", "combined", x, y);
				const QColor qcol { col.getR8Bit(), col.getG8Bit(), col.getB8Bit(), col.getA8Bit() };
				setPixel(x, y, qcol);
			}
		}
		buffer_mutex_.unlock();
		update();
		return true;
	}
	else if(event->type() == static_cast<QEvent::Type>(AreaHighlight) && rendering_)
	{
		const auto ge = static_cast<QtAreaHighlightEvent *>(event);
		QPainter p(&pixmap_);
		ge->accept();
		const int line_l = std::min(4, std::min(ge->getRect().height() - 1, ge->getRect().width() - 1));
		const QPoint tr(ge->getRect().topRight());
		const QPoint tl(ge->getRect().topLeft());
		const QPoint br(ge->getRect().bottomRight());
		const QPoint bl(ge->getRect().bottomLeft());
		p.setPen(QColor(160, 0, 0));
		//top-left corner
		p.drawLine(tl, QPoint(tl.x() + line_l, tl.y()));
		p.drawLine(tl, QPoint(tl.x(), tl.y() + line_l));
		//top-right corner
		p.drawLine(tr, QPoint(tr.x() - line_l, tr.y()));
		p.drawLine(tr, QPoint(tr.x(), tr.y() + line_l));
		//bottom-left corner
		p.drawLine(bl, QPoint(bl.x() + line_l, bl.y()));
		p.drawLine(bl, QPoint(bl.x(), bl.y() - line_l));
		//bottom-right corner
		p.drawLine(br, QPoint(br.x() - line_l, br.y()));
		p.drawLine(br, QPoint(br.x(), br.y() - line_l));
		update(ge->getRect());
		return true;
	}
	return QLabel::event(event);
}

void QtRenderWidget::paintEvent(QPaintEvent *event)
{
	const QRect r = event->rect();
	QPainter painter(this);
	painter.setClipRegion(event->region());
	painter.drawPixmap(r, pixmap_, r);
}

void QtRenderWidget::wheelEvent(QWheelEvent *event)
{
	event->accept();
	if(!rendering_ && !panning_ && (event->modifiers() & Qt::ControlModifier))
	{
		if(event->delta() > 0) zoomIn(event->pos());
		else zoomOut(event->pos());
	}
}

void QtRenderWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::MidButton)
	{
		setCursor(Qt::SizeAllCursor);
		panning_ = true;
		pan_pos_ = event->globalPos();
		bar_pos_ = QPoint(h_bar_->value(), v_bar_->value());
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void QtRenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::MidButton)
	{
		setCursor(Qt::ArrowCursor);
		panning_ = false;
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void QtRenderWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(panning_)
	{
		const QPoint dpos = bar_pos_ + (pan_pos_ - event->globalPos());
		h_bar_->setValue(dpos.x());
		v_bar_->setValue(dpos.y());
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

END_YAFARAY_GUI_QT