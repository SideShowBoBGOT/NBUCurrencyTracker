cmake_minimum_required(VERSION 3.27)
project(CppCurrency)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
        Source/CppCurrency/Controllers/TController.cpp
        Source/CppCurrency/Views/TToggle.cpp
        Source/CppCurrency/Controllers/NSProvider.cpp
        Source/CppCurrency/Views/TUIContainer.cpp
        Source/CppCurrency/Views/TCurrencyDataView.cpp
        Source/CppCurrency/Views/TCurrencyTable.cpp
        Source/CppCurrency/Helpers/TIntervalClosure.cpp
        Source/CppCurrency/Views/TIntervalModal.cpp
        Source/CppCurrency/Controllers/TConfig.cpp
        Source/CppCurrency/CLI/TApplicationCLI.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC Source)

add_subdirectory(External)
add_subdirectory(FTXUI)
target_link_libraries(${PROJECT_NAME} PUBLIC httplib::httplib)
target_link_libraries(${PROJECT_NAME} PUBLIC pugixml::pugixml)
target_link_libraries(${PROJECT_NAME} PUBLIC magic_enum::magic_enum)
target_link_libraries(${PROJECT_NAME} PUBLIC simdutf::simdutf)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC tomlplusplus::tomlplusplus)
target_link_libraries(${PROJECT_NAME} PUBLIC CLI11::CLI11)
target_link_libraries(${PROJECT_NAME}

        PUBLIC Boost::filesystem)
target_link_libraries(${PROJECT_NAME}
        PUBLIC ftxui::screen
        PUBLIC ftxui::dom
        PUBLIC ftxui::component
)

add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE ${PROJECT_NAME})

