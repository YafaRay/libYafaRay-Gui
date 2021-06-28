#pragma once
/****************************************************************************
 *      This is part of the libYafaRay-Gui-Qt package
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

#ifndef LIBYAFARAY_GUI_QT_OUTPUT_H
#define LIBYAFARAY_GUI_QT_OUTPUT_H

#include "common/yafaray_gui_qt_common.h"
#include "gui/images_collection.h"
#include <yafaray_c_api.h>
#include <vector>

BEGIN_YAFARAY_GUI_QT

struct LogEntry
{
	yafaray_LogLevel_t log_level_ = YAFARAY_LOG_LEVEL_MUTE;
	long datetime_ = 0;
	std::string time_of_day_;
	std::string description_;
};

class Output final
{
	public:
		Output(unsigned int width, unsigned int height) : images_collection_(width, height) { }
		static void putPixelCallback(const char *view_name, const char *layer_name, int x, int y, float r, float g, float b, float a, void *callback_user_data);
		static void flushAreaCallback(const char *view_name, int x_0, int y_0, int x_1, int y_1, void *callback_user_data);
		static void flushCallback(const char *view_name, void *callback_user_data);
		static void highlightCallback(const char *view_name, int area_number, int x_0, int y_0, int x_1, int y_1, void *callback_user_data);
		static void monitorCallback(int steps_total, int steps_done, const char *tag, void *callback_user_data);
		static void loggerCallback(yafaray_LogLevel_t log_level, long datetime, const char *time_of_day, const char *description, void *callback_user_data);

		ImagesCollection images_collection_;
		std::vector<LogEntry> log_;
};

END_YAFARAY_GUI_QT

#endif //LIBYAFARAY_GUI_QT_OUTPUT_H
