cmake_minimum_required(VERSION 3.12)

project(SnakeGame)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})
target_include_directories(main PUBLIC src/include third_party/SFML/include)
target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

set_property(
    TARGET main PROPERTY
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON

)

file(COPY "assets" DESTINATION "${CMAKE_BINARY_DIR}/${NAME}")
