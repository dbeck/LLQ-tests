#ifndef LLQ_SHMEM_TEST_INCLUDED
#define LLQ_SHMEM_TEST_INCLUDED

#include "test_config.hh"
#include <LLQ/shmem.hh>

namespace LLQ { namespace test {

  class shmem_test : public ::testing::Test
  {
  };

  TEST_F(shmem_test, destroy_while_active)
  {
    size_t ps = getpagesize();
    shmem sm{"/shmem_test.setup_simple",ps,true};
    EXPECT_TRUE(shmem::destroy("/shmem_test.setup_simple"));
  }
  
  TEST_F(shmem_test, cannot_destroy_non_existant)
  {
    EXPECT_FALSE(shmem::destroy("/shmem_test.cannot_destroy_non_existant"));
  }
  
  TEST_F(shmem_test, readonly_failes_to_create)
  {
    size_t ps = getpagesize();
    {
      auto fn = [ps]() {
        shmem sm{"/shmem_test.readonly_FTC",ps,false};
      };
      EXPECT_THROW(fn(), std::runtime_error);
    }
  }

  TEST_F(shmem_test, writable_flag)
  {
    size_t ps = getpagesize();
    {
      shmem::destroy("/shmem_test.writable_flag");
      
      shmem sm1{"/shmem_test.writable_flag",ps,true};
      EXPECT_EQ(true, sm1.writable());
      
      {
        shmem sm2{"/shmem_test.writable_flag",ps,false};
        EXPECT_FALSE(sm2.writable());
      }
      
      EXPECT_TRUE(shmem::destroy("/shmem_test.writable_flag"));
    }
  }

  TEST_F(shmem_test, double_destroy_after_close)
  {
    size_t ps = getpagesize();
    {
      shmem sm1{"/shmem_test.double_destroy_AC",ps,true};
      EXPECT_EQ(true, sm1.writable());
      EXPECT_EQ(ps, sm1.size());
      EXPECT_EQ(sm1.name(),std::string{"/shmem_test.double_destroy_AC"});
      EXPECT_GT(sm1.fd(), -1);
    }
    
    EXPECT_TRUE(shmem::destroy("/shmem_test.double_destroy_AC"));
    EXPECT_FALSE(shmem::destroy("/shmem_test.double_destroy_AC"));
  }
  
  TEST_F(shmem_test, empty_name_throws)
  {
    size_t ps = getpagesize();
    {
      auto fn = [ps]() {
        shmem sm{"",ps,false};
      };
      EXPECT_THROW(fn(), std::invalid_argument);
    }
  }
  
  TEST_F(shmem_test, double_slash_throws)
  {
    size_t ps = getpagesize();
    {
      auto fn = [ps]() {
        shmem sm{"/double/_slash_throws",ps,false};
      };
      EXPECT_THROW(fn(), std::invalid_argument);
    }
  }
  
  TEST_F(shmem_test, missing_slash_throws)
  {
    size_t ps = getpagesize();
    {
      auto fn = [ps]() {
        shmem sm{"shmem_test.missing_slash_throws",ps,false};
      };
      EXPECT_THROW(fn(), std::invalid_argument);
    }
  }
  
  TEST_F(shmem_test, invalid_pagesize_throws)
  {
    {
      auto fn = []() {
        shmem sm{"/shmem_test.invalid_pagesize_throws",0,false};
      };
      EXPECT_THROW(fn(), std::invalid_argument);
    }
  }
}}

#endif /* end of include guard: LLQ_SHMEM_TEST_INCLUDED */
