cmake_minimum_required(VERSION 3.5)

project(ncm2mp3 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

# Find the Qt package
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Third-party libraries
add_library(cjson STATIC
    third_party/cjson/cJSON.c
    third_party/cjson/cJSON.h
)
target_include_directories(cjson PUBLIC third_party/cjson)

add_library(aes STATIC
    third_party/aes/aes.c
    third_party/aes/aes.h
)
target_include_directories(aes PUBLIC third_party/aes)

# Main executable
set(PROJECT_SOURCES
    src/main.cpp
    src/widget.cpp
    src/widget.h
    src/widget.ui
    src/model.c
    src/model.h
)


qt_add_executable(ncm2mp3
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(ncm2mp3 PRIVATE 
    Qt6::Widgets
    cjson
    aes
)

# Include directories
target_include_directories(ncm2mp3 PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

# Finalize the executable (for Qt6)
qt_finalize_executable(ncm2mp3)