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

#include "gui/main_window.h"
#include "gui/renderwidget.h"
#include "gui/events.h"
#include "gui/animworking.h"
#include "gui/worker.h"
#include <yafaray_c_api.h>
#include <yafaray_xml_c_api.h>

// Embedded Resources:
// Images
#include "resource/toolbar_z_buffer_icon.h"
#include "resource/toolbar_alpha_icon.h"
#include "resource/toolbar_cancel_icon.h"
#include "resource/toolbar_save_as_icon.h"
#include "resource/toolbar_render_icon.h"
#include "resource/toolbar_show_alpha_icon.h"
#include "resource/toolbar_colorbuffer_icon.h"
#include "resource/toolbar_drawparams_icon.h"
#include "resource/toolbar_savedepth_icon.h"
#include "resource/toolbar_zoomin_icon.h"
#include "resource/toolbar_zoomout_icon.h"
#include "resource/toolbar_quit_icon.h"
#include "resource/yafarayicon.h"

#include <QSettings>
#include <QAction>
#include <QApplication>
#include <QGridLayout>
#include <QMenuBar>
#include <QProgressBar>
#include <QPushButton>
#include <QToolBar>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>
// GUI Font
#if !defined(__APPLE__) && defined(YAFARAY_GUI_QT_EMBEDDED_FONT)
#include <QFontDatabase>
#include "resource/guifont.h"
#endif

BEGIN_YAFARAY_GUI_QT

MainWindow::MainWindow(yafaray_Interface_t *yafaray_interface, int width, int height, int border_start_x, int border_start_y, bool close_after_finish) : QMainWindow(), yafaray_interface_(yafaray_interface), width_(width), height_(height), border_start_x_(border_start_x), border_start_y_(border_start_y), auto_close_(close_after_finish)
{
	yafaray_setLoggingCallback(yafaray_interface_, MainWindow::loggerCallback, static_cast<void *>(&log_));

	QCoreApplication::setOrganizationName("YafaRay Team");
	QCoreApplication::setOrganizationDomain("yafaray.org");
	QCoreApplication::setApplicationName("LibYafaRay-Gui-Qt");

	QSettings set;
	ask_unsaved_ = set.value("qtGui/askSave", true).toBool();

#if !defined(__APPLE__) && defined(YAFARAY_GUI_QT_EMBEDDED_FONT)
	int fId = QFontDatabase::addApplicationFontFromData(QByteArray((const char *)guifont_global, guifont_size_global));
	QStringList fam = QFontDatabase::applicationFontFamilies(fId);
	QFont gFont = QFont(fam[0]);
	gFont.setPointSize(8);
	QApplication::setFont(gFont);
#else
#if defined(__APPLE__)
	QFont gFont = QApplication::font();
	gFont.setPointSize(13);
	QApplication::setFont(gFont);
#endif
#endif

	setup();

	QPixmap yaf_icon;
	yaf_icon.loadFromData(yafarayicon_global, yafarayicon_size_global);
	setWindowIcon(QIcon(yaf_icon));

#if defined(__APPLE__)
	m_ui->menubar->setNativeMenuBar(false); //Otherwise the menus don't appear in MacOS for some weird reason
	m_ui->toolBar->close(); //FIXME: I was unable to make the icons in the tool bar to show in MacOS, really weird... so for now we just hide the toolbar entirely in Mac
#endif

	render_saved_ = false;
	action_ask_save_->setChecked(ask_unsaved_);

	render_widget_ = std::unique_ptr<RenderWidget>(new RenderWidget(scroll_area_));
	worker_ = std::unique_ptr<Worker>(new Worker(yafaray_interface_, this));
	// animation widget
	anim_working_ = std::unique_ptr<AnimWorking>(new AnimWorking(scroll_area_));
	anim_working_->resize(200, 87);
	this->move(20, 20);
	scroll_area_->setWidgetResizable(false);
	scroll_area_->resize(width, height);
	scroll_area_->setWidget(render_widget_.get());
	QPalette palette = scroll_area_->viewport()->palette();
	palette.setColor(QPalette::Window, Qt::black);
	scroll_area_->viewport()->setPalette(palette);
	connect(worker_.get(), SIGNAL(finished()), this, SLOT(slotFinished()));

	// move the animwidget over the render area
	QRect r = anim_working_->rect();
	r.moveCenter(scroll_area_->rect().center());
	anim_working_->move(r.topLeft());

	// offset when using border rendering
	render_widget_->setRenderBorderStart(QPoint(border_start_x, border_start_y));
	// filter the resize events of the render area to center the animation widget
	scroll_area_->installEventFilter(this);
}

MainWindow::~MainWindow()
{
	yafaray_setLoggingCallback(yafaray_interface_, nullptr, nullptr);
}


void MainWindow::setup()
{
	setupActions();
	auto menu_bar = setupMenuBar();
	auto tool_bar = setupToolBar();
	auto central_widget = new QWidget();

	cancel_button_ = new QPushButton(central_widget);
	cancel_button_->setText("Cancel");
	QAbstractButton::connect(cancel_button_, SIGNAL(clicked()), this, SLOT(slotCancel()));

	label_ = setupLabel(central_widget);
	progress_bar_ = setupProgressBar(central_widget);
	scroll_area_ = setupRenderArea(central_widget);

	auto layout = new QGridLayout(central_widget);
	layout->setSpacing(2);
	layout->setContentsMargins(2, 2, 2, 2);
	layout->addWidget(scroll_area_, 0, 0, 1, 2);
	layout->addWidget(progress_bar_, 1, 0, 1, 1);
	layout->addWidget(cancel_button_, 1, 1, 1, 1);
	layout->addWidget(label_, 2, 0, 1, 2);

	setWindowTitle("YafaRay's Rendering Output");
	setCentralWidget(central_widget);
	setMenuBar(menu_bar);
	addToolBar(Qt::TopToolBarArea, tool_bar);

	setButtonsIcons();
}

void MainWindow::setupActions()
{
	action_quit_ = new QAction(this);
	action_quit_->setText("Quit");
	action_quit_->setToolTip("Quit YafaRay");
	action_quit_->setShortcut(QKeySequence("Ctrl+Q"));
	QAbstractButton::connect(action_quit_, SIGNAL(triggered(bool)), this, SLOT(close()));

	action_open_ = new QAction(this);
	action_open_->setText("Open");
	action_open_->setToolTip("Open a YafaRay XML file");
	action_open_->setShortcut(QKeySequence("Ctrl+O"));
	QAbstractButton::connect(action_open_, SIGNAL(triggered(bool)), this, SLOT(slotOpen()));

	action_save_as_ = new QAction(this);
	action_save_as_->setText("Save As...");
	action_save_as_->setToolTip("Save the render");
	action_save_as_->setShortcut(QKeySequence("Ctrl+S"));
	QAbstractButton::connect(action_save_as_, SIGNAL(triggered(bool)), this, SLOT(slotSaveAs()));

	action_zoom_in_ = new QAction(this);
	action_zoom_in_->setText("Zoom In");
	action_zoom_in_->setShortcut(QKeySequence("+"));
	QAbstractButton::connect(action_zoom_in_, SIGNAL(triggered(bool)), this, SLOT(zoomIn()));

	action_zoom_out_ = new QAction(this);
	action_zoom_out_->setText("Zoom Out");
	action_zoom_out_->setShortcut(QKeySequence("-"));
	QAbstractButton::connect(action_zoom_out_, SIGNAL(triggered(bool)), this, SLOT(zoomOut()));

	action_render_ = new QAction(this);
	action_render_->setText("Render");
	action_render_->setToolTip("Render the loaded scene");
	action_render_->setShortcut(QKeySequence("Ctrl+R"));
	QAbstractButton::connect(action_render_, SIGNAL(triggered(bool)), this, SLOT(slotRender()));

	action_cancel_ = new QAction(this);
	action_cancel_->setText("Cancel");
	action_cancel_->setToolTip("Cancel current rendering process");
	action_cancel_->setShortcut(QKeySequence("Ctrl+Shift+C"));
	QAbstractButton::connect(action_cancel_, SIGNAL(triggered(bool)), this, SLOT(slotCancel()));

	action_ask_save_ = new QAction(this);
	action_ask_save_->setCheckable(true);
	action_ask_save_->setText("Ask to save before closing");
	action_ask_save_->setToolTip("Enable/disable ask before closing dialog");
	QAbstractButton::connect(action_ask_save_, SIGNAL(triggered(bool)), this, SLOT(setAskSave(bool)));
}

QMenuBar *MainWindow::setupMenuBar()
{
	auto menu_bar = new QMenuBar(this);

	auto menu_file = new QMenu(menu_bar);
	menu_file->setTitle("File");
#ifdef YAFARAY_GUI_QT_WITH_XML
	menu_file->addAction(action_open_);
#endif
	menu_file->addAction(action_save_as_);
	menu_file->addSeparator();
	menu_file->addAction(action_quit_);

	auto menu_image = new QMenu(menu_bar);
	menu_image->setTitle("Image");
	menu_image->addAction(action_zoom_in_);
	menu_image->addAction(action_zoom_out_);
	menu_image->addSeparator();

	auto menu_render_options = new QMenu(menu_bar);
	menu_render_options->setTitle("Render");
	menu_render_options->addAction(action_render_);
	menu_render_options->addAction(action_cancel_);
	menu_render_options->addSeparator();
	menu_render_options->addSeparator();

	auto menu_options = new QMenu(menu_bar);
	menu_options->setTitle("Options");
	menu_options->addAction(action_ask_save_);

	menu_bar->addAction(menu_file->menuAction());
	menu_bar->addAction(menu_image->menuAction());
	menu_bar->addAction(menu_render_options->menuAction());
	menu_bar->addAction(menu_options->menuAction());

	return menu_bar;
}

QToolBar *MainWindow::setupToolBar()
{
	auto tool_bar = new QToolBar();
	tool_bar->setFloatable(false);
#ifdef YAFARAY_GUI_QT_WITH_XML
	tool_bar->addAction(action_open_);
#endif
	tool_bar->addAction(action_save_as_);
	tool_bar->addAction(action_render_);
	tool_bar->addSeparator();
	tool_bar->addAction(action_zoom_in_);
	tool_bar->addAction(action_zoom_out_);
	tool_bar->addSeparator();
	tool_bar->addAction(action_cancel_);
	return tool_bar;
}

QLabel *MainWindow::setupLabel(QWidget *widget_base)
{
	auto label = new QLabel(widget_base);
	label->setText("Status: idle");
	return label;
}

QProgressBar *MainWindow::setupProgressBar(QWidget *widget_base)
{
	auto progress_bar = new QProgressBar(widget_base);
	QFont font;
	font.setPointSize(8);
	progress_bar->setFont(font);
	progress_bar->setValue(0);
	progress_bar->setAlignment(Qt::AlignCenter);
	progress_bar->setTextVisible(true);
	progress_bar->setOrientation(Qt::Horizontal);
	return progress_bar;
}

QScrollArea *MainWindow::setupRenderArea(QWidget *widget_base)
{
	auto render_area = new QScrollArea(widget_base);
	auto scroll_area_widget_contents = new QWidget();
	render_area->setWidget(scroll_area_widget_contents);
	return render_area;
}

void MainWindow::setButtonsIcons()
{
	QPixmap cancel_icon;
	QPixmap open_icon;
	QPixmap save_as_icon;
	QPixmap render_icon;
	QPixmap zoom_in_icon;
	QPixmap zoom_out_icon;
	QPixmap quit_icon;

	cancel_icon.loadFromData(cancel_icon_global, cancel_icon_size_global);
	open_icon.loadFromData(alpha_icon_global, alpha_icon_size_global);
	save_as_icon.loadFromData(saveas_icon_global, saveas_icon_size_global);
	render_icon.loadFromData(render_icon_global, render_icon_size_global);
	zoom_in_icon.loadFromData(zoomin_icon_global, zoomin_icon_size_global);
	zoom_out_icon.loadFromData(zoomout_icon_global, zoomout_icon_size_global);
	quit_icon.loadFromData(quit_icon_global, quit_icon_size_global);

	action_cancel_->setIcon(QIcon(cancel_icon));
	action_open_->setIcon(QIcon(open_icon));
	action_save_as_->setIcon(QIcon(save_as_icon));
	action_render_->setIcon(QIcon(render_icon));
	action_zoom_in_->setIcon(QIcon(zoom_in_icon));
	action_zoom_out_->setIcon(QIcon(zoom_out_icon));
	action_quit_->setIcon(QIcon(quit_icon));
	cancel_button_->setIcon(QIcon(cancel_icon));
}

bool MainWindow::event(QEvent *event)
{
	if(event->type() == static_cast<QEvent::Type>(ProgressUpdate))
	{
		const auto p = static_cast<ProgressUpdateEvent *>(event);
		if(p->getMinSteps() >= 0) progress_bar_->setMinimum(p->getMinSteps());
		if(p->getMaxSteps() >= 0) progress_bar_->setMaximum(p->getMaxSteps());
		progress_bar_->setValue(p->getCurrentSteps());
		return true;
	}
	else if(event->type() == static_cast<QEvent::Type>(ProgressUpdateTag))
	{
		const auto p = static_cast<ProgressUpdateTagEvent *>(event);
		if(p->getTag().contains("Rendering")) anim_working_->hide();
		label_->setText(p->getTag());
		return true;
	}
	else return QMainWindow::event(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if(!closeUnsaved())
	{
		event->ignore();
	}
	else
	{
		slotCancel();
		if(render_cancelled_) QApplication::exit(1); //check if a render was stopped and exit with the appropriate code
		event->accept();
	}

}

void MainWindow::slotRender()
{
	action_render_->setVisible(false);
	action_zoom_in_->setEnabled(false);
	action_zoom_out_->setEnabled(false);
	cancel_button_->setVisible(true);
	action_cancel_->setVisible(true);

	progress_bar_->show();
	time_measure_.start();
	render_widget_->startRendering();
	render_saved_ = false;
	worker_->start();
}

void MainWindow::slotFinished()
{
	int render_time = time_measure_.elapsed();
	const float time_sec = static_cast<float>(render_time) / 1000.f;

	const int ms = render_time % 1000;
	render_time /= 1000;
	const int s = render_time % 60;
	render_time /= 60;
	const int m = render_time % 60;
	const int h = render_time / 60;

	QString time_str = "";
	const QChar fill = '0';
	QString suffix = "";

	if(h > 0)
	{
		time_str.append(QString("%1:").arg(h));
		suffix = "h.";
	}

	if(m > 0 || h > 0)
	{
		if(h > 0) time_str.append(QString("%1:").arg(m, 2, 10, fill));
		else time_str.append(QString("%1:").arg(m));
		if(suffix == "") suffix = "m.";
	}

	if(s < 10 && m == 0 && h == 0) time_str.append(QString("%1.%2").arg(s).arg(ms, 2, 10, fill));
	else time_str.append(QString("%1.%2").arg(s, 2, 10, fill).arg(ms, 2, 10, fill));

	if(suffix == "") suffix = "s.";
	time_str.append(QString(" %1").arg(suffix));

	QString rt;
	rt.append(QString("Render time: %1 [%2s.]").arg(time_str).arg(time_sec, 5));
	label_->setText(rt);
	yafaray_printInfo(yafaray_interface_, "Render completed!");

	render_widget_->finishRendering();
	update();
	action_render_->setVisible(true);
	action_zoom_in_->setEnabled(true);
	action_zoom_out_->setEnabled(true);
	cancel_button_->setVisible(false);
	action_cancel_->setVisible(false);
	if(auto_close_)
	{
		if(render_cancelled_) QApplication::exit(1);
		else QApplication::quit();
		return;
	}
	progress_bar_->hide();
	QApplication::alert(this);
}

void MainWindow::setAskSave(bool checked)
{
	QSettings set;
	ask_unsaved_ = checked;
	set.setValue("qtGui/askSave", ask_unsaved_);
}

void MainWindow::slotOpen()
{
	openDlg();
}

void MainWindow::slotSaveAs()
{
	saveDlg();
}

bool MainWindow::openDlg()
{
#ifdef YAFARAY_GUI_QT_WITH_XML
	const QString xml_file_path = QFileDialog::getOpenFileName(this, tr("Load YafaRay XML file"), last_path_, "*.xml");
	return yafaray_xml_ParseFile(yafaray_interface_, xml_file_path.toStdString().c_str());
#else
	yafaray_printError(yafaray_interface_, "libYafaRay-Gui-Qt is built without XML support, cannot open the file");
	return false;
#endif
}

bool MainWindow::saveDlg()
{
	if(last_path_.isNull()) last_path_ = QDir::currentPath();
	QFileDialog::getSaveFileName(this, tr("YafaRay Save Image"), last_path_, nullptr, nullptr);
	render_saved_ = false;
	return render_saved_;
}

bool MainWindow::closeUnsaved()
{
	if(!render_saved_ && !render_widget_->isRendering() && ask_unsaved_)
	{
		QMessageBox msg_box(QMessageBox::Question, "YafaRay Question", "The render hasn't been saved, if you close, it will be lost.", QMessageBox::NoButton, this);
		msg_box.setInformativeText("Do you want to save your render before closing?");
		QPushButton *discard = msg_box.addButton("Close without Saving", QMessageBox::DestructiveRole);
		const QPushButton *save = msg_box.addButton("Save", QMessageBox::AcceptRole);
		const QPushButton *cancel = msg_box.addButton("Cancel", QMessageBox::RejectRole);
		msg_box.setDefaultButton(discard);
		msg_box.exec();
		if(msg_box.clickedButton() == save) return saveDlg();
		else if(msg_box.clickedButton() == cancel) return false;
	}
	return true;
}

void MainWindow::slotCancel()
{
	yafaray_cancel(yafaray_interface_);
	worker_->wait();
	action_render_->setVisible(true);
	action_zoom_in_->setEnabled(true);
	action_zoom_out_->setEnabled(true);
	cancel_button_->setVisible(false);
	action_cancel_->setVisible(false);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Escape) close();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::Resize)
	{
		// move the anim widget over the render area
		QRect r = anim_working_->rect();
		r.moveCenter(scroll_area_->rect().center());
		anim_working_->move(r.topLeft());
		return true;
	}
	else return QMainWindow::eventFilter(obj, event);
}

void MainWindow::zoomOut() const
{
	render_widget_->zoomOut(QPoint(0, 0));
}

void MainWindow::zoomIn() const
{
	render_widget_->zoomIn(QPoint(0, 0));
}

void MainWindow::adjustWindow()
{
	const QRect available_geometry = QApplication::desktop()->availableGeometry();
	const int width = std::min(width_ + 10, available_geometry.width() - 60);
	const int height = std::min(height_ + 10, available_geometry.height() - 160);
	scroll_area_->setMaximumSize(width, height);
	scroll_area_->setMinimumSize(width, height);
	adjustSize();
	resize(minimumSize());
	scroll_area_->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
	scroll_area_->setMinimumSize(0, 0);
}



void MainWindow::putPixelCallback(const char *view_name, const char *layer_name, int x, int y, float r, float g, float b, float a, void *callback_user_data)
{
	const auto render_widget = static_cast<RenderWidget *>(callback_user_data);
	if(!render_widget) return;
	//RgbaFloat rgba(r, g, b, a);
	//output->images_collection_.setColor(view_name, layer_name, x, y, rgba);
	//if(strcmp(layer_name, "combined") == 0) render_widget->setPixel(x, y, QColor(r * 255.f, g * 255.f, b * 255.f, a * 255.f)); //FIXME VIEWS AND LAYERS

	if(strcmp(layer_name, "combined") == 0)
	{
		const QColor color_ldr {
				std::max(0, std::min(static_cast<int>(r * 255.f), 255)),
				std::max(0, std::min(static_cast<int>(g * 255.f), 255)),
				std::max(0, std::min(static_cast<int>(b * 255.f), 255)),
				std::max(0, std::min(static_cast<int>(a * 255.f), 255)),
		};
		QCoreApplication::postEvent(render_widget, new PutPixelEvent(QPoint(x, y), color_ldr)); //FIXME VIEWS AND LAYERS
	}
}

void MainWindow::flushAreaCallback(const char *view_name, int x_0, int y_0, int x_1, int y_1, void *callback_user_data)
{
	//printf("**** flushAreaCallback view_name='%s', x_0=%d, y_0=%d, x_1=%d, y_1=%d, callback_user_data=%p\n", view_name, x_0, y_0, x_1, y_1, callback_user_data);
	const auto render_widget = static_cast<RenderWidget *>(callback_user_data);
	if(render_widget) QCoreApplication::postEvent(render_widget, new GuiUpdateEvent(QRect(x_0, y_0, x_1 - x_0, y_1 - y_0)));
}

void MainWindow::flushCallback(const char *view_name, void *callback_user_data)
{
	//printf("**** flushCallback view_name='%s', callback_user_data=%p\n", view_name, callback_user_data);
	const auto render_widget = static_cast<RenderWidget *>(callback_user_data);
	if(render_widget) QCoreApplication::postEvent(render_widget, new GuiUpdateEvent(QRect(), true));
}

void MainWindow::highlightCallback(const char *view_name, int area_number, int x_0, int y_0, int x_1, int y_1, void *callback_user_data)
{
	//printf("**** highlightAreaCallback view_name='%s', area_number=%d, x_0=%d, y_0=%d, x_1=%d, y_1=%d, callback_user_data=%p\n", view_name, area_number, x_0, y_0, x_1, y_1, callback_user_data);
	const auto render_widget = static_cast<RenderWidget *>(callback_user_data);
	if(render_widget) QCoreApplication::postEvent(render_widget, new AreaHighlightEvent(area_number, QRect(x_0, y_0, x_1 - x_0, y_1 - y_0)));
}

void MainWindow::monitorCallback(int steps_total, int steps_done, const char *tag, void *callback_user_data)
{
	const auto main_window = static_cast<MainWindow *>(callback_user_data);
	if(!main_window) return;
	if(main_window->label_) QCoreApplication::postEvent(main_window, new ProgressUpdateTagEvent(tag));
	if(main_window->progress_bar_) QCoreApplication::postEvent(main_window, new ProgressUpdateEvent(steps_done, 0, steps_total));
}

void MainWindow::loggerCallback(yafaray_LogLevel_t log_level, long datetime, const char *time_of_day, const char *description, void *callback_user_data)
{
	auto log = static_cast<Log *>(callback_user_data);
	if(log) log->append({log_level, datetime, time_of_day, description});
}

END_YAFARAY_GUI_QT