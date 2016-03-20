#include <LLQ/shmem.hh>
#include <LLQ/buffer.hh>
#include <LLQ/layout.hh>
#include <chrono>
#include <thread>
#include <iostream>

int main()
{
  using namespace LLQ;
  shmem sm{"/layout1", 65536, true};
  buffer bf{sm.fd(), sm.size(), sm.writable()};
  layout_1<65536, 124> ll1{bf.ptr()};
  ll1.reset_header();
  
  std::this_thread::sleep_for(std::chrono::seconds(10));

  std::cout << "start pushing 655360 numbers\n";
  for( uint32_t i=0; i<655360; ++i )
  {
    ll1.push(&i, sizeof(i));
  }
  std::cout << "pushed 655360 numbers\n";
  
  return 0;
}
