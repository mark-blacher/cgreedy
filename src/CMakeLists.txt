cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(src_cgreedy LANGUAGES CXX)

if(APPLE)
    set(LIB_DIR "mac_")
elseif(UNIX)
    set(LIB_DIR "linux_")
elseif(WIN32)
    set(LIB_DIR "windows_")
else()
    message(FATAL_ERROR "Unsupported operating system!")
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(arm64)|(aarch64)")
    set(LIB_DIR "${LIB_DIR}arm64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    set(LIB_DIR "${LIB_DIR}x86")
else()
    message(FATAL_ERROR "Only arm64 and x86_64 supported")
endif ()

file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/cgreedy/${LIB_DIR}")

set(CGREEDY_LIB "cgreedy")
add_library(${CGREEDY_LIB} SHARED cpath.h wrapper.h wrapper.cpp)
target_include_directories(${CGREEDY_LIB} PUBLIC ./)

add_custom_command(TARGET ${CGREEDY_LIB} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${CGREEDY_LIB}>
        ${CMAKE_SOURCE_DIR}/cgreedy/${LIB_DIR}
)