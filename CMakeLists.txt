cmake_minimum_required(VERSION 3.20)
project(untitled1 C)

set(CMAKE_C_STANDARD 99)

# CONFIGURE_DEPENDS: новые .c файлы подхватываются автоматически
file(GLOB_RECURSE ALL_C_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/*.c")

# Убираем ВСЕ папки сборки (cmake-build-debug, cmake-build-release, ...)
list(FILTER ALL_C_FILES EXCLUDE REGEX "/cmake-build-[^/]*/")

foreach(SOURCE_FILE ${ALL_C_FILES})
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)
    if(NOT TARGET ${TARGET_NAME})   # защита от двух файлов с одинаковым именем
        add_executable(${TARGET_NAME} ${SOURCE_FILE})
    endif()
endforeach()