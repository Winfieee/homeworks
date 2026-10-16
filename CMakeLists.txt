cmake_minimum_required(VERSION 3.20)
project(untitled1 C)

set(CMAKE_C_STANDARD 99)

# 1. Находим файлы во всем проекте
file(GLOB_RECURSE ALL_C_FILES "*.c")

# 2. Фильтруем список, полностью удаляя из него всё, что лежит в cmake-build-debug
foreach(FILE_PATH ${ALL_C_FILES})
    if(${FILE_PATH} MATCHES "cmake-build-debug")
        list(REMOVE_ITEM ALL_C_FILES ${FILE_PATH})
    endif()
endforeach()

# 3. Создаем кнопки запуска только для чистых файлов
foreach(SOURCE_FILE ${ALL_C_FILES})
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${SOURCE_FILE}
            Project/151077_project_v1.c)
endforeach()