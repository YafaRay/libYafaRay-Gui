add_executable(yafaray_gui_test01 test01_gui_qt.cc)
target_link_libraries(yafaray_gui_test01 LibYafaRay::libyafaray4 libyafaray4_gui)
target_include_directories(yafaray_gui_test01 PRIVATE ${PROJECT_BINARY_DIR}/include)
set_target_properties(yafaray_gui_test01 PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)

install(TARGETS yafaray_gui_test01
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		)
