
#include "perf.hh"
#include <LLQ/layout.hh>

void baseline() {}

template <uint16_t ITEMS, size_t ITEM_SIZE, size_t BUFFER_SIZE>
void measure_IIB(const char * prefix)
{
  char buf[BUFFER_SIZE];
  char data[ITEM_SIZE];
  ::memset(data,0,ITEM_SIZE);
  
  {
    LLQ::layout_1<BUFFER_SIZE,ITEMS> ll1{buf};

    auto fn = [&ll1,&data]() {
      ll1.push(data, ITEM_SIZE);
    };
    LLQ::test::perf<100000>(prefix, fn);
  }
}

int main()
{
  #define MEASURE(F,N) LLQ::test::perf<N>(#F, F);
  
  MEASURE(baseline, 100000);
  
  #define MEASURE_IIB(ITEMS, ITEM_SIZE, BUFFER_SIZE) measure_IIB<ITEMS, ITEM_SIZE, BUFFER_SIZE>(#ITEMS "-" #ITEM_SIZE "-" #BUFFER_SIZE );

  MEASURE_IIB(28, 1, 4096);
  MEASURE_IIB(60, 1, 4096);
  MEASURE_IIB(92, 1, 4096);
  MEASURE_IIB(124, 1, 4096);

  MEASURE_IIB(28, 5, 4096);
  MEASURE_IIB(60, 5, 4096);
  MEASURE_IIB(92, 5, 4096);
  MEASURE_IIB(124, 5, 4096);

  MEASURE_IIB(28, 19, 4096);
  MEASURE_IIB(60, 19, 4096);
  MEASURE_IIB(92, 19, 4096);

  MEASURE_IIB(28, 1, 60000);
  MEASURE_IIB(60, 1, 60000);
  MEASURE_IIB(92, 1, 60000);
  MEASURE_IIB(124, 1, 60000);
  
  MEASURE_IIB(28, 5, 60000);
  MEASURE_IIB(60, 5, 60000);
  MEASURE_IIB(92, 5, 60000);
  MEASURE_IIB(124, 5, 60000);
  
  MEASURE_IIB(28, 19, 60000);
  MEASURE_IIB(60, 19, 60000);
  MEASURE_IIB(92, 19, 60000);
  MEASURE_IIB(124, 19, 60000);
  
  MEASURE_IIB(28, 101, 60000);
  MEASURE_IIB(60, 101, 60000);
  MEASURE_IIB(92, 101, 60000);
  MEASURE_IIB(124, 101, 60000);

  MEASURE_IIB(28, 1, 2060000);
  MEASURE_IIB(60, 1, 2060000);
  MEASURE_IIB(92, 1, 2060000);
  MEASURE_IIB(124, 1, 2060000);
  
  MEASURE_IIB(28, 5, 2060000);
  MEASURE_IIB(60, 5, 2060000);
  MEASURE_IIB(92, 5, 2060000);
  MEASURE_IIB(124, 5, 2060000);
  
  MEASURE_IIB(28, 19, 2060000);
  MEASURE_IIB(60, 19, 2060000);
  MEASURE_IIB(92, 19, 2060000);
  MEASURE_IIB(124, 19, 2060000);
  
  MEASURE_IIB(28, 101, 2060000);
  MEASURE_IIB(60, 101, 2060000);
  MEASURE_IIB(92, 101, 2060000);
  MEASURE_IIB(124, 101, 2060000);
  
  return 0;
}
