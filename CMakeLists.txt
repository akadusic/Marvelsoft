cmake_minimum_required(VERSION 3.0.0)

project(OrderBook VERSION 1.0.0)


find_package(jsoncpp CONFIG REQUIRED)

add_subdirectory(src)

add_executable(orderBook main.cpp)

target_link_directories(orderBook PRIVATE src jsoncpp_object jsoncpp_static JsonCpp::JsonCpp)

target_link_libraries(orderBook PRIVATE jsoncpp_object jsoncpp_static JsonCpp::JsonCpp_lib)
