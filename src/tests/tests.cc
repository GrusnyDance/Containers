#include <gtest/gtest.h>

#include "test_array.cc"
#include "test_list.cc"
#include "test_map.cc"
#include "test_queue.cc"
#include "test_set.cc"
#include "test_stack.cc"
#include "test_vector.cc"
#include "test_multiset.cc"

GTEST_API_ int main(int argc, char** argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}