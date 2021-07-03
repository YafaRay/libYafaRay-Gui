/****************************************************************************
 *      qtoutput.h: a Qt color output for yafray
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

#ifndef YAFARAY_QTOUTPUT_H
#define YAFARAY_QTOUTPUT_H

#include "common/yafaray_gui_qt_common.h"
#include "renderwidget.h"
#include <QImage>

BEGIN_YAFARAY_GUI_QT

class QWidget;

class QtOutput final
{
	public:
		QtOutput(RenderWidget *render);
		void setRenderSize(const QSize &s);
/*
		// inherited from yafaray4::colorOutput_t
		virtual bool putPixel(int x, int y, const yafaray4::ColorLayer &color_layer) override;
		virtual void flush(const yafaray4::RenderControl &render_control) override;
		virtual void flushArea(int x_0, int y_0, int x_1, int y_1) override;
		virtual void highlightArea(int x_0, int y_0, int x_1, int y_1) override;*/

	private:
		RenderWidget *render_buffer_ = nullptr;
};

END_YAFARAY_GUI_QT

#endif
