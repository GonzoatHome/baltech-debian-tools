add_executable(baltech_id_engine_explorer
	id_engine_explorer.c
	reader_helpers.c)
target_link_libraries(baltech_id_engine_explorer PRIVATE baltech_api)
set_target_properties(baltech_id_engine_explorer PROPERTIES
	C_STANDARD 99
	C_STANDARD_REQUIRED ON
	BUILD_RPATH "$ORIGIN"
	INSTALL_RPATH "$ORIGIN"
	FOLDER "Tools")

add_executable(baltech_firmware_uploader
	firmware_uploader.c
	reader_helpers.c)
target_link_libraries(baltech_firmware_uploader PRIVATE baltech_api)
find_package(LibXml2 QUIET)
if(LibXml2_FOUND)
	target_compile_definitions(baltech_firmware_uploader PRIVATE BALTECH_HAVE_LIBXML2=1)
	target_link_libraries(baltech_firmware_uploader PRIVATE LibXml2::LibXml2)
else()
	message(STATUS "Legacy .bec uploads disabled; install libxml2 development headers to enable them.")
endif()
set_target_properties(baltech_firmware_uploader PROPERTIES
	C_STANDARD 99
	C_STANDARD_REQUIRED ON
	BUILD_RPATH "$ORIGIN"
	INSTALL_RPATH "$ORIGIN"
	FOLDER "Tools")

include(CheckLanguage)
check_language(CXX)
if(CMAKE_CXX_COMPILER)
	enable_language(CXX)
	find_package(Qt6 COMPONENTS Widgets Concurrent QUIET)
	if(TARGET Qt6::Widgets AND TARGET Qt6::Concurrent)
		add_executable(baltech_id_engine_explorer_gui id_engine_explorer_gui.cpp reader_select_dialog.cpp reader_helpers.c)
		target_link_libraries(baltech_id_engine_explorer_gui PRIVATE baltech_api Qt6::Widgets Qt6::Concurrent)
		set_target_properties(baltech_id_engine_explorer_gui PROPERTIES
			CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON BUILD_RPATH "$ORIGIN" INSTALL_RPATH "$ORIGIN" FOLDER "Tools")

		add_executable(baltech_firmware_uploader_gui firmware_uploader_gui.cpp reader_select_dialog.cpp reader_helpers.c)
		target_link_libraries(baltech_firmware_uploader_gui PRIVATE baltech_api Qt6::Widgets Qt6::Concurrent)
		set_target_properties(baltech_firmware_uploader_gui PROPERTIES
			CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON BUILD_RPATH "$ORIGIN" INSTALL_RPATH "$ORIGIN" FOLDER "Tools")
	else()
		message(STATUS "Qt6 Widgets not found; building CLI tools only. Install qt6-base-dev to enable desktop tools.")
	endif()
endif()