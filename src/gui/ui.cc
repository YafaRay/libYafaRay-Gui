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

void Ui::setup(QMainWindow *WindowBase)
{
	actionQuit = new QAction(WindowBase);
	actionQuit->setObjectName("actionQuit");
	actionQuit->setText("Quit");
	actionQuit->setToolTip("Quit YafaRay");
	actionQuit->setShortcut(QKeySequence("Ctrl+Q"));

	actionSave_As = new QAction(WindowBase);
	actionSave_As->setObjectName("actionSave_As");
	actionSave_As->setText("Save As...");
	actionSave_As->setToolTip("Save the render");
	actionSave_As->setShortcut(QKeySequence("Ctrl+S"));

	actionZoom_In = new QAction(WindowBase);
	actionZoom_In->setObjectName("actionZoom_In");
	actionZoom_In->setText("Zoom In");
	actionZoom_In->setShortcut(QKeySequence("+"));

	actionZoom_Out = new QAction(WindowBase);
	actionZoom_Out->setObjectName("actionZoom_Out");
	actionZoom_Out->setText("Zoom Out");
	actionZoom_Out->setShortcut(QKeySequence("-"));

	actionRender = new QAction(WindowBase);
	actionRender->setObjectName("actionRender");
	actionRender->setText("Render");
	actionRender->setToolTip("Render the loaded scene");
	actionRender->setShortcut(QKeySequence("Ctrl+R"));

	actionCancel = new QAction(WindowBase);
	actionCancel->setObjectName("actionCancel");
	actionCancel->setText("Cancel");
	actionCancel->setToolTip("Cancel current rendering process");
	actionCancel->setShortcut(QKeySequence("Ctrl+Shift+C"));

	actionAskSave = new QAction(WindowBase);
	actionAskSave->setObjectName("actionAskSave");
	actionAskSave->setCheckable(true);
	actionAskSave->setText("Ask to save before closing");
	actionAskSave->setToolTip("Enable/disable ask before closing dialog");

	menubar = new QMenuBar(WindowBase);
	menubar->setObjectName("menubar");
	menubar->setGeometry(QRect(0, 0, 1028, 22));

	menuFile = new QMenu(menubar);
	menuFile->setObjectName("menuFile");
	menuFile->setTitle("File");

	menuImage = new QMenu(menubar);
	menuImage->setObjectName("menuImage");
	menuImage->setTitle("Image");

	menuRender_Options = new QMenu(menubar);
	menuRender_Options->setObjectName("menuRender_Oprions");
	menuRender_Options->setTitle("Render");

	menuOptions = new QMenu(menubar);
	menuOptions->setObjectName("menuOptions");
	menuOptions->setTitle("Options");

	toolBar = new QToolBar(WindowBase);
	toolBar->setObjectName("toolBar");
	toolBar->setMinimumSize(QSize(0, 0));
	toolBar->setMaximumSize(QSize(16777215, 34));
	toolBar->setMovable(false);
	toolBar->setIconSize(QSize(26, 26));
	toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	toolBar->setFloatable(false);
	toolBar->setWindowTitle("toolBar");

	menubar->addAction(menuFile->menuAction());
	menubar->addAction(menuImage->menuAction());
	menubar->addAction(menuRender_Options->menuAction());
	menubar->addAction(menuOptions->menuAction());

	menuFile->addAction(actionSave_As);
	menuFile->addSeparator();
	menuFile->addAction(actionQuit);

	menuImage->addAction(actionZoom_In);
	menuImage->addAction(actionZoom_Out);
	menuImage->addSeparator();

	menuRender_Options->addAction(actionRender);
	menuRender_Options->addAction(actionCancel);
	menuRender_Options->addSeparator();
	menuRender_Options->addSeparator();
	menuOptions->addAction(actionAskSave);

	toolBar->addAction(actionRender);
	toolBar->addAction(actionCancel);
	toolBar->addSeparator();
	toolBar->addAction(actionSave_As);
	toolBar->addSeparator();
	toolBar->addSeparator();
	toolBar->addSeparator();
	toolBar->addAction(actionQuit);

	centralwidget = new QWidget(WindowBase);
	centralwidget->setObjectName("centralwidget");

	cancelButton = new QPushButton(centralwidget);
	cancelButton->setObjectName("cancelButton");
	cancelButton->setText("Cancel");

	yafLabel = new QLabel(centralwidget);
	yafLabel->setObjectName("yafLabel");
	yafLabel->setText("Rendering...");
	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(yafLabel->sizePolicy().hasHeightForWidth());
	yafLabel->setSizePolicy(sizePolicy1);
	yafLabel->setTextFormat(Qt::AutoText);
	yafLabel->setMargin(0);
	yafLabel->setIndent(4);
	yafLabel->setTextInteractionFlags(Qt::NoTextInteraction);

	progressbar = new QProgressBar(centralwidget);
	progressbar->setObjectName("progressbar");
	QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(progressbar->sizePolicy().hasHeightForWidth());
	progressbar->setSizePolicy(sizePolicy);
	progressbar->setMinimumSize(QSize(0, 13));
	progressbar->setMaximumSize(QSize(16777215, 13));
	QFont font;
	font.setPointSize(8);
	progressbar->setFont(font);
	progressbar->setValue(0);
	progressbar->setAlignment(Qt::AlignCenter);
	progressbar->setTextVisible(true);
	progressbar->setOrientation(Qt::Horizontal);

	renderArea = new QScrollArea(centralwidget);
	renderArea->setObjectName("renderArea");
	renderArea->setFrameShadow(QFrame::Plain);
	renderArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	renderArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	renderArea->setWidgetResizable(true);
	renderArea->setAlignment(Qt::AlignCenter);
	scrollAreaWidgetContents = new QWidget();
	scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
	scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1022, 491));
	renderArea->setWidget(scrollAreaWidgetContents);

	yafarayLayout = new QGridLayout();
	yafarayLayout->setSpacing(2);
	yafarayLayout->setObjectName("yafarayLayout");
	yafarayLayout->setContentsMargins(2, 2, 2, 2);
	yafarayLayout->addWidget(renderArea, 0, 0, 1, 2);
	yafarayLayout->addWidget(progressbar, 1, 0, 1, 1);
	yafarayLayout->addWidget(cancelButton, 1, 1, 1, 1);
	yafarayLayout->addWidget(yafLabel, 2, 0, 1, 2);

	gridLayout = new QGridLayout(centralwidget);
	gridLayout->setSpacing(0);
	gridLayout->setObjectName("gridLayout");
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->addLayout(yafarayLayout, 0, 0, 1, 1);

	WindowBase->setObjectName("WindowBase");
	WindowBase->resize(1028, 597);
	WindowBase->setWindowTitle("YafaRay's Rendering Output");
	WindowBase->setCentralWidget(centralwidget);
	WindowBase->setMenuBar(menubar);
	WindowBase->addToolBar(Qt::TopToolBarArea, toolBar);

	setToolBarIcons();
	connectActionSlots(WindowBase);

	QMetaObject::connectSlotsByName(WindowBase);
}

void Ui::setToolBarIcons()
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

	actionCancel->setIcon(QIcon(cancel_icon));
	actionSave_As->setIcon(QIcon(save_as_icon));
	actionRender->setIcon(QIcon(render_icon));
	actionZoom_In->setIcon(QIcon(zoom_in_icon));
	actionZoom_Out->setIcon(QIcon(zoom_out_icon));
	actionQuit->setIcon(QIcon(quit_icon));
	cancelButton->setIcon(QIcon(cancel_icon));
}

void Ui::connectActionSlots(QMainWindow *WindowBase)
{
	QAbstractButton::connect(actionRender, SIGNAL(triggered(bool)), WindowBase, SLOT(slotRender()));
	QAbstractButton::connect(actionCancel, SIGNAL(triggered(bool)), WindowBase, SLOT(slotCancel()));
	QAbstractButton::connect(actionSave_As, SIGNAL(triggered(bool)), WindowBase, SLOT(slotSaveAs()));
	QAbstractButton::connect(actionQuit, SIGNAL(triggered(bool)), WindowBase, SLOT(close()));
	QAbstractButton::connect(actionZoom_In, SIGNAL(triggered(bool)), WindowBase, SLOT(zoomIn()));
	QAbstractButton::connect(actionZoom_Out, SIGNAL(triggered(bool)), WindowBase, SLOT(zoomOut()));
	QAbstractButton::connect(actionAskSave, SIGNAL(triggered(bool)), WindowBase, SLOT(setAskSave(bool)));
	QAbstractButton::connect(cancelButton, SIGNAL(clicked()), WindowBase, SLOT(slotCancel()));
}

void Ui::slotEnableDisable(bool enable)
{
	actionRender->setVisible(enable);
	cancelButton->setVisible(!enable);
	actionCancel->setVisible(!enable);
	actionZoom_In->setEnabled(enable);
	actionZoom_Out->setEnabled(enable);
}

END_YAFARAY_GUI_QT