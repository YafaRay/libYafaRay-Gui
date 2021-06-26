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
	auto menu_bar = setupMenuBar(window_base);
	auto tool_bar = setupToolBar(window_base);

	auto central_widget = new QWidget(window_base);

	cancel_button_ = new QPushButton(central_widget);
	cancel_button_->setText("Cancel");
	QAbstractButton::connect(cancel_button_, SIGNAL(clicked()), window_base, SLOT(slotCancel()));

	label_ = setupLabel(central_widget);
	progress_bar_ = setupProgressBar(central_widget);
	render_area_ = setupRenderArea(central_widget);

	auto yafaray_layout = new QGridLayout();
	yafaray_layout->setSpacing(2);
	yafaray_layout->setContentsMargins(2, 2, 2, 2);
	yafaray_layout->addWidget(render_area_, 0, 0, 1, 2);
	yafaray_layout->addWidget(progress_bar_, 1, 0, 1, 1);
	yafaray_layout->addWidget(cancel_button_, 1, 1, 1, 1);
	yafaray_layout->addWidget(label_, 2, 0, 1, 2);

	auto grid_layout = new QGridLayout(central_widget);
	grid_layout->setSpacing(0);
	grid_layout->setContentsMargins(0, 0, 0, 0);
	grid_layout->addLayout(yafaray_layout, 0, 0, 1, 1);

	window_base->setWindowTitle("YafaRay's Rendering Output");
	window_base->setCentralWidget(central_widget);
	window_base->setMenuBar(menu_bar);
	window_base->addToolBar(Qt::TopToolBarArea, tool_bar);

	setButtonsIcons();
	QMetaObject::connectSlotsByName(window_base);
}

void Ui::setupActions(QMainWindow *window_base)
{
	action_quit_ = new QAction(window_base);
	action_quit_->setText("Quit");
	action_quit_->setToolTip("Quit YafaRay");
	action_quit_->setShortcut(QKeySequence("Ctrl+Q"));
	QAbstractButton::connect(action_quit_, SIGNAL(triggered(bool)), window_base, SLOT(close()));

	action_save_as_ = new QAction(window_base);
	action_save_as_->setText("Save As...");
	action_save_as_->setToolTip("Save the render");
	action_save_as_->setShortcut(QKeySequence("Ctrl+S"));
	QAbstractButton::connect(action_save_as_, SIGNAL(triggered(bool)), window_base, SLOT(slotSaveAs()));

	action_zoom_in_ = new QAction(window_base);
	action_zoom_in_->setText("Zoom In");
	action_zoom_in_->setShortcut(QKeySequence("+"));
	QAbstractButton::connect(action_zoom_in_, SIGNAL(triggered(bool)), window_base, SLOT(zoomIn()));

	action_zoom_out_ = new QAction(window_base);
	action_zoom_out_->setText("Zoom Out");
	action_zoom_out_->setShortcut(QKeySequence("-"));
	QAbstractButton::connect(action_zoom_out_, SIGNAL(triggered(bool)), window_base, SLOT(zoomOut()));

	action_render_ = new QAction(window_base);
	action_render_->setText("Render");
	action_render_->setToolTip("Render the loaded scene");
	action_render_->setShortcut(QKeySequence("Ctrl+R"));
	QAbstractButton::connect(action_render_, SIGNAL(triggered(bool)), window_base, SLOT(slotRender()));

	action_cancel_ = new QAction(window_base);
	action_cancel_->setText("Cancel");
	action_cancel_->setToolTip("Cancel current rendering process");
	action_cancel_->setShortcut(QKeySequence("Ctrl+Shift+C"));
	QAbstractButton::connect(action_cancel_, SIGNAL(triggered(bool)), window_base, SLOT(slotCancel()));

	action_ask_save_ = new QAction(window_base);
	action_ask_save_->setCheckable(true);
	action_ask_save_->setText("Ask to save before closing");
	action_ask_save_->setToolTip("Enable/disable ask before closing dialog");
	QAbstractButton::connect(action_ask_save_, SIGNAL(triggered(bool)), window_base, SLOT(setAskSave(bool)));
}

QMenuBar *Ui::setupMenuBar(QMainWindow *window_base)
{
	auto menu_bar = new QMenuBar(window_base);

	auto menu_file = new QMenu(menu_bar);
	menu_file->setTitle("File");
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

QToolBar *Ui::setupToolBar(QMainWindow *window_base)
{
	auto tool_bar = new QToolBar(window_base);
	tool_bar->setMinimumSize(QSize(0, 0));
	tool_bar->setMaximumSize(QSize(16777215, 34));
	tool_bar->setMovable(false);
	tool_bar->setIconSize(QSize(26, 26));
	tool_bar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	tool_bar->setFloatable(false);
	tool_bar->setWindowTitle("toolBar");
	tool_bar->addAction(action_render_);
	tool_bar->addAction(action_cancel_);
	tool_bar->addSeparator();
	tool_bar->addAction(action_save_as_);
	tool_bar->addSeparator();
	tool_bar->addSeparator();
	tool_bar->addSeparator();
	tool_bar->addAction(action_quit_);
	return tool_bar;
}

QLabel *Ui::setupLabel(QWidget *widget_base)
{
	auto label = new QLabel(widget_base);
	label->setText("Rendering...");
	QSizePolicy size_policy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	size_policy.setHorizontalStretch(0);
	size_policy.setVerticalStretch(0);
	size_policy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
	label->setSizePolicy(size_policy);
	label->setTextFormat(Qt::AutoText);
	label->setMargin(0);
	label->setIndent(4);
	label->setTextInteractionFlags(Qt::NoTextInteraction);
	return label;
}

QProgressBar *Ui::setupProgressBar(QWidget *widget_base)
{
	auto progress_bar = new QProgressBar(widget_base);
	QSizePolicy size_policy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	size_policy.setHorizontalStretch(0);
	size_policy.setVerticalStretch(0);
	size_policy.setHeightForWidth(progress_bar->sizePolicy().hasHeightForWidth());
	progress_bar->setSizePolicy(size_policy);
	progress_bar->setMinimumSize(QSize(0, 13));
	progress_bar->setMaximumSize(QSize(16777215, 13));
	QFont font;
	font.setPointSize(8);
	progress_bar->setFont(font);
	progress_bar->setValue(0);
	progress_bar->setAlignment(Qt::AlignCenter);
	progress_bar->setTextVisible(true);
	progress_bar->setOrientation(Qt::Horizontal);
	return progress_bar;
}

QScrollArea *Ui::setupRenderArea(QWidget *widget_base)
{
	auto render_area = new QScrollArea(widget_base);
	render_area->setFrameShadow(QFrame::Plain);
	render_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	render_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	render_area->setWidgetResizable(true);
	render_area->setAlignment(Qt::AlignCenter);
	auto scroll_area_widget_contents = new QWidget();
	scroll_area_widget_contents->setObjectName("scrollAreaWidgetContents");
	scroll_area_widget_contents->setGeometry(QRect(0, 0, 1022, 491));
	render_area->setWidget(scroll_area_widget_contents);
	return render_area;
}

void Ui::setButtonsIcons()
{
	QPixmap cancel_icon;
	QPixmap save_as_icon;
	QPixmap render_icon;
	QPixmap zoom_in_icon;
	QPixmap zoom_out_icon;
	QPixmap quit_icon;

	cancel_icon.loadFromData(cancel_icon_global, cancel_icon_size_global);
	save_as_icon.loadFromData(saveas_icon_global, saveas_icon_size_global);
	render_icon.loadFromData(render_icon_global, render_icon_size_global);
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