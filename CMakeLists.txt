cmake_minimum_required(VERSION 3.13)

project(redis-starter-cpp)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(Catch2 3 CONFIG REQUIRED)

add_library(redis_core ${SOURCE_FILES})
target_include_directories(redis_core PUBLIC src)
target_link_libraries(redis_core PUBLIC asio asio::asio Threads::Threads)

add_executable(redis src/main.cpp)
target_link_libraries(redis PRIVATE redis_core)

file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE redis_core Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)