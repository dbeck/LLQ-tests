
#include <LLQ/shmem.hh>
#include <LLQ/buffer.hh>
#include <LLQ/layout.hh>
#include <vector>
#include <iostream>

int main()
{
  using namespace LLQ;
  shmem sm{"/layout1", 65536, false};
  buffer bf{sm.fd(), sm.size(), sm.writable()};
  layout_1<65536, 124> ll1{bf.ptr()};
  std::vector<uint32_t> target;
  target.reserve(655360);
  
  for( uint32_t i=0; i<655360; ++i )
  {
    uint32_t res = 0;
    
    target.push_back(res);
    if( res == (655360-1) ) break;
  }
  
  return 0;
}
