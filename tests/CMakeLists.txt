include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.0
)
FetchContent_MakeAvailable(Catch2)


include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(unit_tests unit_tests.cpp)
target_link_libraries(unit_tests
    core
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)

add_executable(scenario_start_stop scenario_start_stop.cpp)
target_link_libraries(scenario_start_stop core)

add_executable(scenario_create_project_task scenario_create_project_task.cpp)
target_link_libraries(scenario_create_project_task core)

add_executable(scenario_export_csv scenario_export_csv.cpp)
target_link_libraries(scenario_export_csv core)