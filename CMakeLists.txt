cmake_minimum_required(VERSION 3.20)
project(untitled1 C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE ALL_C_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/*.c")
list(FILTER ALL_C_FILES EXCLUDE REGEX "/cmake-build-[^/]*/")

foreach(SOURCE_FILE ${ALL_C_FILES})
    get_filename_component(RAW_NAME ${SOURCE_FILE} NAME_WE)
    # Заменяет пробелы, скобки и прочие спецсимволы на "_"
    string(MAKE_C_IDENTIFIER "${RAW_NAME}" TARGET_NAME)

    if(NOT TARGET ${TARGET_NAME})
        add_executable(${TARGET_NAME} ${SOURCE_FILE}
                cvicenie5/151077_2026_5_5.c)
    endif()
endforeach()