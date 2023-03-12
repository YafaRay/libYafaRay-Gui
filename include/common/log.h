#pragma once
/****************************************************************************
 *      This is part of the libYafaRay-Gui package
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

#ifndef LIBYAFARAY_GUI_LOG_ENTRY_H
#define LIBYAFARAY_GUI_LOG_ENTRY_H

#include <yafaray_c_api.h>
#include <string>
#include <vector>

namespace yafaray_gui
{

class LogEntry final
{
	public:
		LogEntry(yafaray_LogLevel log_level, size_t datetime, const char *time_of_day, const char *description) : log_level_(log_level), datetime_(datetime), time_of_day_(time_of_day), description_(description) { }
		yafaray_LogLevel getLogLevel() const { return log_level_; }
		size_t getDateTime() const { return datetime_; }
		std::string getTimeOfDay() const { return time_of_day_; }
		std::string getDescription() const { return description_; }

	private:
		yafaray_LogLevel log_level_ = YAFARAY_LOG_LEVEL_MUTE;
		size_t datetime_ = 0;
		std::string time_of_day_;
		std::string description_;
};

class Log final
{
	public:
		void append(const LogEntry &log_entry) { data_.emplace_back(log_entry); }
		std::vector<LogEntry> getLog() const { return data_; }

	private:
		std::vector<LogEntry> data_;
};

} // namespace yafaray_gui

#endif //LIBYAFARAY_GUI_LOG_ENTRY_H
