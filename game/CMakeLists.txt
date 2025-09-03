cmake_minimum_required (VERSION 3.20)

add_library(game "src/Game.cpp" "src/Grid.cpp")

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(game ${CURSES} curl_helpers)
