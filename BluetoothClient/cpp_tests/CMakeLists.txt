cmake_minimum_required(VERSION 3.10)
project(project-name)

set(CMAKE_CXX_STANDARD 17)  # Catch2 v3 requires C++17

include_directories(${CMAKE_SOURCE_DIR}/tests)

enable_testing()

add_executable(CalculatorTests tests/CalculatorTests.cpp)
add_executable(BufferHelperTests tests/BufferHelperTests.cpp)

find_package(Catch2 3 REQUIRED)
target_link_libraries(CalculatorTests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(BufferHelperTests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)

catch_discover_tests(CalculatorTests)
catch_discover_tests(BufferHelperTests)