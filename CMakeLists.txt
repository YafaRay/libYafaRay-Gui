cmake_minimum_required(VERSION 3.18)

set(YAFARAY_GUI_VERSION_MAJOR 4)
set(YAFARAY_GUI_VERSION_MINOR 0)
set(YAFARAY_GUI_VERSION_PATCH 0)
set(YAFARAY_GUI_VERSION "${YAFARAY_GUI_VERSION_MAJOR}.${YAFARAY_GUI_VERSION_MINOR}.${YAFARAY_GUI_VERSION_PATCH}")
set(YAFARAY_GUI_VERSION_PRE_RELEASE "pre-alpha")
set(YAFARAY_GUI_VERSION_PRE_RELEASE_DESCRIPTION "PRE-ALPHA UNSTABLE VERSION, WORK IN PROGRESS.")
set(YAFARAY_GUI_VERSION_DESCRIPTION "libYafaRay-Gui is a library with a GUI interface to access libYafaRay. libYafaRay is a free open-source montecarlo raytracing engine released under the LGPL 2.1 license. Raytracing is a rendering technique for generating realistic images by tracing the path of light through a 3D scene. ${YAFARAY_GUI_VERSION_PRE_RELEASE_DESCRIPTION}")

project(libYafaRay-Gui
		VERSION "${YAFARAY_GUI_VERSION}"
		DESCRIPTION "${YAFARAY_GUI_VERSION_DESCRIPTION}"
		LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

option(BUILD_SHARED_LIBS "Build project libraries as shared libraries" ON)
option(YAFARAY_GUI_WITH_QT "Build with QT GUI support" ON)
option(YAFARAY_GUI_WITH_WXWIDGETS "Build with WxWidgets GUI support" ON)
option(YAFARAY_GUI_WITH_XML "Build with XML files loading support" ON)
option(YAFARAY_GUI_EMBED_FONT "Embed GUI Fonts" OFF)
option(YAFARAY_GUI_BUILD_TESTS "Build test libYafaRay-Gui client examples" ON)

include(message_boolean)
message_boolean("Building project libraries as" BUILD_SHARED_LIBS "shared" "static")

include(GNUInstallDirs)
if(APPLE)
	set(BASE_RPATH @loader_path)
else()
	set(BASE_RPATH $ORIGIN)
endif()

set(CMAKE_BUILD_WITH_INSTALL_RPATH YES)
file(RELATIVE_PATH RPATH_RELDIR
		${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
		${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
		)
set(CMAKE_INSTALL_RPATH ${BASE_RPATH} ${BASE_RPATH}/${RPATH_RELDIR})

find_package(LibYafaRay 4.0.0 REQUIRED)

add_subdirectory(src)

if(YAFARAY_GUI_BUILD_TESTS)
	add_subdirectory(tests)
endif()

add_subdirectory(cmake)
