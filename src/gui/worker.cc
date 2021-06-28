/****************************************************************************
 *      worker.cc: a thread for running the rendering process
 *      This is part of the libYafaRay-Gui-Qt package
 *      Copyright (C) 2008-2009 Gustavo Pichorim Boiko
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


#include "gui/main_window.h"
#include "gui/worker.h"
#include "gui/renderwidget.h"

BEGIN_YAFARAY_GUI_QT

Worker::Worker(::yafaray_Interface_t *yafaray_interface, MainWindow *main_window)
	: QThread(), yafaray_interface_(yafaray_interface), main_window_(main_window)
{
}

void Worker::run()
{
	main_window_->render_->setup(QSize(640, 480));
	/* Creating callback output */
	yafaray_setLoggingCallback(yafaray_interface_, Output::loggerCallback, (void *) &main_window_->output_);
	yafaray_paramsSetString(yafaray_interface_, "type", "callback_output");
	yafaray_createOutput(yafaray_interface_, "test_callback_output", YAFARAY_BOOL_TRUE, Output::putPixelCallback, Output::flushAreaCallback, Output::flushCallback, (void *) main_window_->render_.get());
	if(yafaray_interface_) yafaray_render(yafaray_interface_, Output::monitorCallback, main_window_, YAFARAY_DISPLAY_CONSOLE_NORMAL);
}

END_YAFARAY_GUI_QT