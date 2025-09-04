if (NOT (TARGET gtest AND TARGET gtest_main))
    message(FATAL_ERROR "gtest and gtest_main targets NOT found")
endif()

add_executable(lib_network_tests "network_HttpRequest.cpp")

target_link_libraries(lib_network_tests lib_network GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lib_network_tests)
