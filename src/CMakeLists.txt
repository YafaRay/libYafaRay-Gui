add_library(libyafaray4_gui)
set_target_properties(libyafaray4_gui PROPERTIES PREFIX "" VERSION 4.0.0 SOVERSION 4)
set_target_properties(libyafaray4_gui PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
set_target_properties(libyafaray4_gui PROPERTIES CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN ON)
target_include_directories(libyafaray4_gui PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include)
target_include_directories(libyafaray4_gui INTERFACE $<INSTALL_INTERFACE:include>)
target_link_libraries(libyafaray4_gui PRIVATE LibYafaRay::libyafaray4)

add_subdirectory(common)
add_subdirectory(public_api)

message_boolean("Building with XML loading support" YAFARAY_GUI_WITH_XML "yes" "no")
if(YAFARAY_GUI_WITH_XML)
	find_package(LibYafaRay_Xml 4.0.0 REQUIRED)
	list(APPEND YAFARAY_GUI_CUSTOM_DEFINITIONS "YAFARAY_GUI_WITH_XML")
	target_link_libraries(libyafaray4_gui PRIVATE LibYafaRay_Xml::libyafaray4_xml)
endif()

message_boolean("Building with QT GUI support" YAFARAY_GUI_WITH_QT "yes" "no")
if(YAFARAY_GUI_WITH_QT)
	find_package(Qt5 REQUIRED COMPONENTS Widgets)
	find_package(PNG 1.6 REQUIRED)
	list(APPEND YAFARAY_GUI_CUSTOM_DEFINITIONS "YAFARAY_GUI_WITH_QT")
	target_link_libraries(libyafaray4_gui PRIVATE Qt5::Widgets)
	set_target_properties(libyafaray4_gui PROPERTIES AUTOMOC ON)
	add_subdirectory(gui_qt)
endif()

message_boolean("Building with WxWidgets GUI support" YAFARAY_GUI_WITH_WXWIDGETS "yes" "no")
if(YAFARAY_GUI_WITH_WXWIDGETS)
	find_package(wxWidgets 3.0.0 REQUIRED COMPONENTS core base)
	include(${wxWidgets_USE_FILE}) #This is necessary to use wxWidgets with CMake properly
	list(APPEND YAFARAY_GUI_CUSTOM_DEFINITIONS "YAFARAY_GUI_WITH_WXWIDGETS")
	list(APPEND YAF_GUI_DEPS_INCLUDE_DIRS ${wxWidgets_INCLUDE_DIRS})
	target_link_libraries(libyafaray4_gui PRIVATE ${wxWidgets_LIBRARIES})
	add_subdirectory(gui_wx)
endif()

# Custom definitions
if(YAFARAY_GUI_EMBED_FONT)
	list(APPEND YAFARAY_GUI_CUSTOM_DEFINITIONS "YAFARAY_GUI_EMBEDDED_FONT")
endif()

target_include_directories(libyafaray4_gui SYSTEM BEFORE PRIVATE ${YAF_GUI_DEPS_INCLUDE_DIRS})

target_compile_definitions(libyafaray4_gui
		PRIVATE
		"${YAFARAY_GUI_CUSTOM_DEFINITIONS}"
		"YAFARAY_GUI_BUILD_TYPE=\"$<UPPER_CASE:$<CONFIG>>\""
		"YAFARAY_GUI_BUILD_FLAGS=\"${CMAKE_CXX_FLAGS} $<$<CONFIG:Debug>:${CMAKE_CXX_FLAGS_DEBUG}>$<$<CONFIG:Release>:${CMAKE_CXX_FLAGS_RELEASE}>$<$<CONFIG:RelWithDebInfo>:${CMAKE_CXX_FLAGS_RELWITHDEBINFO}>$<$<CONFIG:MinSizeRel>:${CMAKE_CXX_FLAGS_MINSIZEREL}>\"")

# Custom linker options
if(CMAKE_SYSTEM_NAME MATCHES "Linux" AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
	target_link_options(libyafaray4_gui PRIVATE
			"LINKER:SHELL:--no-undefined"
			"LINKER:SHELL:--version-script=${PROJECT_SOURCE_DIR}/include/public_api/yafaray_gui_c_api_symbols.map" # Custom symbols export and versioning map
			"$<$<CONFIG:RELEASE>:LINKER:SHELL:-s>" # Strip in release builds
			)
endif()

# Copy C API include files to binary directory for other targets to use
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include)
configure_file(${PROJECT_SOURCE_DIR}/include/public_api/yafaray_gui_c_api.h ${PROJECT_BINARY_DIR}/include/)

# Shared target used for generating export header for both the shared and static targets
include(GenerateExportHeader)
generate_export_header(libyafaray4_gui BASE_NAME yafaray_gui_c_api)
generate_export_header(libyafaray4_gui BASE_NAME yafaray_gui_c_api EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/yafaray_gui_c_api_export.h)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(${PROJECT_BINARY_DIR}/cmake/LibYafaRay_GuiConfigVersion.cmake
		COMPATIBILITY "AnyNewerVersion"
		)

install(TARGETS libyafaray4_gui
		EXPORT LibYafaRay_Gui
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		)

install(FILES
		${PROJECT_SOURCE_DIR}/include/public_api/yafaray_gui_c_api.h
		${PROJECT_BINARY_DIR}/include/yafaray_gui_c_api_export.h
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		)

install(EXPORT LibYafaRay_Gui
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LibYafaRay_Gui
		NAMESPACE LibYafaRay_Gui::
		FILE LibYafaRay_GuiConfig.cmake
		)

install(FILES
		${PROJECT_BINARY_DIR}/cmake/LibYafaRay_GuiConfigVersion.cmake
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LibYafaRay_Gui
		)