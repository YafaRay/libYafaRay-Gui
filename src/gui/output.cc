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

#include "gui/output.h"
#include "gui/images_collection.h"
#include "gui/image.h"
#include "gui/main_window.h"
#include "gui/events.h"
#include "gui/renderwidget.h"
#include <QCoreApplication>

BEGIN_YAFARAY_GUI_QT

void Output::putPixelCallback(const char *view_name, const char *layer_name, int x, int y, float r, float g, float b, float a, void *callback_user_data)
{
	auto render_widget = static_cast<RenderWidget *>(callback_user_data);
	if(!render_widget) return;
	//RgbaFloat rgba(r, g, b, a);
	//output->images_collection_.setColor(view_name, layer_name, x, y, rgba);
	//if(strcmp(layer_name, "combined") == 0) render_widget->setPixel(x, y, QColor(r * 255.f, g * 255.f, b * 255.f, a * 255.f)); //FIXME VIEWS AND LAYERS

	if(strcmp(layer_name, "combined") == 0)
	{
		const QColor color_ldr {
				std::min(static_cast<int>(r * 255.f), 255),
				std::min(static_cast<int>(g * 255.f), 255),
				std::min(static_cast<int>(b * 255.f), 255),
				std::min(static_cast<int>(a * 255.f), 255),
		};
		QCoreApplication::postEvent(render_widget, new PutPixelEvent(QPoint(x, y), color_ldr)); //FIXME VIEWS AND LAYERS
	}
}

void Output::flushAreaCallback(const char *view_name, int x_0, int y_0, int x_1, int y_1, void *callback_user_data)
{
	//printf("**** flushAreaCallback view_name='%s', x_0=%d, y_0=%d, x_1=%d, y_1=%d, callback_user_data=%p\n", view_name, x_0, y_0, x_1, y_1, callback_user_data);
	auto render_widget = (RenderWidget *) callback_user_data;
	if(render_widget) QCoreApplication::postEvent(render_widget, new GuiUpdateEvent(QRect(x_0, y_0, x_1 - x_0, y_1 - y_0)));
}

void Output::flushCallback(const char *view_name, void *callback_user_data)
{
	//printf("**** flushCallback view_name='%s', callback_user_data=%p\n", view_name, callback_user_data);
	auto render_widget = (RenderWidget *) callback_user_data;
	if(render_widget) QCoreApplication::postEvent(render_widget, new GuiUpdateEvent(QRect(), true));
}

void Output::highlightCallback(const char *view_name, int area_number, int x_0, int y_0, int x_1, int y_1, void *callback_user_data)
{
	//printf("**** highlightAreaCallback view_name='%s', area_number=%d, x_0=%d, y_0=%d, x_1=%d, y_1=%d, callback_user_data=%p\n", view_name, area_number, x_0, y_0, x_1, y_1, callback_user_data);
	auto render_widget = (RenderWidget *) callback_user_data;
	if(render_widget) QCoreApplication::postEvent(render_widget, new AreaHighlightEvent(area_number, QRect(x_0, y_0, x_1 - x_0, y_1 - y_0)));
}

void Output::monitorCallback(int steps_total, int steps_done, const char *tag, void *callback_user_data)
{
	auto main_window = static_cast<MainWindow *>(callback_user_data);
	if(!main_window) return;
	if(main_window->label_) QCoreApplication::postEvent(main_window, new ProgressUpdateTagEvent(tag));
	if(main_window->progress_bar_) QCoreApplication::postEvent(main_window, new ProgressUpdateEvent(steps_done, 0, steps_total));
}

void Output::loggerCallback(yafaray_LogLevel_t log_level, long datetime, const char *time_of_day, const char *description, void *callback_user_data)
{
	LogEntry log_entry;
	log_entry.log_level_ = log_level;
	log_entry.datetime_ = datetime;
	log_entry.time_of_day_ = time_of_day;
	log_entry.description_ = description;
	auto output = static_cast<Output *>(callback_user_data);
	if(output) output->log_.emplace_back(log_entry);
}

END_YAFARAY_GUI_QT