add_executable(hamming main.cpp)

target_link_libraries(hamming PRIVATE codec)

target_include_directories(hamming PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
)