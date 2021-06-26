/****************************************************************************
 *      mywindow.h: main window of the yafray UI
 *      This is part of the libYafaRay-Gui-Qt package
 *      Copyright (C) 2008 Gustavo Pichorim Boiko
 *      Copyright (C) 2009 Rodrigo Placencia Vazquez
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


#ifndef YAFARAY_MYWINDOW_H
#define YAFARAY_MYWINDOW_H

#include "common/yafaray_gui_qt_common.h"
#include "gui/animworking.h"
#include <QMainWindow>
#include <QTime>
#include <string>
#include <memory>

typedef struct yafaray_Interface yafaray_Interface_t;

BEGIN_YAFARAY_GUI_QT

class AnimWorking;
class QtOutput;
class RenderWidget;
class Worker;
class Ui;

class MainWindow final : public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow(yafaray_Interface_t *yafaray_interface, int resx, int resy, int b_start_x, int b_start_y, bool auto_save, bool close_after_finish);
		~MainWindow() override;
		bool event(QEvent *e) override;
		void adjustWindow();

	public slots:
		void slotRender();
		void slotFinished();
		void slotOpen();
		void slotSaveAs();
		void slotCancel();
		void setAskSave(bool checked);
		void zoomIn();
		void zoomOut();

	private:
		bool eventFilter(QObject *obj, QEvent *event) override;
		void keyPressEvent(QKeyEvent *event) override;
		void closeEvent(QCloseEvent *e) override;
		bool closeUnsaved();
		bool openDlg();
		bool saveDlg();

		std::unique_ptr<Ui> ui_;
		std::unique_ptr<RenderWidget> render_;
		std::unique_ptr<QtOutput> output_;
		std::unique_ptr<Worker> worker_;
		yafaray_Interface_t *yafaray_interface_;
		QString last_path_;
		int res_x_, res_y_, b_x_, b_y_;
		std::string file_name_;
		bool auto_close_;	// if true, rendering gets saved to fileName after finish and GUI gets closed (for animation)
		bool auto_save_;	// if true, rendering gets saved to fileName after finish but GUI stays opened
		QTime time_measure_;		// time measure for the render
		std::unique_ptr<AnimWorking> anim_;
		bool render_saved_;
		bool ask_unsaved_;
};

END_YAFARAY_GUI_QT

#endif
