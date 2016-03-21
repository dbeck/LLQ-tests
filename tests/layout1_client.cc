
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
  target.reserve(65536000);
  
  uint64_t idx = 0;
  auto fn = [&target, &idx](const void * ptr,
                            uint16_t len,
                            uint64_t id) {
    uint32_t tmp;
    ::memcpy(&tmp,ptr,len);
    target.push_back(tmp);
    idx = id;
    return true;
  };
  
  std::cout << "start receiving messages\n";
  
  while( true )
  {
    if( ll1.pop(idx, fn) == 0 )
    {
      if( target.size() > 0 &&
          target.back() == (65536000-1) )
      {
        break;
      }
    }
  }
  
  std::cout << " target.size=" << target.size()
            << " target.front=" << target.front()
            << " target.back=" << target.back()
            << "\n";

  uint32_t prev = 0;
  size_t c = 0;
  for( auto it=target.begin(); it!=target.end(); ++it )
  {
    std::cout << *it;
    if( prev > *it )
      std::cout << "(!)";
    else if( (prev+1) != *it )
      std::cout << '[' << ((*it)-prev) << ']';
    std::cout << ' ';
    if( (++c % 16) == 0 )
      std::cout << std::endl;
    prev = *it;
  }
  std::cout << std::endl;
  
  return 0;
}
