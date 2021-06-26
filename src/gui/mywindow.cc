/****************************************************************************
 *      mywindow.cc: the main window for the yafray GUI
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

#include "gui/mywindow.h"
#include "gui/renderwidget.h"
#include "gui/worker.h"
#include "gui/qtoutput.h"
#include "gui/ui.h"
#include "gui/events.h"
#include "resource/yafarayicon.h"
#include <yafaray_c_api.h>
#include <yafaray_xml_c_api.h>

// GUI Font
#if !defined(__APPLE__) && defined(YAFARAY_GUI_QT_EMBEDDED_FONT)
#include <QFontDatabase>
#include "resource/guifont.h"
#endif

// End of resources inclusion

// Standard Headers

// Qt Headers
#include <QFileDialog>
#include <QImageWriter>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QSettings>

BEGIN_YAFARAY_GUI_QT

MainWindow::MainWindow(yafaray_Interface_t *yafaray_interface, int resx, int resy, int b_start_x, int b_start_y, bool auto_save, bool close_after_finish)
	: QMainWindow(), yafaray_interface_(yafaray_interface), res_x_(resx), res_y_(resy), b_x_(b_start_x), b_y_(b_start_y), auto_save_(auto_save), auto_close_(close_after_finish)
{
	QCoreApplication::setOrganizationName("YafaRay Team");
	QCoreApplication::setOrganizationDomain("yafaray.org");
	QCoreApplication::setApplicationName("YafaRay Qt Gui");

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

	ui_ = std::unique_ptr<Ui>(new Ui());
	ui_->setup(this);

	QPixmap yaf_icon;
	yaf_icon.loadFromData(yafarayicon_global, yafarayicon_size_global);
	setWindowIcon(QIcon(yaf_icon));

#if defined(__APPLE__)
	m_ui->menubar->setNativeMenuBar(false); //Otherwise the menus don't appear in MacOS for some weird reason
	m_ui->toolBar->close(); //FIXME: I was unable to make the icons in the tool bar to show in MacOS, really weird... so for now we just hide the toolbar entirely in Mac
#endif

	render_saved_ = false;

	ui_->action_ask_save_->setChecked(ask_unsaved_);

/*	yafaray4::ParamMap *p = yafaray_interface_->getRenderParameters();
	p->getParam("z_channel", use_zbuf_);*/

	render_ = std::unique_ptr<RenderWidget>(new RenderWidget(ui_->render_area_));
//FIXME	output_ = std::unique_ptr<QtOutput>(new QtOutput(render_.get()));
	worker_ = std::unique_ptr<Worker>(new Worker(yafaray_interface_, this, output_.get()));

//FIXME	output_->setRenderSize(QSize(resx, resy));

	// animation widget
	anim_ = std::unique_ptr<AnimWorking>(new AnimWorking(ui_->render_area_));
	anim_->resize(200, 87);

	this->move(20, 20);

	ui_->render_area_->setWidgetResizable(false);
	ui_->render_area_->resize(resx, resy);
	ui_->render_area_->setWidget(render_.get());

	QPalette render_area_pal;
	render_area_pal = ui_->render_area_->viewport()->palette();
	render_area_pal.setColor(QPalette::Window, Qt::black);

	ui_->render_area_->viewport()->setPalette(render_area_pal);
	connect(worker_.get(), SIGNAL(finished()), this, SLOT(slotFinished()));

	// move the animwidget over the render area
	QRect r = anim_->rect();
	r.moveCenter(ui_->render_area_->rect().center());
	anim_->move(r.topLeft());

	// offset when using border rendering
	render_->setRenderBorderStart(QPoint(b_start_x, b_start_y));

	if(auto_save_)
	{
		this->setWindowTitle(this->windowTitle() + QString(" (") + QString(file_name_.c_str()) + QString(")"));
	}

	// filter the resize events of the render area to center the animation widget
	ui_->render_area_->installEventFilter(this);
}

MainWindow::~MainWindow() = default;

bool MainWindow::event(QEvent *e)
{
	if(e->type() == (QEvent::Type)ProgressUpdate)
	{
		auto *p = dynamic_cast<ProgressUpdateEvent *>(e);
		if(p->min() >= 0) ui_->progress_bar_->setMinimum(p->min());
		if(p->max() >= 0) ui_->progress_bar_->setMaximum(p->max());
		ui_->progress_bar_->setValue(p->progress());
		return true;
	}

	if(e->type() == (QEvent::Type)ProgressUpdateTag)
	{
		auto *p = dynamic_cast<ProgressUpdateTagEvent *>(e);
		if(p->tag().contains("Rendering")) anim_->hide();
		ui_->label_->setText(p->tag());
		return true;
	}

	return QMainWindow::event(e);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
	if(!closeUnsaved())
	{
		e->ignore();
	}
	else
	{
		slotCancel();

		//if(render_cancelled_) app_global->exit(1); //check if a render was stopped and exit with the appropiate code
		e->accept();
	}

}

void MainWindow::slotRender()
{
	ui_->slotEnableDisable(false);
	ui_->progress_bar_->show();
	time_measure_.start();
	ui_->label_->setText(tr("Rendering image..."));
	render_->startRendering();
	if(yafaray_interface_) yafaray_render(yafaray_interface_, nullptr, nullptr, YAFARAY_DISPLAY_CONSOLE_NORMAL);
	render_saved_ = false;
	worker_->start();
}

void MainWindow::slotFinished()
{
	QString rt;

	if(auto_save_)
	{
		yafaray_printInfo(yafaray_interface_, (" Image saved to " + file_name_).c_str());
		yafaray_paramsClearAll(yafaray_interface_);
		yafaray_paramsSetString(yafaray_interface_, "type", "image_output");
		yafaray_paramsSetString(yafaray_interface_, "image_path", "file_name_");
		yafaray_paramsSetInt(yafaray_interface_, "border_x", b_x_);
		yafaray_paramsSetInt(yafaray_interface_, "border_y", b_y_);
		//FIXME yafaray_createOutput(yafaray_interface_, "image_output");
		yafaray_paramsClearAll(yafaray_interface_);
		render_saved_ = true;

		rt = QString("Image Auto-saved. ");
/*		if(auto_close_)
		{
			if(render_cancelled_) app_global->exit(1);
			else app_global->quit();
			return;
		}*/
	}

	int render_time = time_measure_.elapsed();
	const float time_sec = static_cast<float>(render_time) / 1000.f;

	int ms = render_time % 1000;
	render_time = render_time / 1000;
	int s = render_time % 60;
	render_time = render_time / 60;
	int m = render_time % 60;
	int h = render_time / 60;

	QString time_str = "";
	QChar fill = '0';
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

	rt.append(QString("Render time: %1 [%2s.]").arg(time_str).arg(time_sec, 5));
	ui_->label_->setText(rt);
	yafaray_printInfo(yafaray_interface_, "Render completed!");

	render_->finishRendering();
	update();

	ui_->slotEnableDisable(true);

/*	if(auto_close_)
	{
		if(render_cancelled_) app_global->exit(1);
		else app_global->quit();
		return;
	}*/

	ui_->progress_bar_->hide();

	QApplication::alert(this);
}

void MainWindow::setAskSave(bool checked)
{
	QSettings set;
	ask_unsaved_ = checked;
	set.setValue("qtGui/askSave", ask_unsaved_);
}

/*void MainWindow::slotOpen()
{
	if (m_lastPath.isNull())
		m_lastPath = QDir::currentPath();
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Yafaray Scene"), m_lastPath, tr("Yafaray Scenes (*.xml)"));

	if (m_worker->isRunning())
		m_worker->terminate();
	delete m_worker;
	m_worker = new Worker(interf, this, m_output);

	m_lastPath = QDir(fileName).absolutePath();
	slotEnableDisable(true);
}*/

/*void MainWindow::slotSave()
{
	if (m_outputPath.isNull())
	{
		saveDlg();
	}
}*/

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
	return yafaray_xml_Parse(yafaray_interface_, xml_file_path.toStdString().c_str());
#else
	yafaray_printError(yafaray_interface_, "libYafaRay-Gui-Qt is built without XML support, cannot open the file");
	return false;
#endif
}

bool MainWindow::saveDlg()
{
	QString formats;
/* FIXME	std::vector<std::string> format_list = yafaray_interface_->listImageHandlers();
	std::vector<std::string> format_desc = yafaray_interface_->listImageHandlersFullName();

	std::sort(format_list.begin(), format_list.end());
	std::sort(format_desc.begin(), format_desc.end());

	for(size_t i = 0; i < format_list.size(); ++i)
	{
		formats += QString::fromStdString(format_desc[i]) + " (*." + QString::fromStdString(format_list[i]) + ")";
		if(i < format_list.size() - 1) formats += ";;";
	} */

	if(last_path_.isNull())
		last_path_ = QDir::currentPath();

	QString selected_filter;
	render_saved_ = false;
	QString file_name = QFileDialog::getSaveFileName(this, tr("YafaRay Save Image"), last_path_,
													 formats, &selected_filter);

	// "re"extract the actual file ending
	selected_filter.remove(0, selected_filter.indexOf("."));
	selected_filter.remove(selected_filter.indexOf(")"), 2);

	if(!file_name.endsWith(selected_filter, Qt::CaseInsensitive))
	{
		file_name.append(selected_filter.toLower());
	}

	selected_filter.remove(0, 1); // Remove the dot "."

	if(!file_name.isNull())
	{
		yafaray_paramsClearAll(yafaray_interface_);
		yafaray_paramsSetString(yafaray_interface_, "type", selected_filter.toStdString().c_str());
		yafaray_paramsSetInt(yafaray_interface_, "width", res_x_);
		yafaray_paramsSetInt(yafaray_interface_, "height", res_y_);
		last_path_ = QDir(file_name).absolutePath();

		yafaray_paramsSetString(yafaray_interface_, "type", "image_output");
		yafaray_paramsSetString(yafaray_interface_, "image_path", last_path_.toStdString().c_str());
		yafaray_paramsSetInt(yafaray_interface_, "border_x", b_x_);
		yafaray_paramsSetInt(yafaray_interface_, "border_y", b_y_);
		//FIXME yafaray_createOutput(yafaray_interface_, "image_output");
		yafaray_paramsClearAll(yafaray_interface_);
		//FIXME: interf->setDrawParams(useDrawParams);

		render_saved_ = true;

		QString savemesg;
		savemesg.append("Render ");
		savemesg.append("saved.");
		ui_->label_->setText(savemesg);
	}

	return render_saved_;
}

bool MainWindow::closeUnsaved()
{
	if(!render_saved_ && !render_->isRendering() && ask_unsaved_)
	{
		QMessageBox msg_box(QMessageBox::Question, "YafaRay Question", "The render hasn't been saved, if you close, it will be lost.",
							QMessageBox::NoButton, this);

		msg_box.setInformativeText("Do you want to save your render before closing?");
		QPushButton *discard = msg_box.addButton("Close without Saving", QMessageBox::DestructiveRole);
		QPushButton *save = msg_box.addButton("Save", QMessageBox::AcceptRole);
		QPushButton *cancel = msg_box.addButton("Cancel", QMessageBox::RejectRole);
		msg_box.setDefaultButton(discard);

		msg_box.exec();

		if(msg_box.clickedButton() == save) return saveDlg();
		else if(msg_box.clickedButton() == cancel) return false;
	}
	return true;
}

void MainWindow::slotCancel()
{
	// cancel the render and cleanup, especially wait for the worker to finish up
	// (otherwise the app will crash (if this is followed by a quit))
	yafaray_cancel(yafaray_interface_);
	worker_->wait();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Escape)	close();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::Resize)
	{
		// move the animwidget over the render area
		QRect r = anim_->rect();
		r.moveCenter(ui_->render_area_->rect().center());
		anim_->move(r.topLeft());
	}
	return QMainWindow::eventFilter(obj, event);
}

void MainWindow::zoomOut()
{
	render_->zoomOut(QPoint(0, 0));
}

void MainWindow::zoomIn()
{
	render_->zoomIn(QPoint(0, 0));
}

void MainWindow::adjustWindow()
{
	QRect scr_geom = QApplication::desktop()->availableGeometry();

	int w = std::min(res_x_ + 10, scr_geom.width() - 60);
	int h = std::min(res_y_ + 10, scr_geom.height() - 160);

	ui_->render_area_->setMaximumSize(w, h);
	ui_->render_area_->setMinimumSize(w, h);

	adjustSize();
	resize(minimumSize());

	ui_->render_area_->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
	ui_->render_area_->setMinimumSize(0, 0);
}

END_YAFARAY_GUI_QT