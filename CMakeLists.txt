cmake_minimum_required(VERSION 3.10)
project(TimeTracker VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

set(SOURCES
    src/main.cpp
    src/commands/Command.cpp
    src/controllers/TimeTrackerController.cpp
    src/models/Project.cpp
    src/models/Task.cpp
    src/models/TimeSession.cpp
    src/models/User.cpp
    src/observers/Observer.cpp
    src/strategies/ExportStrategy.cpp
    src/factories/ReportFactory.cpp
)

add_executable(timetracker ${SOURCES})