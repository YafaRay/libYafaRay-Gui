#****************************************************************************
#      This is part of the libYafaRay-Gui-Qt package
#
#      This library is free software; you can redistribute it and/or
#      modify it under the terms of the GNU Lesser General Public
#      License as published by the Free Software Foundation; either
#      version 2.1 of the License, or (at your option) any later version.
#
#      This library is distributed in the hope that it will be useful,
#      but WITHOUT ANY WARRANTY; without even the implied warranty of
#      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#      Lesser General Public License for more details.
#
#      You should have received a copy of the GNU Lesser General Public
#      License along with this library; if not, write to the Free Software
#      Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

target_sources(libyafaray4_gui_qt
	PRIVATE
		animworking.cc
		events.cc
		renderwidget.cc
		worker.cc
		qt_main_window.cc
		images_collection.cc
		output.cc
		#Adding directly all include files with classes containing "Q_OBJECT" for Qt MOC to generate proper code and linking virtual parent Qt classes correctly
		${PROJECT_SOURCE_DIR}/include/gui/animworking.h
		${PROJECT_SOURCE_DIR}/include/gui/renderwidget.h #For Qt MOC to generate proper code
		${PROJECT_SOURCE_DIR}/include/gui/worker.h #For Qt MOC to generate proper code
		${PROJECT_SOURCE_DIR}/include/gui/qt_main_window.h #For Qt MOC to generate proper code
)
