project( LLQ-tests )
cmake_minimum_required( VERSION 3.5 )
include_directories( ./ )
link_directories( ./googletest/googlemock/gtest )

set(BUILD_GTEST ON)
set(BUILD_GMOCK ON)

subdirs( googletest tests )
