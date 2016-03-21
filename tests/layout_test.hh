#ifndef LLQ_LAYOUT_TEST_INCLUDED
#define LLQ_LAYOUT_TEST_INCLUDED

#include "test_config.hh"
#include <LLQ/layout.hh>
#include <vector>
#include <functional>

namespace LLQ { namespace test {

  class layout_test : public ::testing::Test
  {
  };

  TEST_F(layout_test, basic)
  {
    char buf[65536];
    LLQ::layout_1<65536,124> ll1{buf};
    ll1.reset_header();
    
    uint64_t var = 0xDeadBeef;
    ll1.push(&var, sizeof(var));
    
    std::vector<uint64_t> res;
    
    auto fn = [&res](const void * ptr,
                     uint16_t len,
                     uint64_t id) {
      uint64_t tmp;
      ::memcpy(&tmp,ptr,len);
      res.push_back(tmp);
      return false;
    };
    
    EXPECT_EQ(1, ll1.pop(0, fn));
    EXPECT_EQ(1, res.size());
    EXPECT_EQ(0xDeadBeef, res.at(0));
  }
  
  TEST_F(layout_test, multi_pop)
  {
    char buf[65536];
    LLQ::layout_1<65536,124> ll1{buf};
    ll1.reset_header();
    
    std::vector<uint64_t> res, res2;
    
    for( uint64_t i=0; i<30; ++i )
    {
      ll1.push(&i, sizeof(i));
      res2.push_back(i);
    }
    
    uint64_t idx = 0;
    auto fn = [&res, &idx](const void * ptr,
                           uint16_t len,
                           uint64_t id) {
      uint64_t tmp;
      ::memcpy(&tmp,ptr,len);
      res.push_back(tmp);
      idx = id;
      return false;
    };
    
    for( uint64_t i=0; i<30; ++i )
    {
      EXPECT_EQ(1, ll1.pop(idx, fn));
    }
    
    EXPECT_EQ(0, ll1.pop(idx, fn));
    EXPECT_EQ(30, res.size());
    EXPECT_EQ(res2, res);
  }
  
  TEST_F(layout_test, batch_pop)
  {
    char buf[65536];
    LLQ::layout_1<65536,124> ll1{buf};
    ll1.reset_header();
    
    std::vector<uint64_t> res, res2;
    
    for( uint64_t i=0; i<30; ++i )
    {
      ll1.push(&i, sizeof(i));
      res2.push_back(i);
    }
    
    uint64_t idx = 0;
    auto fn = [&res, &idx](const void * ptr,
                           uint16_t len,
                           uint64_t id) {
      uint64_t tmp;
      ::memcpy(&tmp,ptr,len);
      res.push_back(tmp);
      idx = id;
      return ((tmp % 5) != 0);
    };
    
    for( uint64_t i=0; i<30; ++i )
    {
      ll1.pop(idx, fn);
    }
    
    EXPECT_EQ(0, ll1.pop(idx, fn));
    EXPECT_EQ(30, res.size());
    EXPECT_EQ(res2, res);
  }

  TEST_F(layout_test, overflow)
  {
    char buf[65536];
    LLQ::layout_1<65536,28> ll1{buf};
    ll1.reset_header();
    
    std::vector<uint64_t> res, res2;
    
    for( uint64_t i=0; i<30; ++i )
    {
      ll1.push(&i, sizeof(i));
      if( i >= 28 )
      {
        res2.push_back(i);
      }
    }
    
    uint64_t idx = 0;
    auto fn = [&res, &idx](const void * ptr,
                           uint16_t len,
                           uint64_t id) {
      uint64_t tmp;
      ::memcpy(&tmp,ptr,len);
      res.push_back(tmp);
      idx = id;
      return ((tmp % 5) != 0);
    };
    
    for( uint64_t i=0; i<30; ++i )
    {
      ll1.pop(idx, fn);
    }
    
    EXPECT_EQ(0, ll1.pop(idx, fn));
    EXPECT_EQ(2, res.size());
    EXPECT_EQ(res2, res);
  }

  
}}

#endif /* end of include guard: LLQ_LAYOUT_TEST_INCLUDED */
