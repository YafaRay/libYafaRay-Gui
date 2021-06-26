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

#include "yafaray_gui_qt_c_api.h"
#include <memory>

#ifdef WIN32
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
	const int version_string_size = 100;
	char *version_c_string = (char *) malloc(version_string_size * sizeof(char));
	yafaray_gui_qt_getVersionString(version_c_string, version_string_size);
	const std::string version_string {version_c_string};
	free(version_c_string);
	yafaray_Interface_t *yi = yafaray_createInterface(YAFARAY_INTERFACE_FOR_RENDERING, nullptr, nullptr, nullptr, YAFARAY_DISPLAY_CONSOLE_NORMAL);
	yafaray_printInfo(yi, ("YafaRay GUI Qt loader v" + version_string).c_str());
	yafaray_gui_qt_createRenderWidget(yi, 640, 480, 0, 0, false);
	yafaray_destroyInterface(yi);
	return 0;
}
