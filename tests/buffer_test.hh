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
    size_t ps = getpagesize();
    shmem sm{"/basic",ps,true};
    buffer buf{sm.fd(), sm.size(), sm.writable()};
    EXPECT_TRUE(shmem::destroy("/basic"));
  }
}}

#endif /* end of include guard: LLQ_BUFFER_TEST_INCLUDED */
