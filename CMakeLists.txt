project( LLQ-tests )
cmake_minimum_required( VERSION 3.5 )
include_directories( ./ ./googletest/googletest/include )
link_directories( ./googletest/googlemock/gtest ./googletest/googletest )
enable_testing()

set(BUILD_GTEST ON)
set(BUILD_GMOCK ON)

subdirs( googletest tests )
