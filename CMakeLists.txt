cmake_minimum_required(VERSION 3.2)

# ENV ist im .bashrc definiert
#   (Am Mac auf /Volumes/Daten/DevLocal/DevCPP/cmake )
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘

project(HelloESP32)

# Output bin, c++11 usw
include(Config)

# Password for this project
include(.config/passwords.cmake)

# The version number.
set (${PROJECT_NAME}_VERSION_MAJOR 0)
set (${PROJECT_NAME}_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
        "${PROJECT_SOURCE_DIR}/.config/config.h.in"
        "${PROJECT_SOURCE_DIR}/src/config.h"
        @ONLY
)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Precompiled headers                                             │
# └──────────────────────────────────────────────────────────────────┘

add_library(${PROJECT_NAME}_pch
        ${PROJECT_SOURCE_DIR}/src/stdafx.cpp ${PROJECT_SOURCE_DIR}/src/stdafx.h)

set_source_files_properties(${PROJECT_SOURCE_DIR}/src/stdafx.cpp
        PROPERTIES
        COMPILE_FLAGS "-include ${PROJECT_SOURCE_DIR}/src/stdafx.h")

# ┌──────────────────────────────────────────────────────────────────┐
# │  Google-Test (BasisProjekt: find_package(GTest)                  │
# └──────────────────────────────────────────────────────────────────┘

#find_package(GTest)
add_subdirectory(tests)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Platform.io                                                     │
# └──────────────────────────────────────────────────────────────────┘

include(CMakeListsPrivate.txt)

add_custom_target(
    ${PROJECT_NAME}_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    ${PROJECT_NAME}_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    ${PROJECT_NAME}_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

#add_custom_target(
#    PLATFORMIO_TEST ALL
#    COMMAND ${PLATFORMIO_CMD} -f -c clion test
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)
#
#add_custom_target(
#    PLATFORMIO_PROGRAM ALL
#    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target program
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)
#
#add_custom_target(
#    PLATFORMIO_UPLOADFS ALL
#    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)
#
#add_custom_target(
#    PLATFORMIO_UPDATE_ALL ALL
#    COMMAND ${PLATFORMIO_CMD} -f -c clion update
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)
#
#add_custom_target(
#    PLATFORMIO_REBUILD_PROJECT_INDEX ALL
#    COMMAND ${PLATFORMIO_CMD} -f -c clion init --ide clion
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)

include_directories(include)
include_directories(src)

set(SOURCE_FILES
        src/config.h
        
        src/main.cpp
        src/stdafx.cpp
        src/ota.cpp
#        src/main.cpp
#        src/gpio_task.cpp
#        src/ble.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#add_executable(${PROJECT_NAME} ${SRC_LIST})
