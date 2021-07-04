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

#ifndef YAFARAY_GUI_WX_MAIN_WINDOW_H
#define YAFARAY_GUI_WX_MAIN_WINDOW_H

#include "common/yafaray_gui_common.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

BEGIN_YAFARAY_GUI

class WxApp final : public wxApp
{
	public:
		bool OnInit() override;
};

class WxFrame final : public wxFrame
{
	public:
		WxFrame();
	private:
		enum ButtonId : int { Test, };
		void onTest(wxCommandEvent& event);
		void onExit(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);
};

END_YAFARAY_GUI

#endif //YAFARAY_GUI_WX_MAIN_WINDOW_H
