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

# Boost::filesystem

set(BOOST_INCLUDE_LIBRARIES filesystem system)
set(BOOST_ENABLE_CMAKE ON)

include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.74.0
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Boost)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::filesystem)

# other libs
target_link_libraries(${PROJECT_NAME} PUBLIC httplib::httplib)

add_subdirectory(External)
target_link_libraries(${PROJECT_NAME} PUBLIC httplib::httplib)
target_link_libraries(${PROJECT_NAME} PUBLIC pugixml::pugixml)
target_link_libraries(${PROJECT_NAME} PUBLIC magic_enum::magic_enum)
target_link_libraries(${PROJECT_NAME} PUBLIC simdutf::simdutf)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC tomlplusplus::tomlplusplus)
target_link_libraries(${PROJECT_NAME} PUBLIC CLI11::CLI11)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)
target_link_libraries(${PROJECT_NAME}
        PUBLIC ftxui::screen
        PUBLIC ftxui::dom
        PUBLIC ftxui::component
)

add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE ${PROJECT_NAME})

