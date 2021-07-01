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
#include "common/output.h"

BEGIN_YAFARAY_GUI_QT

Worker::Worker(::yafaray_Interface_t *yafaray_interface, MainWindow *main_window)
	: QThread(), yafaray_interface_(yafaray_interface), main_window_(main_window)
{
}

void Worker::run()
{
	const int output_width = yafaray_getSceneFilmWidth(yafaray_interface_);
	const int output_height = yafaray_getSceneFilmHeight(yafaray_interface_);
	Output output(output_width, output_height);
	char *views_table = yafaray_getViewsTable(yafaray_interface_);
	char *layers_table = yafaray_getLayersTable(yafaray_interface_);
	yafaray_printVerbose(yafaray_interface_, views_table);
	yafaray_printVerbose(yafaray_interface_, layers_table);
	main_window_->render_widget_->setup(QSize(output_width, output_height));

	yafaray_paramsSetString(yafaray_interface_, "type", "callback_output");
	yafaray_createOutput(yafaray_interface_, "test_callback_output", YAFARAY_BOOL_TRUE);

	yafaray_setOutputPutPixelCallback(yafaray_interface_, "test_callback_output", Output::putPixelCallback, static_cast<void *>(main_window_->render_widget_.get()));
	yafaray_setOutputFlushAreaCallback(yafaray_interface_, "test_callback_output", Output::flushAreaCallback, static_cast<void *>(main_window_->render_widget_.get()));
	yafaray_setOutputFlushCallback(yafaray_interface_, "test_callback_output", Output::flushCallback, static_cast<void *>(main_window_->render_widget_.get()));
	yafaray_setOutputHighlightCallback(yafaray_interface_, "test_callback_output", Output::highlightCallback, static_cast<void *>(main_window_->render_widget_.get()));
	if(yafaray_interface_) yafaray_render(yafaray_interface_, Output::monitorCallback, main_window_, YAFARAY_DISPLAY_CONSOLE_HIDDEN);
	yafaray_removeOutput(yafaray_interface_, "test_callback_output");
	yafaray_deallocateCharPointer(layers_table);
	yafaray_deallocateCharPointer(views_table);
}

END_YAFARAY_GUI_QT