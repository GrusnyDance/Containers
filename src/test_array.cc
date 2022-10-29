#include <gtest/gtest.h>

#include <array>
#include <iostream>

#include "s21_array.hpp"

using namespace std;

// namespace TestSpace {
// // To use a test fixture, derive a class from testing::Test.
// class MyTest : public testing::Test {
//  protected:
//   s21::Array<int, 3> A = {1, 2, 3};
//   array<int, 3> origA = {1, 2, 3};
//   s21::Array<int, 5> B = {4, 5, 6};
//   array<int, 5> origB = {4, 5, 6};
//   s21::Array<int, 7> C = {7, 6, 5, 4, 3};
//   array<int, 7> origC = {7, 6, 5, 4, 3};
//   s21::Array<int, 7> D = {-7, -6, -5, -4, -3};
//   array<int, 7> origD = {-7, -6, -5, -4, -3};
// };

// TEST_F(MyTest, InitializationList) { ASSERT_EQ(A.size(), origA.size()); }

// TEST_F(MyTest, Copy) {
//   s21::Array<int, 3> E(A);
//   ASSERT_EQ(E.size(), A.size());
// }

// TEST_F(MyTest, Move) {
//   s21::Array<int, 3> E = std::move(A);
//   ASSERT_EQ(E.size(), A.size());
// }

// TEST(MyTest, At) {
//   s21::Array<int, 3> E = {1, 2, 3};
//   // cout << A.at(1) << endl;
//   ASSERT_EQ(E.at(1), 2);
// }

// // TEST_F(MyTest, Index) { ASSERT_EQ(A[1], origA[1]); }

// // TEST_F(MyTest, Front) { ASSERT_EQ(A.front(), origA.front()); }

// // TEST_F(MyTest, Back) { ASSERT_EQ(A.back(), origA.back()); }

// // TEST_F(MyTest, Data) { ASSERT_EQ(*(A.data()), *(origA.data())); }

// // TEST_F(MyTest, Begin) { ASSERT_EQ(*(A.begin()), *(origA.begin())); }

// // TEST_F(MyTest, End) { ASSERT_EQ(*(A.end()), *(origA.end())); }

// // TEST_F(MyTest, Empty) {
// //   s21::Array<int, 0> E;
// //   array<int, 0> lm;
// //   ASSERT_EQ(lm.empty(), !A.empty());
// // }

// // TEST_F(MyTest, MaxSize) { ASSERT_EQ(A.max_size(), origA.max_size()); }

// // TEST_F(MyTest, Swap) { ASSERT_EQ(*(A.end()), *(origA.end())); }

// // TEST_F(MyTest, Fill) { ASSERT_EQ(*(A.end()), *(origA.end())); }

// }  // namespace TestSpace

// GTEST_API_ int main(int argc, char** argv) {
//   printf("Running main() from %s\n", __FILE__);
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }

int main() {
  // array<int, 5> a = {1, 2, 3};
  // array<int, 5> b = {4, 5, 6};
  //   array<int, 3> a;
  array<int, 7> c = {7, 6, 5, 4, 3};
  cout << c.at(3) << "  ";
  // s21::Array<int, 7> d = {-7, -6, -5, -4, -3};
  //   s21::Array<int, 2> b;
  // a.fill(1);
  // c.fill(2);

  // for (auto i : c) {
  //   cout << i << "  ";
  // }
  // cout << endl;

  // for (auto i : c) {
  //   cout << i << "  ";
  // }

  //   cout << a[1] << endl;
  //   cout << b[1] << endl;

  //   cout << a.max_size();
  //   for (int i = 0; i < 5; i++) {
  //     cout << a[i] << " ";
  //   }

  return 0;
}