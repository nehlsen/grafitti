cmake_minimum_required(VERSION 3.15)
project(Grafitti)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(qmqtt_SHARED OFF)
add_subdirectory(lib/qmqtt)

add_executable(Grafitti
#        mainwindow.ui
        MainWindow.cpp
        main.cpp
#        resources.qrc
        )

target_link_libraries(Grafitti Qt5::Widgets qmqtt)
