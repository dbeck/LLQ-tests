project( LLQ-tests )
cmake_minimum_required( VERSION 2.8 )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/ ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include )
link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/gtest ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest )
enable_testing()

set(BUILD_GTEST ON)
set(BUILD_GMOCK ON)

subdirs( googletest tests )
