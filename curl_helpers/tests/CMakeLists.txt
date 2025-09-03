if (NOT (TARGET gtest AND TARGET gtest_main))
    message(FATAL_ERROR "gtest and gtest_main targets NOT found")
endif()

add_executable(curl_helpers_tests curl_helpers_CurlInstance.cpp)

target_link_libraries(curl_helpers_tests curl_helpers GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(curl_helpers_tests)
