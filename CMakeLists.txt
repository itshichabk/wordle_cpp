# CMakeList.txt : projet CMake pour wordle, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

include(FetchContent)

project ("wordle")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (wordle "main.cpp")

FetchContent_Declare(
	miniaudio
	GIT_REPOSITORY https://github.com/mackron/miniaudio.git
	GIT_TAG        350784a9467a79d0fa65802132668e5afbcf3777
)

FetchContent_Declare(
	nlohmann_json
	GIT_REPOSITORY https://github.com/nlohmann/json.git
	GIT_TAG        55f93686c01528224f448c19128836e7df245f72
)

FetchContent_Declare(
	pdcurses
	GIT_REPOSITORY https://github.com/scivision/PDCurses.git
	GIT_TAG        743ba4cf0f14c3f416934b11e3c22702068d260b
)

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(miniaudio nlohmann_json googletest)

set(CURSES_WIN   pdcurses)
set(CURSES_LINUX ncursesw)

# Windows
if (WIN32)
	set(BUILD_SHARED_LIBS OFF)
	set(BUILD_STATIC_LIBS ON)

	# PDCurses
	set(CURSES ${CURSES_WIN})
	add_compile_definitions(PDC_WIDE)

	FetchContent_MakeAvailable(pdcurses)

# Linux
elseif (LINUX)
	# Ncurses
	set(CURSES ${CURSES_LINUX})
	set(CURSES_NEED_NCURSES TRUE)
	find_package(Curses REQUIRED)
	include_directories(${CURSES_INCLUDE_DIR}})

endif()

enable_testing()

add_subdirectory(curl_helpers)
add_subdirectory(game)

set(LINK_LIBS_COMMON 
		curl_helpers game
		miniaudio nlohmann_json::nlohmann_json)

list(APPEND LINK_LIBS ${LINK_LIBS_COMMON} ${CURSES})
target_link_libraries(wordle ${LINK_LIBS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET wordle PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
