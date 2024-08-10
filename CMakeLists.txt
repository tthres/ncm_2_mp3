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
find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent )

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

set(UI_FILES
    src/widget.ui
)

qt_wrap_ui(UI_HEADERS ${UI_FILES})

# Main executable
set(PROJECT_SOURCES
    src/main.cpp
    src/widget.cpp
    src/widget.h
    src/widget.ui
    src/converter/model.c
    src/converter/model.h
    src/converter/converter.cpp
    src/converter/converter.h
    src/delegate/item_delegate.cpp
    src/delegate/item_delegate.h
    src/model/file_model.cpp
    src/model/file_model.h
)


qt_add_executable(ncm2mp3
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${UI_HEADERS}
)

target_link_libraries(ncm2mp3 PRIVATE 
    Qt6::Widgets
    Qt6::Concurrent
    cjson
    aes
)

# Include directories
target_include_directories(ncm2mp3 PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Finalize the executable (for Qt6)
qt_finalize_executable(ncm2mp3)