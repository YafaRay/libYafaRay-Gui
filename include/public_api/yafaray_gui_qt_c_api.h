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

#ifndef YAFARAY_GUI_QT_C_API_H
#define YAFARAY_GUI_QT_C_API_H

#include "yafaray_gui_qt_c_api_export.h"
#include <yafaray_c_api.h>

#define YAFARAY_GUI_QT_C_API_VERSION_MAJOR 4

#ifdef __cplusplus
extern "C" {
#endif

	YAFARAY_GUI_QT_C_API_EXPORT int yafaray_gui_qt_createRenderWidget(yafaray_Interface_t *yafaray_interface, int width, int height, int border_start_x, int border_start_y, yafaray_bool_t auto_render, yafaray_bool_t close_after_finish);
	YAFARAY_GUI_QT_C_API_EXPORT int yafaray_gui_qt_getVersionMajor();
	YAFARAY_GUI_QT_C_API_EXPORT int yafaray_gui_qt_getVersionMinor();
	YAFARAY_GUI_QT_C_API_EXPORT int yafaray_gui_qt_getVersionPatch();
	/* The following functions return a text string where memory is allocated by libYafaRay itself. Do not free the char* directly with free, use "yafaray_gui_qt_deallocateCharPointer" to free them instead to ensure proper deallocation. */
	YAFARAY_GUI_QT_C_API_EXPORT char *yafaray_gui_qt_getVersionString();
	YAFARAY_GUI_QT_C_API_EXPORT void yafaray_gui_qt_deallocateCharPointer(char *string_pointer_to_deallocate);

#ifdef __cplusplus
}
#endif

#endif /* YAFARAY_GUI_QT_C_API_H */
