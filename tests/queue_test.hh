#ifndef LLQ_QUEUE_TEST_INCLUDED
#define LLQ_QUEUE_TEST_INCLUDED

#include "test_config.hh"
#include <LLQ/queue.hh>

#include "test_config.hh"
#include <LLQ/shmem.hh>
#include <LLQ/buffer.hh>

namespace LLQ { namespace test {
  
  class queue_test : public ::testing::Test
  {
  };
  
  TEST_F(queue_test, basic)
  {
    shmem::destroy("/queue_test.basic");
    size_t ps = getpagesize();
    shmem sm{"/queue_test.basic",ps*2,true};
    {
      queue<shmem> mqueue{sm};
    }
    EXPECT_TRUE(shmem::destroy("/queue_test.basic"));
  }
}}

#endif /* end of include guard: LLQ_QUEUE_TEST_INCLUDED */
