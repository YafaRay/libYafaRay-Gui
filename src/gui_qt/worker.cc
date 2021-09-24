/****************************************************************************
 *      worker.cc: a thread for running the rendering process
 *      This is part of the libYafaRay-Gui package
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


#include "gui_qt/main_window.h"
#include "gui_qt/worker.h"
#include "gui_qt/renderwidget.h"

BEGIN_YAFARAY_GUI

QtWorker::QtWorker(::yafaray_Interface_t *yafaray_interface, QtMainWindow *main_window)
	: QThread(), yafaray_interface_(yafaray_interface), main_window_(main_window)
{
}

void QtWorker::run()
{
	if(yafaray_interface_) yafaray_render(yafaray_interface_, QtMainWindow::monitorCallback, this, YAFARAY_DISPLAY_CONSOLE_HIDDEN);
}

END_YAFARAY_GUI