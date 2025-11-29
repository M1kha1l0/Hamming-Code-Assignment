add_library(codec STATIC codec.cpp codec.h)
target_include_directories(codec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})