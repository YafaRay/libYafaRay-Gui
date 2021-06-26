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

class Ui
{
	public:
		void setup(QMainWindow *WindowBase);

		QAction *actionQuit;
		QAction *actionSave_As;
		QAction *actionZoom_In;
		QAction *actionZoom_Out;
		QAction *actionRender;
		QAction *actionCancel;
		QAction *actionAskSave;
		QWidget *centralwidget;
		QGridLayout *gridLayout;
		QGridLayout *yafarayLayout;
		QScrollArea *renderArea;
		QWidget *scrollAreaWidgetContents;
		QProgressBar *progressbar;
		QPushButton *cancelButton;
		QLabel *yafLabel;
		QMenuBar *menubar;
		QMenu *menuFile;
		QMenu *menuImage;
		QMenu *menuRender_Options;
		QMenu *menuOptions;
		QToolBar *toolBar;

};

inline void Ui::setup(QMainWindow *WindowBase)
{
	WindowBase->setObjectName("WindowBase");
	WindowBase->resize(1028, 597);
	WindowBase->setWindowTitle("YafaRay's Rendering Output");

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

	centralwidget = new QWidget(WindowBase);
	centralwidget->setObjectName("centralwidget");

	gridLayout = new QGridLayout(centralwidget);
	gridLayout->setSpacing(0);
	gridLayout->setObjectName("gridLayout");
	gridLayout->setContentsMargins(0, 0, 0, 0);

	yafarayLayout = new QGridLayout();
	yafarayLayout->setSpacing(2);
	yafarayLayout->setObjectName("yafarayLayout");
	yafarayLayout->setContentsMargins(2, 2, 2, 2);

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
	yafarayLayout->addWidget(renderArea, 0, 0, 1, 2);

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

	yafarayLayout->addWidget(progressbar, 1, 0, 1, 1);

	cancelButton = new QPushButton(centralwidget);
	cancelButton->setObjectName("cancelButton");
	cancelButton->setText("Cancel");

	yafarayLayout->addWidget(cancelButton, 1, 1, 1, 1);

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

	yafarayLayout->addWidget(yafLabel, 2, 0, 1, 2);
	gridLayout->addLayout(yafarayLayout, 0, 0, 1, 1);
	WindowBase->setCentralWidget(centralwidget);

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

	WindowBase->setMenuBar(menubar);

	toolBar = new QToolBar(WindowBase);
	toolBar->setObjectName("toolBar");
	toolBar->setMinimumSize(QSize(0, 0));
	toolBar->setMaximumSize(QSize(16777215, 34));
	toolBar->setMovable(false);
	toolBar->setIconSize(QSize(26, 26));
	toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	toolBar->setFloatable(false);
	toolBar->setWindowTitle("toolBar");

	WindowBase->addToolBar(Qt::TopToolBarArea, toolBar);

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

	QMetaObject::connectSlotsByName(WindowBase);
}


END_YAFARAY_GUI_QT

#endif //LIBYAFARAY_GUI_QT_UI_H
