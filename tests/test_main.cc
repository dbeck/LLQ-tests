
#include "simple_test.hh"
#include "buffer_test.hh"
#include "file_test.hh"
#include "queue_test.hh"
#include "shmem_test.hh"
#include "layout_test.hh"

int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  return ret;
}
