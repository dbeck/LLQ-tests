#ifndef LLQ_TEST_PERF_INCLUDED
#define LLQ_TEST_PERF_INCLUDED

#include <chrono>
#include <functional>
#include <iostream>

namespace LLQ { namespace test {

  template <uint32_t MIN, uint32_t MS=1500>
  void perf( const std::string & prefix, std::function<void(void)> fn )
  {
    using namespace std::chrono;
    time_point<high_resolution_clock> start = high_resolution_clock::now();

    uint64_t n_calls = 0;
    uint64_t iter    = MIN;

    while( true )
    {
      for( uint64_t i=0; i<iter; ++i ) fn();
      n_calls += iter;
      iter    *= 2;
      auto now = high_resolution_clock::now();
      if( duration_cast<milliseconds>(now - start).count() > MS  )
      {
        // print
        uint64_t usec = duration_cast<microseconds>(now - start).count();
        double calls_per_usec = ((double)(n_calls)) / ((double)(usec));
        double usecs_per_call = ((double)(usec)) / ((double)(n_calls));
        std::cout << prefix
                  << " : calls/usec: " << calls_per_usec
                  << " : usecs/call: " << usecs_per_call
                  << std::endl;
        break;
      }
    }
  }

}}

#endif /* end of include guard: LLQ_TEST_PERF_INCLUDED */
