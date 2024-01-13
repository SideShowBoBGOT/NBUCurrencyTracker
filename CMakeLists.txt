cmake_minimum_required(VERSION 3.27)
project(CppCurrency)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
        Source/CppCurrency/TApplication.cpp
        Source/CppCurrency/Views/TConsoleUI.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC Source)

add_subdirectory(External)
target_link_libraries(${PROJECT_NAME} PUBLIC httplib::httplib)
target_link_libraries(${PROJECT_NAME} PUBLIC pugixml::pugixml)
target_link_libraries(${PROJECT_NAME} PUBLIC magic_enum::magic_enum)
target_link_libraries(${PROJECT_NAME} PUBLIC simdutf::simdutf)
target_link_libraries(${PROJECT_NAME}
        PUBLIC ftxui::screen
        PUBLIC ftxui::dom
        PUBLIC ftxui::component
)

add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE ${PROJECT_NAME})

