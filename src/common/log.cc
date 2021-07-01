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

#include "common/log.h"

BEGIN_YAFARAY_GUI_QT

void Log::loggerCallback(yafaray_LogLevel_t log_level, long datetime, const char *time_of_day, const char *description, void *callback_user_data)
{
	auto log = static_cast<Log *>(callback_user_data);
	if(log) log->append({log_level, datetime, time_of_day, description});
}

END_YAFARAY_GUI_QT