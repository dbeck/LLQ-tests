#ifndef LLQ_BUFFER_TEST_INCLUDED
#define LLQ_BUFFER_TEST_INCLUDED

#include "test_config.hh"
#include <LLQ/shmem.hh>
#include <LLQ/buffer.hh>

namespace LLQ { namespace test {
  
  class buffer_test : public ::testing::Test
  {
  };
  
  TEST_F(buffer_test, basic)
  {
    shmem::destroy("/buffer_test.basic");
    size_t ps = getpagesize();
    shmem sm{"/buffer_test.basic",ps*2,true};
    buffer buf{sm.fd(), sm.size(), sm.writable()};
    EXPECT_TRUE(shmem::destroy("/buffer_test.basic"));
  }
}}

#endif /* end of include guard: LLQ_BUFFER_TEST_INCLUDED */
