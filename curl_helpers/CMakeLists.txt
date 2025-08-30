cmake_minimum_required (VERSION 3.15)

add_library(curl_helpers STATIC "src/CurlInstance.cpp" "src/CurlRequest.cpp")

if (WIN32)
	FetchContent_Declare(
		curl
		GIT_REPOSITORY https://github.com/curl/curl.git
		GIT_TAG        cfbfb65047e85e6b08af65fe9cdbcf68e9ad496a
	)

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

	FetchContent_MakeAvailable(curl)
else()
	# CURL
	find_package(CURL REQUIRED)
	include_directories(${CURL_INCLUDE_DIR})
endif()

target_include_directories(curl_helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(curl_helpers ${CURL_LIBRARIES})
