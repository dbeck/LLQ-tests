project( LLQ-tests )
cmake_minimum_required( VERSION 3.5 )
enable_testing( )
include_directories( ./ )

set(BUILD_GTEST ON)
set(BUILD_GMOCK OFF)

subdirs( googletest tests )

set(LLQ_COMMON_FLAGS "-std=c++11 -fno-strict-aliasing")
set(CMAKE_CXX_FLAGS "-g3 ${LLQ_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 ${LLQ_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-s -O3 ${LLQ_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -O0 ${LLQ_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 ${LLQ_COMMON_FLAGS}")

add_executable( simple.t simple.cc )
add_test( simple.t ${EXECUTABLE_OUTPUT_PATH}/simple.t )

add_executable( buffer.t buffer.cc LLQ/buffer.hh )
add_test( buffer.t ${EXECUTABLE_OUTPUT_PATH}/buffer.t )

add_executable( reader.t reader.cc LLQ/reader.hh )
add_test( reader.t ${EXECUTABLE_OUTPUT_PATH}/reader.t )

add_executable( writer.t writer.cc LLQ/writer.hh )
add_test( writer.t ${EXECUTABLE_OUTPUT_PATH}/writer.t )

add_executable( queue.t queue.cc LLQ/queue.hh )
add_test( queue.t ${EXECUTABLE_OUTPUT_PATH}/queue.t )

add_executable( file.t file.cc LLQ/file.hh )
add_test( file.t ${EXECUTABLE_OUTPUT_PATH}/file.t )

add_executable( shmem.t shmem.cc LLQ/shmem.hh )
add_test( shmem.t ${EXECUTABLE_OUTPUT_PATH}/shmem.t )
