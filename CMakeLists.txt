cmake_minimum_required(VERSION 3.0.0)

project(OrderBook VERSION 1.0.0)

include(./vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(jsoncpp CONFIG REQUIRED)

add_definitions(-w)

add_subdirectory(src)

add_executable(main main.cpp)

target_link_libraries(main jsoncpp_object jsoncpp_static JsonCpp::JsonCpp firstLib)
