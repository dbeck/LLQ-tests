
set(LLQ_COMMON_FLAGS "-std=c++11 -fno-strict-aliasing")
set(CMAKE_CXX_FLAGS "-g3 ${LLQ_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 ${LLQ_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-s -O3 ${LLQ_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -O0 ${LLQ_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 ${LLQ_COMMON_FLAGS}")

link_libraries( gtest )
include_directories( ./LLQ ../googletest/googletest/include )

add_executable( test_main.t
                test_main.cc
                simple_test.hh
                buffer_test.hh ../LLQ/buffer.hh
                reader_test.hh ../LLQ/reader.hh
                writer_test.hh ../LLQ/writer.hh
                queue_test.hh ../LLQ/queue.hh
                file_test.hh ../LLQ/file.hh
                shmem_test.hh ../LLQ/shmem.hh )

add_test( test_main.t ${EXECUTABLE_OUTPUT_PATH}/test_main.t )
