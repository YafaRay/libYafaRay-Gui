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

#ifndef LIBYAFARAY_GUI_QT_MAIN_WINDOW_H
#define LIBYAFARAY_GUI_QT_MAIN_WINDOW_H

#include "common/yafaray_gui_qt_common.h"
#include "gui/output.h"
#include <QtWidgets/QMainWindow>
#include <QTime>
#include <memory>

typedef struct yafaray_Interface yafaray_Interface_t;
class QScrollArea;
class QProgressBar;
class QLabel;
class QPushButton;

BEGIN_YAFARAY_GUI_QT

class AnimWorking;
class RenderWidget;
class Worker;

class MainWindow final : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow(yafaray_Interface_t *yafaray_interface, int resx, int resy, int b_start_x, int b_start_y, bool close_after_finish);
		~MainWindow() override;
		void adjustWindow();
		void setup();

		std::unique_ptr<RenderWidget> render_;
		QScrollArea *render_area_ = nullptr;
		QAction *action_ask_save_ = nullptr;
		QProgressBar *progress_bar_ = nullptr;
		QLabel *label_ = nullptr;
		Output output_;

	public slots:
		void slotRender();
		void slotFinished();
		void slotOpen();
		void slotSaveAs();
		void slotCancel();
		void setAskSave(bool checked);
		void zoomIn() const;
		void zoomOut() const;

	private:
		bool event(QEvent *event) override;
		bool eventFilter(QObject *obj, QEvent *event) override;
		void keyPressEvent(QKeyEvent *event) override;
		void closeEvent(QCloseEvent *event) override;
		bool closeUnsaved();
		bool openDlg();
		bool saveDlg();
		void setButtonsIcons();
		void setupActions();
		QMenuBar *setupMenuBar();
		QToolBar *setupToolBar();
		static QLabel *setupLabel(QWidget *widget_base);
		static QProgressBar *setupProgressBar(QWidget *widget_base);
		static QScrollArea *setupRenderArea(QWidget *widget_base);

		QAction *action_quit_ = nullptr;
		QAction *action_open_ = nullptr;
		QAction *action_save_as_ = nullptr;
		QAction *action_zoom_in_ = nullptr;
		QAction *action_zoom_out_ = nullptr;
		QAction *action_render_ = nullptr;
		QAction *action_cancel_ = nullptr;
		QPushButton *cancel_button_ = nullptr;

		std::unique_ptr<Worker> worker_;
		yafaray_Interface_t *yafaray_interface_ = nullptr;
		QString last_path_;
		int res_x_ = 0, res_y_ = 0, b_x_ = 0, b_y_ = 0;
		bool auto_close_ = false; // if true, rendering gets saved to fileName after finish and GUI gets closed (for animation)
		QTime time_measure_; // time measure for the render
		std::unique_ptr<AnimWorking> anim_;
		bool render_saved_ = false;
		bool ask_unsaved_ = false;
		bool render_cancelled_ = false;
};

END_YAFARAY_GUI_QT

#endif //LIBYAFARAY_GUI_QT_MAIN_WINDOW_H
