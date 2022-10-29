#include <gtest/gtest.h>

#include <array>
#include <iostream>

#include "s21_array.hpp"

using namespace std;

namespace TestSpace {
// To use a test fixture, derive a class from testing::Test.
class MyTest : public testing::Test {
 protected:
  s21::Array<int, 3> A = {1, 2, 3};
  array<int, 3> origA = {1, 2, 3};
  s21::Array<int, 5> B = {4, 5, 6};
  array<int, 5> origB = {4, 5, 6};
  s21::Array<int, 7> C = {7, 6, 5, 4, 3};
  array<int, 7> origC = {7, 6, 5, 4, 3};
  s21::Array<int, 7> D = {-7, -6, -5, -4, -3};
  array<int, 7> origD = {-7, -6, -5, -4, -3};
};

TEST_F(MyTest, InitializationList) { ASSERT_EQ(A.size(), origA.size()); }

TEST_F(MyTest, Copy) {
  s21::Array<int, 3> E(A);
  ASSERT_EQ(E.size(), A.size());
}

TEST_F(MyTest, Move) {
  s21::Array<int, 3> E = std::move(A);
  ASSERT_EQ(E.size(), A.size());
}

}  // namespace TestSpace

GTEST_API_ int main(int argc, char** argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// int main() {
//   array<int, 5> a = {1, 2, 3};
//   array<int, 5> b = {4, 5, 6};
//   //   array<int, 3> a;
//   s21::Array<int, 7> c = {7, 6, 5, 4, 3};
//   s21::Array<int, 7> d = {-7, -6, -5, -4, -3};
//   //   s21::Array<int, 2> b;
//   a.fill(1);
//   c.fill(2);

//   for (auto i : a) {
//     cout << i << "  ";
//   }
//   cout << endl;

//   for (auto i : c) {
//     cout << i << "  ";
//   }

//   //   cout << a[1] << endl;
//   //   cout << b[1] << endl;

//   //   cout << a.max_size();
//   //   for (int i = 0; i < 5; i++) {
//   //     cout << a[i] << " ";
//   //   }

//   return 0;
// }