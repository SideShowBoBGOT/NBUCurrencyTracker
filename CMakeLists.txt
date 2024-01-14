cmake_minimum_required(VERSION 3.27)
project(CppCurrency)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
        Source/CppCurrency/Views/TConsoleUI.cpp
        Source/CppCurrency/Views/NSTable.cpp
        Source/CppCurrency/Controllers/TController.cpp
        Source/CppCurrency/Views/NSToggle.cpp
        Source/CppCurrency/Controllers/NSProvider.cpp
        Source/CppCurrency/Models/SCurrencyData.cpp
        Source/CppCurrency/Views/TUIContainer.cpp
        Source/CppCurrency/Views/TCurrencyDataView.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC Source)

add_subdirectory(External)
add_subdirectory(FTXUI)
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

