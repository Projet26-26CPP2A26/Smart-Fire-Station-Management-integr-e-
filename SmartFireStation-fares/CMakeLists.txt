cmake_minimum_required(VERSION 3.16)
project(SmartFireStation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

file(GLOB SRC_FILES CONFIGURE_DEPENDS *.cpp *.h *.ui)

add_executable(SmartFireStation ${SRC_FILES} resources.qrc)
target_link_libraries(SmartFireStation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)