cmake_minimum_required (VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
project (brp_lib C)


#- BRPlib library --------------------------------------------------------------
# Platform-specific source files
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(PLATFORM_SRC  src/platform_win.c brp_lib.rc)
    set(AES_SRC  src/aes_cng.c)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(PLATFORM_SRC  src/platform_posix.c)
    set(AES_SRC  src/aes_commoncrypto.c)
else ()
    set(PLATFORM_SRC  src/platform_posix.c)
    set(AES_SRC  src/aes_openssl.c)
endif()

add_library(brp_lib SHARED
        ${AES_SRC}
        src/brp_protocol.c
        src/commands.c
        src/composite_protocol.c
        src/frames.c
        src/ioiter.c
        src/security_protocol.c
        src/protocol.c
        src/usb_hid_protocol.c
        src/rs232_protocol.c
        src/monitor_protocol.c
        src/version.c
        src/mempool.c
        src/names.c
        ${PLATFORM_SRC})
target_include_directories(brp_lib PUBLIC
        inc)
target_include_directories(brp_lib PRIVATE
        ..)    # is needed to compile brp_lib even if release.h is not copied
target_compile_definitions(brp_lib PRIVATE
        _CRT_SECURE_NO_WARNINGS
        _WIN32_WINNT=0x0601  # Windows 7 SP1 minimum
        WINVER=0x0601        # Windows 7 SP1 minimum
)
target_link_libraries(brp_lib PRIVATE
        hidapi
        rs232)
set_target_properties(brp_lib PROPERTIES
        FOLDER "BRP Lib"
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Platform-specific crypto library linking
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(brp_lib PRIVATE bcrypt)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # CommonCrypto is part of the Security framework on macOS
    find_library(SECURITY_FRAMEWORK Security)
    if(NOT SECURITY_FRAMEWORK)
        message(FATAL_ERROR "Security framework not found (required for CommonCrypto)")
    endif()
    target_link_libraries(brp_lib PRIVATE ${SECURITY_FRAMEWORK})
else()
    # Linux: Link against system OpenSSL
    find_package(OpenSSL REQUIRED)
    if(NOT OPENSSL_FOUND)
        message(FATAL_ERROR "OpenSSL not found. Please install libssl-dev or openssl-devel")
    endif()
    target_link_libraries(brp_lib PRIVATE OpenSSL::Crypto)
    message(STATUS "Using OpenSSL version: ${OPENSSL_VERSION}")
endif()
if (MSVC)
    target_compile_options(brp_lib PRIVATE "/WX")
else()
    target_compile_options(brp_lib PRIVATE "-Werror")
endif()


add_subdirectory(thirdparty)