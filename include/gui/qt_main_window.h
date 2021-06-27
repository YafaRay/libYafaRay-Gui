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

#ifndef LIBYAFARAY_GUI_QT_QT_MAIN_WINDOW_H
#define LIBYAFARAY_GUI_QT_QT_MAIN_WINDOW_H

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
class QTimer;

BEGIN_YAFARAY_GUI_QT

class AnimWorking;
class RenderWidget;
class Worker;

class QtMainWindow final : public QMainWindow
{
	Q_OBJECT

	public:
		QtMainWindow(yafaray_Interface_t *yafaray_interface, int resx, int resy, int b_start_x, int b_start_y, bool close_after_finish);
		~QtMainWindow() override;
		void adjustWindow();
		void setup(QMainWindow *window_base);

		QScrollArea *render_area_ = nullptr;
		QAction *action_ask_save_ = nullptr;
		QProgressBar *progress_bar_ = nullptr;
		QLabel *label_ = nullptr;

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
		bool event(QEvent *e) override;
		bool eventFilter(QObject *obj, QEvent *event) override;
		void keyPressEvent(QKeyEvent *event) override;
		void closeEvent(QCloseEvent *e) override;
		bool closeUnsaved();
		bool openDlg();
		bool saveDlg();
		void setButtonsIcons();
		void setupActions(QMainWindow *window_base);
		QMenuBar *setupMenuBar(QMainWindow *window_base);
		QToolBar *setupToolBar(QMainWindow *window_base);
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

		std::unique_ptr<RenderWidget> render_;
		std::unique_ptr<Worker> worker_;
		yafaray_Interface_t *yafaray_interface_ = nullptr;
		Output output_;
		QString last_path_;
		int res_x_ = 0, res_y_ = 0, b_x_ = 0, b_y_ = 0;
		bool auto_close_ = false; // if true, rendering gets saved to fileName after finish and GUI gets closed (for animation)
		QTime time_measure_; // time measure for the render
		QTimer *timer_ = nullptr;
		std::unique_ptr<AnimWorking> anim_;
		bool render_saved_ = false;
		bool ask_unsaved_ = false;
		bool render_cancelled_ = false;
};

END_YAFARAY_GUI_QT

#endif //LIBYAFARAY_GUI_QT_QT_MAIN_WINDOW_H
