cmake_minimum_required(VERSION 3.14)

project(hinotori-core LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_library(hinotori-core SHARED
        include/hinotori-core/hinotori-core_global.h
        include/hinotori-core/question.h
        include/hinotori-core/question.cpp
        include/hinotori-core/questionnaire.h
        include/hinotori-core/questionnaire.cpp
)

target_link_libraries(hinotori-core PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(hinotori-core PRIVATE HINOTORICORE_LIBRARY)
