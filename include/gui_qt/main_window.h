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

#ifndef YAFARAY_GUI_QT_MAIN_WINDOW_H
#define YAFARAY_GUI_QT_MAIN_WINDOW_H

#include "common/yafaray_gui_common.h"
#include "common/log.h"
#include <QMainWindow>
#include <QTime>
#include <memory>

typedef struct yafaray_Interface yafaray_Interface_t;
class QScrollArea;
class QProgressBar;
class QLabel;
class QPushButton;
class QTextEdit;

BEGIN_YAFARAY_GUI

class QtAnimWorking;
class QtRenderWidget;
class QtWorker;

class QtMainWindow final : public QMainWindow
{
	Q_OBJECT

	public:
		QtMainWindow(yafaray_Interface_t *yafaray_interface, int width, int height, int border_start_x, int border_start_y, bool close_after_finish);
		~QtMainWindow() override;
		void adjustWindow();
		void setup();
		static void notifyViewCallback(const char *view_name, void *callback_data);
		static void notifyLayerCallback(const char *internal_layer_name, const char *exported_layer_name, int width, int height, int exported_channels, void *callback_data);
		static void putPixelCallback(const char *view_name, const char *layer_name, int x, int y, float r, float g, float b, float a, void *callback_data);
		static void flushAreaCallback(const char *view_name, int area_id, int x_0, int y_0, int x_1, int y_1, void *callback_data);
		static void flushCallback(const char *view_name, void *callback_data);
		static void highlightAreaCallback(const char *view_name, int area_id, int x_0, int y_0, int x_1, int y_1, void *callback_data);
		static void highlightPixelCallback(const char *view_name, int x, int y, float r, float g, float b, float a, void *callback_data);
		static void monitorCallback(int steps_total, int steps_done, const char *tag, void *callback_data);
		static void loggerCallback(yafaray_LogLevel_t log_level, long datetime, const char *time_of_day, const char *description, void *callback_data);

		std::unique_ptr<QtRenderWidget> render_widget_;
		QTextEdit *log_widget_;
		QScrollArea *scroll_area_ = nullptr;
		QAction *action_ask_save_ = nullptr;

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
		QProgressBar *progress_bar_ = nullptr;
		QLabel *label_ = nullptr;

		std::unique_ptr<QtWorker> worker_;
		yafaray_Interface_t *yafaray_interface_ = nullptr;
		QString last_path_;
		int width_ = 0, height_ = 0, border_start_x_ = 0, border_start_y_ = 0;
		bool auto_close_ = false; // if true, rendering gets saved to fileName after finish and GUI gets closed (for animation)
		QTime time_measure_; // time measure for the render
		std::unique_ptr<QtAnimWorking> anim_working_;
		bool render_saved_ = false;
		bool ask_unsaved_ = false;
		bool render_cancelled_ = false;
		Log log_;
};

END_YAFARAY_GUI

#endif //YAFARAY_GUI_QT_MAIN_WINDOW_H
