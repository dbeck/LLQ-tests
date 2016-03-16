project(LLQ-tests)
cmake_minimum_required(VERSION 3.5)
enable_testing()
include_directories( ./ )

add_executable( simple.t simple.cc )
add_test( simple.t ${EXECUTABLE_OUTPUT_PATH}/simple.t )

add_executable( buffer.t buffer.cc LLQ/buffer.hh )
add_test( buffer.t ${EXECUTABLE_OUTPUT_PATH}/buffer.t )
