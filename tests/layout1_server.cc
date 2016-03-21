#include <LLQ/shmem.hh>
#include <LLQ/buffer.hh>
#include <LLQ/layout.hh>
#include <chrono>
#include <thread>
#include <iostream>

int main()
{
  using namespace LLQ;
  
  shmem::destroy("/layout1");
  shmem sm{"/layout1", 65536, true};
  buffer bf{sm.fd(), sm.size(), sm.writable()};
  layout_1<65536, 124> ll1{bf.ptr()};
  ll1.reset_header();
  
  std::this_thread::sleep_for(std::chrono::seconds(10));

  std::cout << "start pushing 65536000 numbers\n";
  for( uint32_t i=0; i<65536000; ++i )
  {
    ll1.push(&i, 4);
  }
  std::cout << "pushed 65536000 numbers\n";
  return 0;
}
