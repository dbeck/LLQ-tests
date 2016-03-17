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
    shmem sm{"/setup_simple",ps,true};
    EXPECT_TRUE(shmem::destroy("/setup_simple"));
  }
  
  TEST_F(shmem_test, cannot_destroy_non_existant)
  {
    EXPECT_EQ(false, shmem::destroy("/cannot_destroy_non_existant"));
  }
  
  TEST_F(shmem_test, readonly_failes_to_create)
  {
    size_t ps = getpagesize();
    {
      auto fn = [ps]() {
        shmem sm{"/readonly_failes_to_create",ps,false};
      };
      EXPECT_THROW(fn(), std::runtime_error);
    }
  }

  TEST_F(shmem_test, writable_flag)
  {
    size_t ps = getpagesize();
    {
      shmem::destroy("/writable_flag");
      
      shmem sm1{"/writable_flag",ps,true};
      EXPECT_EQ(true, sm1.writable());
      
      {
        shmem sm2{"/writable_flag",ps,false};
        EXPECT_FALSE(sm2.writable());
      }
      
      EXPECT_TRUE(shmem::destroy("/writable_flag"));
    }
  }

  TEST_F(shmem_test, double_destroy_after_close)
  {
    size_t ps = getpagesize();
    {
      shmem sm1{"/double_destroy_after_close",ps,true};
      EXPECT_EQ(true, sm1.writable());
      EXPECT_EQ(ps, sm1.size());
      EXPECT_EQ(sm1.name(),std::string{"/double_destroy_after_close"});
      EXPECT_GT(sm1.fd(), -1);
    }
    
    EXPECT_TRUE(shmem::destroy("/double_destroy_after_close"));
    EXPECT_FALSE(shmem::destroy("/double_destroy_after_close"));
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
        shmem sm{"missing_slash_throws",ps,false};
      };
      EXPECT_THROW(fn(), std::invalid_argument);
    }
  }
  
  TEST_F(shmem_test, invalid_pagesize_throws)
  {
    {
      auto fn = []() {
        shmem sm{"/invalid_pagesize_throws",0,false};
      };
      EXPECT_THROW(fn(), std::invalid_argument);
    }
  }
}}

#endif /* end of include guard: LLQ_SHMEM_TEST_INCLUDED */
