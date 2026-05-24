cmake_minimum_required(VERSION 3.10)
project(TimeTracker VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

set(CORE_SOURCES
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

add_library(core OBJECT ${CORE_SOURCES})
target_include_directories(core PRIVATE ${INCLUDE_DIR})


add_executable(timetracker src/main.cpp)
target_link_libraries(timetracker core)


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(timetracker PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(core PRIVATE -Wall -Wextra -Wpedantic)
endif()


option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()