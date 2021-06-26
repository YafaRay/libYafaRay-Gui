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

class Ui_WindowBase
{
	public:
		QAction *actionQuit;
		QAction *actionSave_As;
		QAction *actionZoom_In;
		QAction *actionZoom_Out;
		QAction *actionSaveAlpha;
		QAction *actionShowDepth;
		QAction *actionRender;
		QAction *actionCancel;
		QAction *actionShowAlpha;
		QAction *actionShowRGB;
		QAction *actionAskSave;
		QAction *actionSaveDepth;
		QAction *actionDrawParams;
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
		QMenu *menuRender_Oprions;
		QMenu *menuOptions;
		QToolBar *toolBar;

		void setupUi(QMainWindow *WindowBase)
		{
			if (WindowBase->objectName().isEmpty())
				WindowBase->setObjectName(QString::fromUtf8("WindowBase"));
			WindowBase->resize(1028, 597);
			actionQuit = new QAction(WindowBase);
			actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
			actionSave_As = new QAction(WindowBase);
			actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
			actionZoom_In = new QAction(WindowBase);
			actionZoom_In->setObjectName(QString::fromUtf8("actionZoom_In"));
			actionZoom_Out = new QAction(WindowBase);
			actionZoom_Out->setObjectName(QString::fromUtf8("actionZoom_Out"));
			actionSaveAlpha = new QAction(WindowBase);
			actionSaveAlpha->setObjectName(QString::fromUtf8("actionSaveAlpha"));
			actionSaveAlpha->setCheckable(true);
			actionShowDepth = new QAction(WindowBase);
			actionShowDepth->setObjectName(QString::fromUtf8("actionShowDepth"));
			actionShowDepth->setCheckable(true);
			actionRender = new QAction(WindowBase);
			actionRender->setObjectName(QString::fromUtf8("actionRender"));
			actionCancel = new QAction(WindowBase);
			actionCancel->setObjectName(QString::fromUtf8("actionCancel"));
			actionShowAlpha = new QAction(WindowBase);
			actionShowAlpha->setObjectName(QString::fromUtf8("actionShowAlpha"));
			actionShowAlpha->setCheckable(true);
			actionShowRGB = new QAction(WindowBase);
			actionShowRGB->setObjectName(QString::fromUtf8("actionShowRGB"));
			actionShowRGB->setCheckable(true);
			actionAskSave = new QAction(WindowBase);
			actionAskSave->setObjectName(QString::fromUtf8("actionAskSave"));
			actionAskSave->setCheckable(true);
			actionSaveDepth = new QAction(WindowBase);
			actionSaveDepth->setObjectName(QString::fromUtf8("actionSaveDepth"));
			actionSaveDepth->setCheckable(true);
			actionDrawParams = new QAction(WindowBase);
			actionDrawParams->setObjectName(QString::fromUtf8("actionDrawParams"));
			actionDrawParams->setCheckable(true);
			centralwidget = new QWidget(WindowBase);
			centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
			gridLayout = new QGridLayout(centralwidget);
			gridLayout->setSpacing(0);
			gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
			gridLayout->setContentsMargins(0, 0, 0, 0);
			yafarayLayout = new QGridLayout();
			yafarayLayout->setSpacing(2);
			yafarayLayout->setObjectName(QString::fromUtf8("yafarayLayout"));
			yafarayLayout->setContentsMargins(2, 2, 2, 2);
			renderArea = new QScrollArea(centralwidget);
			renderArea->setObjectName(QString::fromUtf8("renderArea"));
			renderArea->setFrameShadow(QFrame::Plain);
			renderArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
			renderArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
			renderArea->setWidgetResizable(true);
			renderArea->setAlignment(Qt::AlignCenter);
			scrollAreaWidgetContents = new QWidget();
			scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
			scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1022, 491));
			renderArea->setWidget(scrollAreaWidgetContents);

			yafarayLayout->addWidget(renderArea, 0, 0, 1, 2);

			progressbar = new QProgressBar(centralwidget);
			progressbar->setObjectName(QString::fromUtf8("progressbar"));
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
			cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

			yafarayLayout->addWidget(cancelButton, 1, 1, 1, 1);

			yafLabel = new QLabel(centralwidget);
			yafLabel->setObjectName(QString::fromUtf8("yafLabel"));
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
			menubar->setObjectName(QString::fromUtf8("menubar"));
			menubar->setGeometry(QRect(0, 0, 1028, 22));
			menuFile = new QMenu(menubar);
			menuFile->setObjectName(QString::fromUtf8("menuFile"));
			menuImage = new QMenu(menubar);
			menuImage->setObjectName(QString::fromUtf8("menuImage"));
			menuRender_Oprions = new QMenu(menubar);
			menuRender_Oprions->setObjectName(QString::fromUtf8("menuRender_Oprions"));
			menuOptions = new QMenu(menubar);
			menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
			WindowBase->setMenuBar(menubar);
			toolBar = new QToolBar(WindowBase);
			toolBar->setObjectName(QString::fromUtf8("toolBar"));
			toolBar->setMinimumSize(QSize(0, 0));
			toolBar->setMaximumSize(QSize(16777215, 34));
			toolBar->setMovable(false);
			toolBar->setIconSize(QSize(26, 26));
			toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
			toolBar->setFloatable(false);
			WindowBase->addToolBar(Qt::TopToolBarArea, toolBar);

			menubar->addAction(menuFile->menuAction());
			menubar->addAction(menuImage->menuAction());
			menubar->addAction(menuRender_Oprions->menuAction());
			menubar->addAction(menuOptions->menuAction());
			menuFile->addAction(actionSave_As);
			menuFile->addSeparator();
			menuFile->addAction(actionQuit);
			menuImage->addAction(actionZoom_In);
			menuImage->addAction(actionZoom_Out);
			menuImage->addSeparator();
			menuRender_Oprions->addAction(actionRender);
			menuRender_Oprions->addAction(actionCancel);
			menuRender_Oprions->addSeparator();
			menuRender_Oprions->addSeparator();
			menuOptions->addAction(actionAskSave);
			toolBar->addAction(actionRender);
			toolBar->addAction(actionCancel);
			toolBar->addSeparator();
			toolBar->addAction(actionSave_As);
			toolBar->addSeparator();
			toolBar->addSeparator();
			toolBar->addSeparator();
			toolBar->addAction(actionQuit);

			retranslateUi(WindowBase);

			QMetaObject::connectSlotsByName(WindowBase);
		} // setupUi

		void retranslateUi(QMainWindow *WindowBase)
		{
			WindowBase->setWindowTitle(QApplication::translate("WindowBase", "YafaRay's Rendering Output", nullptr));
			actionQuit->setText(QApplication::translate("WindowBase", "Quit", nullptr));
#ifndef QT_NO_TOOLTIP
			actionQuit->setToolTip(QApplication::translate("WindowBase", "Quit YafaRay", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
			actionQuit->setShortcut(QApplication::translate("WindowBase", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
			actionSave_As->setText(QApplication::translate("WindowBase", "Save As...", nullptr));
#ifndef QT_NO_TOOLTIP
			actionSave_As->setToolTip(QApplication::translate("WindowBase", "Save the render", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
			actionSave_As->setShortcut(QApplication::translate("WindowBase", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
			actionZoom_In->setText(QApplication::translate("WindowBase", "Zoom In", nullptr));
#ifndef QT_NO_SHORTCUT
			actionZoom_In->setShortcut(QApplication::translate("WindowBase", "+", nullptr));
#endif // QT_NO_SHORTCUT
			actionZoom_Out->setText(QApplication::translate("WindowBase", "Zoom Out", nullptr));
#ifndef QT_NO_SHORTCUT
			actionZoom_Out->setShortcut(QApplication::translate("WindowBase", "-", nullptr));
#endif // QT_NO_SHORTCUT
			actionSaveAlpha->setText(QApplication::translate("WindowBase", "Save with alpha channel", nullptr));
			actionSaveAlpha->setIconText(QApplication::translate("WindowBase", "Save with Alpha channel", nullptr));
#ifndef QT_NO_TOOLTIP
			actionSaveAlpha->setToolTip(QApplication::translate("WindowBase", "Enables saving the image with a transparency channel (RGBA)", nullptr));
#endif // QT_NO_TOOLTIP
			actionShowDepth->setText(QApplication::translate("WindowBase", "Show z-buffer channel", nullptr));
#ifndef QT_NO_TOOLTIP
			actionShowDepth->setToolTip(QApplication::translate("WindowBase", "Shows the z-buffer channel of the render", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
			actionShowDepth->setShortcut(QApplication::translate("WindowBase", "Z", nullptr));
#endif // QT_NO_SHORTCUT
			actionRender->setText(QApplication::translate("WindowBase", "Render", nullptr));
#ifndef QT_NO_TOOLTIP
			actionRender->setToolTip(QApplication::translate("WindowBase", "Render the loaded scene", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
			actionRender->setShortcut(QApplication::translate("WindowBase", "Ctrl+R", nullptr));
#endif // QT_NO_SHORTCUT
			actionCancel->setText(QApplication::translate("WindowBase", "Cancel", nullptr));
#ifndef QT_NO_TOOLTIP
			actionCancel->setToolTip(QApplication::translate("WindowBase", "Cancel current rendering process", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
			actionCancel->setShortcut(QApplication::translate("WindowBase", "Ctrl+Shift+C", nullptr));
#endif // QT_NO_SHORTCUT
			actionShowAlpha->setText(QApplication::translate("WindowBase", "Show alpha channel", nullptr));
#ifndef QT_NO_TOOLTIP
			actionShowAlpha->setToolTip(QApplication::translate("WindowBase", "Shows the alpha channel of the render", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
			actionShowAlpha->setShortcut(QApplication::translate("WindowBase", "A", nullptr));
#endif // QT_NO_SHORTCUT
			actionShowRGB->setText(QApplication::translate("WindowBase", "Show RGB buffer", nullptr));
#ifndef QT_NO_TOOLTIP
			actionShowRGB->setToolTip(QApplication::translate("WindowBase", "Shows the RGB channels of the render", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
			actionShowRGB->setShortcut(QApplication::translate("WindowBase", "R", nullptr));
#endif // QT_NO_SHORTCUT
			actionAskSave->setText(QApplication::translate("WindowBase", "Ask to save before closing", nullptr));
#ifndef QT_NO_TOOLTIP
			actionAskSave->setToolTip(QApplication::translate("WindowBase", "Enable/disable ask before closing dialog", nullptr));
#endif // QT_NO_TOOLTIP
			actionSaveDepth->setText(QApplication::translate("WindowBase", "Save with Z-Buffer", nullptr));
#ifndef QT_NO_TOOLTIP
			actionSaveDepth->setToolTip(QApplication::translate("WindowBase", "Save with Z-Buffer", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
			actionSaveDepth->setShortcut(QApplication::translate("WindowBase", "Alt+Shift+Z", nullptr));
#endif // QT_NO_SHORTCUT
			actionDrawParams->setText(QApplication::translate("WindowBase", "Add render parameters badge", nullptr));
#ifndef QT_NO_TOOLTIP
			actionDrawParams->setToolTip(QApplication::translate("WindowBase", "Add a badge with the parameters of the render", nullptr));
#endif // QT_NO_TOOLTIP
			cancelButton->setText(QApplication::translate("WindowBase", "Cancel", nullptr));
			yafLabel->setText(QApplication::translate("WindowBase", "Rendering...", nullptr));
			menuFile->setTitle(QApplication::translate("WindowBase", "File", nullptr));
			menuImage->setTitle(QApplication::translate("WindowBase", "Image", nullptr));
			menuRender_Oprions->setTitle(QApplication::translate("WindowBase", "Render", nullptr));
			menuOptions->setTitle(QApplication::translate("WindowBase", "Options", nullptr));
			toolBar->setWindowTitle(QApplication::translate("WindowBase", "toolBar", nullptr));
		} // retranslateUi

};

END_YAFARAY_GUI_QT

#endif //LIBYAFARAY_GUI_QT_UI_H
