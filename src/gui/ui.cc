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

#include "gui/ui.h"
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

BEGIN_YAFARAY_GUI_QT

void Ui::setup(QMainWindow *window_base)
{
	setupActions(window_base);
	setupMenuBar(window_base);
	setupToolBar(window_base);

	central_widget_ = new QWidget(window_base);
	central_widget_->setObjectName("centralwidget");

	cancel_button_ = new QPushButton(central_widget_);
	cancel_button_->setObjectName("cancelButton");
	cancel_button_->setText("Cancel");
	QAbstractButton::connect(cancel_button_, SIGNAL(clicked()), window_base, SLOT(slotCancel()));

	setupLabel(window_base);
	setupProgressBar(window_base);
	setupRenderArea(window_base);

	yafaray_layout_ = new QGridLayout();
	yafaray_layout_->setSpacing(2);
	yafaray_layout_->setObjectName("yafarayLayout");
	yafaray_layout_->setContentsMargins(2, 2, 2, 2);
	yafaray_layout_->addWidget(render_area_, 0, 0, 1, 2);
	yafaray_layout_->addWidget(progress_bar_, 1, 0, 1, 1);
	yafaray_layout_->addWidget(cancel_button_, 1, 1, 1, 1);
	yafaray_layout_->addWidget(label_, 2, 0, 1, 2);

	grid_layout_ = new QGridLayout(central_widget_);
	grid_layout_->setSpacing(0);
	grid_layout_->setObjectName("gridLayout");
	grid_layout_->setContentsMargins(0, 0, 0, 0);
	grid_layout_->addLayout(yafaray_layout_, 0, 0, 1, 1);

	window_base->setObjectName("WindowBase");
	window_base->resize(1028, 597);
	window_base->setWindowTitle("YafaRay's Rendering Output");
	window_base->setCentralWidget(central_widget_);
	window_base->setMenuBar(menubar_);
	window_base->addToolBar(Qt::TopToolBarArea, tool_bar_);

	setButtonsIcons();
	QMetaObject::connectSlotsByName(window_base);
}

void Ui::setupActions(QMainWindow *window_base)
{
	action_quit_ = new QAction(window_base);
	action_quit_->setObjectName("actionQuit");
	action_quit_->setText("Quit");
	action_quit_->setToolTip("Quit YafaRay");
	action_quit_->setShortcut(QKeySequence("Ctrl+Q"));
	QAbstractButton::connect(action_quit_, SIGNAL(triggered(bool)), window_base, SLOT(close()));

	action_save_as_ = new QAction(window_base);
	action_save_as_->setObjectName("actionSave_As");
	action_save_as_->setText("Save As...");
	action_save_as_->setToolTip("Save the render");
	action_save_as_->setShortcut(QKeySequence("Ctrl+S"));
	QAbstractButton::connect(action_save_as_, SIGNAL(triggered(bool)), window_base, SLOT(slotSaveAs()));

	action_zoom_in_ = new QAction(window_base);
	action_zoom_in_->setObjectName("actionZoom_In");
	action_zoom_in_->setText("Zoom In");
	action_zoom_in_->setShortcut(QKeySequence("+"));
	QAbstractButton::connect(action_zoom_in_, SIGNAL(triggered(bool)), window_base, SLOT(zoomIn()));

	action_zoom_out_ = new QAction(window_base);
	action_zoom_out_->setObjectName("actionZoom_Out");
	action_zoom_out_->setText("Zoom Out");
	action_zoom_out_->setShortcut(QKeySequence("-"));
	QAbstractButton::connect(action_zoom_out_, SIGNAL(triggered(bool)), window_base, SLOT(zoomOut()));

	action_render_ = new QAction(window_base);
	action_render_->setObjectName("actionRender");
	action_render_->setText("Render");
	action_render_->setToolTip("Render the loaded scene");
	action_render_->setShortcut(QKeySequence("Ctrl+R"));
	QAbstractButton::connect(action_render_, SIGNAL(triggered(bool)), window_base, SLOT(slotRender()));

	action_cancel_ = new QAction(window_base);
	action_cancel_->setObjectName("actionCancel");
	action_cancel_->setText("Cancel");
	action_cancel_->setToolTip("Cancel current rendering process");
	action_cancel_->setShortcut(QKeySequence("Ctrl+Shift+C"));
	QAbstractButton::connect(action_cancel_, SIGNAL(triggered(bool)), window_base, SLOT(slotCancel()));

	action_ask_save_ = new QAction(window_base);
	action_ask_save_->setObjectName("actionAskSave");
	action_ask_save_->setCheckable(true);
	action_ask_save_->setText("Ask to save before closing");
	action_ask_save_->setToolTip("Enable/disable ask before closing dialog");
	QAbstractButton::connect(action_ask_save_, SIGNAL(triggered(bool)), window_base, SLOT(setAskSave(bool)));
}

void Ui::setupMenuBar(QMainWindow *window_base)
{
	menubar_ = new QMenuBar(window_base);
	menubar_->setObjectName("menubar");
	menubar_->setGeometry(QRect(0, 0, 1028, 22));

	menu_file_ = new QMenu(menubar_);
	menu_file_->setObjectName("menuFile");
	menu_file_->setTitle("File");
	menu_file_->addAction(action_save_as_);
	menu_file_->addSeparator();
	menu_file_->addAction(action_quit_);

	menu_image_ = new QMenu(menubar_);
	menu_image_->setObjectName("menuImage");
	menu_image_->setTitle("Image");
	menu_image_->addAction(action_zoom_in_);
	menu_image_->addAction(action_zoom_out_);
	menu_image_->addSeparator();

	menu_render_options_ = new QMenu(menubar_);
	menu_render_options_->setObjectName("menuRender_Oprions");
	menu_render_options_->setTitle("Render");
	menu_render_options_->addAction(action_render_);
	menu_render_options_->addAction(action_cancel_);
	menu_render_options_->addSeparator();
	menu_render_options_->addSeparator();

	menu_options_ = new QMenu(menubar_);
	menu_options_->setObjectName("menuOptions");
	menu_options_->setTitle("Options");
	menu_options_->addAction(action_ask_save_);

	menubar_->addAction(menu_file_->menuAction());
	menubar_->addAction(menu_image_->menuAction());
	menubar_->addAction(menu_render_options_->menuAction());
	menubar_->addAction(menu_options_->menuAction());
}

void Ui::setupToolBar(QMainWindow *window_base)
{
	tool_bar_ = new QToolBar(window_base);
	tool_bar_->setObjectName("toolBar");
	tool_bar_->setMinimumSize(QSize(0, 0));
	tool_bar_->setMaximumSize(QSize(16777215, 34));
	tool_bar_->setMovable(false);
	tool_bar_->setIconSize(QSize(26, 26));
	tool_bar_->setToolButtonStyle(Qt::ToolButtonIconOnly);
	tool_bar_->setFloatable(false);
	tool_bar_->setWindowTitle("toolBar");
	tool_bar_->addAction(action_render_);
	tool_bar_->addAction(action_cancel_);
	tool_bar_->addSeparator();
	tool_bar_->addAction(action_save_as_);
	tool_bar_->addSeparator();
	tool_bar_->addSeparator();
	tool_bar_->addSeparator();
	tool_bar_->addAction(action_quit_);
}

void Ui::setupLabel(QMainWindow *window_base)
{
	label_ = new QLabel(central_widget_);
	label_->setObjectName("yafLabel");
	label_->setText("Rendering...");
	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(label_->sizePolicy().hasHeightForWidth());
	label_->setSizePolicy(sizePolicy1);
	label_->setTextFormat(Qt::AutoText);
	label_->setMargin(0);
	label_->setIndent(4);
	label_->setTextInteractionFlags(Qt::NoTextInteraction);
}

void Ui::setupProgressBar(QMainWindow *window_base)
{
	progress_bar_ = new QProgressBar(central_widget_);
	progress_bar_->setObjectName("progressbar");
	QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(progress_bar_->sizePolicy().hasHeightForWidth());
	progress_bar_->setSizePolicy(sizePolicy);
	progress_bar_->setMinimumSize(QSize(0, 13));
	progress_bar_->setMaximumSize(QSize(16777215, 13));
	QFont font;
	font.setPointSize(8);
	progress_bar_->setFont(font);
	progress_bar_->setValue(0);
	progress_bar_->setAlignment(Qt::AlignCenter);
	progress_bar_->setTextVisible(true);
	progress_bar_->setOrientation(Qt::Horizontal);
}

void Ui::setupRenderArea(QMainWindow *window_base)
{
	render_area_ = new QScrollArea(central_widget_);
	render_area_->setObjectName("renderArea");
	render_area_->setFrameShadow(QFrame::Plain);
	render_area_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	render_area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	render_area_->setWidgetResizable(true);
	render_area_->setAlignment(Qt::AlignCenter);
	scroll_area_widget_contents_ = new QWidget();
	scroll_area_widget_contents_->setObjectName("scrollAreaWidgetContents");
	scroll_area_widget_contents_->setGeometry(QRect(0, 0, 1022, 491));
	render_area_->setWidget(scroll_area_widget_contents_);
}

void Ui::setButtonsIcons()
{
	QPixmap zbuff_icon;
	QPixmap alpha_icon;
	QPixmap cancel_icon;
	QPixmap save_as_icon;
	QPixmap render_icon;
	QPixmap show_alpha_icon;
	QPixmap show_color_icon;
	QPixmap save_depth_icon;
	QPixmap draw_params_icon;
	QPixmap zoom_in_icon;
	QPixmap zoom_out_icon;
	QPixmap quit_icon;

	zbuff_icon.loadFromData(z_buf_icon_global, z_buf_icon_size_global);
	alpha_icon.loadFromData(alpha_icon_global, alpha_icon_size_global);
	cancel_icon.loadFromData(cancel_icon_global, cancel_icon_size_global);
	save_as_icon.loadFromData(saveas_icon_global, saveas_icon_size_global);
	render_icon.loadFromData(render_icon_global, render_icon_size_global);
	show_alpha_icon.loadFromData(show_alpha_icon_global, show_alpha_icon_size_global);
	show_color_icon.loadFromData(rgb_icon_global, rgb_icon_size_global);
	save_depth_icon.loadFromData(save_z_buf_icon_global, save_z_buf_icon_size_global);
	draw_params_icon.loadFromData(drawparams_icon_global, drawparams_icon_size_global);
	zoom_in_icon.loadFromData(zoomin_icon_global, zoomin_icon_size_global);
	zoom_out_icon.loadFromData(zoomout_icon_global, zoomout_icon_size_global);
	quit_icon.loadFromData(quit_icon_global, quit_icon_size_global);

	action_cancel_->setIcon(QIcon(cancel_icon));
	action_save_as_->setIcon(QIcon(save_as_icon));
	action_render_->setIcon(QIcon(render_icon));
	action_zoom_in_->setIcon(QIcon(zoom_in_icon));
	action_zoom_out_->setIcon(QIcon(zoom_out_icon));
	action_quit_->setIcon(QIcon(quit_icon));
	cancel_button_->setIcon(QIcon(cancel_icon));
}

void Ui::slotEnableDisable(bool enable)
{
	action_render_->setVisible(enable);
	cancel_button_->setVisible(!enable);
	action_cancel_->setVisible(!enable);
	action_zoom_in_->setEnabled(enable);
	action_zoom_out_->setEnabled(enable);
}

END_YAFARAY_GUI_QT