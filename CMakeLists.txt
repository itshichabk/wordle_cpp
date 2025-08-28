# CMakeList.txt : projet CMake pour wordle, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.15)

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

include(FetchContent)

project ("wordle")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (wordle "wordle.cpp" "wordle.h")

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
	curl
	GIT_REPOSITORY https://github.com/curl/curl.git
	GIT_TAG        cfbfb65047e85e6b08af65fe9cdbcf68e9ad496a
)

FetchContent_MakeAvailable(miniaudio nlohmann_json)

set(LINK_LIBS_COMMON miniaudio nlohmann_json::nlohmann_json)
set(CURSES_WIN   pdcurses)
set(CURSES_LINUX ncursesw)

# Windows
if (WIN32)
	set(BUILD_SHARED_LIBS OFF)
	set(BUILD_STATIC_LIBS ON)

	# PDCurses
	set(CURSES ${CURSES_WIN})
	add_compile_definitions(PDC_WIDE)

	# CURL (static)
	add_compile_definitions(CURL_STATICLIB)
	set(CURL_LIBRARIES CURL::libcurl_static)
	set(BUILD_LIBCURL_DOCS OFF)
	set(BUILD_STATIC_CURL ON)
	set(CURL_STATIC_CRT ON)
	set(CURL_USE_LIBPSL OFF)
	set(CURL_ENABLE_SSL ON)
	set(CURL_USE_OPENSSL OFF)
	set(CURL_USE_SCHANNEL ON)

	FetchContent_MakeAvailable(pdcurses curl)

# Linux
elseif (LINUX)
	# Ncurses
	set(CURSES ${CURSES_LINUX})
	set(CURSES_NEED_NCURSES TRUE)
	find_package(Curses REQUIRED)
	include_directories(${CURSES_INCLUDE_DIR}})

	# CURL
	find_package(CURL REQUIRED)
	include_directories(${CURL_INCLUDE_DIR}})

endif()

list(APPEND LINK_LIBS ${LINK_LIBS_COMMON} ${CURSES} ${CURL_LIBRARIES})
target_link_libraries(wordle ${LINK_LIBS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET wordle PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
