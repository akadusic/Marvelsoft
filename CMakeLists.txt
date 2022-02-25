cmake_minimum_required(VERSION 3.0.0)

project(OrderBook)

include(./vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(jsoncpp CONFIG REQUIRED)

add_definitions(-w)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PUBLIC ../Marvelsoft/include)

target_link_directories(${PROJECT_NAME} PUBLIC ../Marvelsoft/include)

target_link_libraries(${PROJECT_NAME} jsoncpp_object jsoncpp_static JsonCpp::JsonCpp firstLib)
