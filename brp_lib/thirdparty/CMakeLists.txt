
if (MSVC)
    set(OPT_WARNINGS_AS_ERRORS "/WX")
else()
    set(OPT_WARNINGS_AS_ERRORS "-Werror")
endif()


#- HIDAPI static library -------------------------------------------------------
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_library(hidapi STATIC
            hidapi/windows/hid.c)
    target_link_libraries(hidapi
            setupapi)
elseif (APPLE)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(CF_LIBRARY CoreFoundation)
    add_library(hidapi STATIC
            hidapi/mac/hid.c)
    target_link_libraries(hidapi PRIVATE
            ${IOKIT_LIBRARY}
            ${CF_LIBRARY})
else()
    add_library(hidapi STATIC
            hidapi/linux/hid.c)
    target_link_libraries(hidapi
            udev)
endif()
target_include_directories(hidapi PUBLIC
        hidapi/hidapi)
target_compile_definitions(hidapi PUBLIC
        HID_API_NO_EXPORT_DEFINE)
target_compile_options(hidapi PRIVATE ${OPT_WARNINGS_AS_ERRORS})
if (MSVC)
    target_compile_options(hidapi PRIVATE "/wd4267")
endif()


#- RS232 static library --------------------------------------------------------
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_library(rs232 STATIC
            rs232/rs232-win.c)
else()
    add_library(rs232 STATIC
            rs232/rs232-linux.c)
endif()
target_include_directories(rs232 PUBLIC
        rs232)
target_compile_definitions(rs232 PRIVATE
        _CRT_SECURE_NO_WARNINGS=
        COM_MAXDEVICES=256)
target_compile_options(rs232 PRIVATE ${OPT_WARNINGS_AS_ERRORS})



#-------------------------------------------------------------------------------
set_target_properties(hidapi rs232 PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/brp_lib/thirdparty
    FOLDER "BRP Lib/Thirdparty Libs"
    POSITION_INDEPENDENT_CODE ON
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
