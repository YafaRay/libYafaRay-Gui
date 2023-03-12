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

#include "gui_wx/main_window.h"

namespace yafaray_gui
{

bool WxApp::OnInit()
{
	auto *frame = new WxFrame();
	frame->Show(true);
	return true;
}

WxFrame::WxFrame() : wxFrame(nullptr, wxID_ANY, "LibYafaRay-Gui")
{
	SetFont(wxFont(32, wxFONTFAMILY_SWISS,
				   wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	auto *menu_file = new wxMenu;
	menu_file->Append(ButtonId::Test, "&Test...\tCtrl-T", "Test menu entry");
	menu_file->AppendSeparator();
	menu_file->Append(wxID_EXIT);
	auto *menu_help = new wxMenu;
	menu_help->Append(wxID_ABOUT);
	auto *menu_bar = new wxMenuBar;
	menu_bar->Append(menu_file, "&File");
	menu_bar->Append(menu_help, "&Help");
	SetMenuBar(menu_bar);
	CreateStatusBar();
	SetStatusText("Status: idle");
	Bind(wxEVT_MENU, &WxFrame::onTest, this, ButtonId::Test);
	Bind(wxEVT_MENU, &WxFrame::onAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &WxFrame::onExit, this, wxID_EXIT);
}

void WxFrame::onExit(wxCommandEvent& event)
{
	Close(true);
}

void WxFrame::onAbout(wxCommandEvent& event)
{
	wxMessageBox("libYafaRay-Gui is a library with a GUI interface to access libYafaRay.\nToolkit used: WxWidgets.", "About libYafaRay-Gui", wxOK | wxICON_INFORMATION);
}

void WxFrame::onTest(wxCommandEvent& event)
{
	wxLogMessage("Test menu entry");
}

} // namespace yafaray_gui