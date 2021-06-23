/****************************************************************************
 *      progressbar.h: A progress updater for the yafray GUI
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

#ifndef YAFARAY_GUI_QT_PROGRESS_H
#define YAFARAY_GUI_QT_PROGRESS_H

#include "common/yafaray_gui_qt_common.h"

BEGIN_YAFARAY_GUI_QT

class MainWindow;

class QtProgress final
{
	public:
		QtProgress(MainWindow *window);
		~QtProgress() = default;
		void init(int total_steps);
		void update(int steps = 1);
		void setTag(const char *tag);
		void done();
	private:
		MainWindow *win_ = nullptr;
		int current_step_ = 0;
		int total_steps_ = 0;
};

END_YAFARAY_GUI_QT

#endif //YAFARAY_GUI_QT_PROGRESS_H
