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

#include "public_api/yafaray_gui_qt_c_api.h"
#include "common/version_build_info.h"
#include "gui/main_window.h"
#include <QApplication>
#include <cstring>

int yafaray_gui_qt_createRenderWidget(yafaray_Interface_t *yafaray_interface, int width, int height, int border_start_x, int border_start_y, yafaray_bool_t auto_render, yafaray_bool_t close_after_finish)
{
	int argc = 0;
	auto app = new QApplication(argc, nullptr, 0);
	yafaray_gui_qt::MainWindow w(yafaray_interface, width, height, border_start_x, border_start_y, close_after_finish == YAFARAY_BOOL_TRUE);
	w.show();
	w.adjustWindow();
	if(auto_render == YAFARAY_BOOL_TRUE) w.slotRender();
	return QApplication::exec();
}

int yafaray_gui_qt_getVersionMajor() { return yafaray_gui_qt::buildinfo::getVersionMajor(); }
int yafaray_gui_qt_getVersionMinor() { return yafaray_gui_qt::buildinfo::getVersionMinor(); }
int yafaray_gui_qt_getVersionPatch() { return yafaray_gui_qt::buildinfo::getVersionPatch(); }

char *createCString(const std::string &std_string)
{
	const size_t string_size = std_string.size();
	char *c_string = new char[string_size + 1];
	std::strcpy(c_string, std_string.c_str());
	return c_string;
}

char *yafaray_gui_qt_getVersionString()
{
	return createCString(yafaray_gui_qt::buildinfo::getVersionString());
}

void yafaray_gui_qt_deallocateCharPointer(char *string_pointer_to_deallocate)
{
	delete[] string_pointer_to_deallocate;
}