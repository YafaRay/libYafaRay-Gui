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

#ifndef LIBYAFARAY_GUI_QT_UI_H
#define LIBYAFARAY_GUI_QT_UI_H

#include "common/yafaray_gui_qt_common.h"
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

BEGIN_YAFARAY_GUI_QT

class Ui final
{
	public:
		void setup(QMainWindow *window_base);
		void slotEnableDisable(bool enable = true);

		QScrollArea *render_area_;
		QAction *action_ask_save_;
		QProgressBar *progress_bar_;
		QLabel *label_;

	private:
		void setButtonsIcons();
		void setupActions(QMainWindow *window_base);
		QMenuBar *setupMenuBar(QMainWindow *window_base);
		QToolBar *setupToolBar(QMainWindow *window_base);
		static QLabel *setupLabel(QWidget *widget_base);
		static QProgressBar *setupProgressBar(QWidget *widget_base);
		static QScrollArea *setupRenderArea(QWidget *widget_base);

		QAction *action_quit_;
		QAction *action_save_as_;
		QAction *action_zoom_in_;
		QAction *action_zoom_out_;
		QAction *action_render_;
		QAction *action_cancel_;
		QPushButton *cancel_button_;
};

END_YAFARAY_GUI_QT

#endif //LIBYAFARAY_GUI_QT_UI_H
