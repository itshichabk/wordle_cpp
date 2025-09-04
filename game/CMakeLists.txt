cmake_minimum_required (VERSION 3.20)

add_library(lib_game "src/Game.cpp" "src/Grid.cpp")

target_include_directories(lib_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(lib_game ${CURSES} lib_network)
