cmake_minimum_required(VERSION 3.27)
project(CppCurrency)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
    Source/CppCurrency/TApplication.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC Source)

add_subdirectory(External)
target_link_libraries(${PROJECT_NAME} PUBLIC drogon)

add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE ${PROJECT_NAME})

