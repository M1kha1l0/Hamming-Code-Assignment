include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(hamming_tests
    test_hamming_codec.cpp
)

target_include_directories(hamming_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(hamming_tests PRIVATE
    codec
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hamming_tests)
