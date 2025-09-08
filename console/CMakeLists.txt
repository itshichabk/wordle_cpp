cmake_minimum_required (VERSION 3.20)

add_library(lib_console "src/Console.cpp" "src/Window.cpp")

target_include_directories(lib_console PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(lib_console ${CURSES} lib_game)
