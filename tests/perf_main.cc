
#include "perf.hh"
#include <LLQ/layout.hh>

void baseline() {}

int main()
{
  #define MEASURE(F,N) LLQ::test::perf<N>(#F, F);
  
  MEASURE(baseline, 1000);
  {
    char           b[4096];
    LLQ::layout_1  ll1{b, sizeof(b)};
    
    auto ll1_test = [&ll1]() {
      ll1.add("hello",5);
    };
    
    MEASURE(ll1_test, 100);
  }
  return 0;
}
