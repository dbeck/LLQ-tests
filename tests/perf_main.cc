
#include "perf.hh"
#include <LLQ/layout.hh>

void baseline() {}

int main()
{
  #define MEASURE(F,N) LLQ::test::perf<N>(#F, F);
  
  MEASURE(baseline, 1000);
  
  {
    char           b[4096];
    LLQ::layout_1  ll{b, sizeof(b)};
    
    auto ll1_nocheck_1b = [&ll]() {
      ll.add_nocheck("hello",1);
    };
    
    MEASURE(ll1_nocheck_1b, 100);
  }

  {
    char           b[4096];
    LLQ::layout_1  ll{b, sizeof(b)};
    
    auto ll1_checked_5b = [&ll]() {
      ll.add("hello",5);
    };
    
    MEASURE(ll1_checked_5b, 100);
  }
  
  {
    char           b[4096];
    LLQ::layout_1  ll{b, sizeof(b)};
    
    auto ll2_nocheck_5b = [&ll]() {
      ll.add_nocheck("hello",5);
    };
    
    MEASURE(ll2_nocheck_5b, 100);
  }
  
  return 0;
}
