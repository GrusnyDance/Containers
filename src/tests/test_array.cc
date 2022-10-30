// #include <gmock/gmock.h>

#include <array>
// #include <iostream>

#include "../s21_array.hpp"

using namespace std;

namespace ArraySpace {
// To use a test fixture, derive a class from testing::Test.
class ArrayTest : public testing::Test {
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

TEST_F(ArrayTest, InitializationList) { ASSERT_EQ(A.size(), origA.size()); }

TEST_F(ArrayTest, Copy) {
  s21::Array<int, 3> E(A);
  ASSERT_EQ(E.size(), A.size());
}

TEST_F(ArrayTest, Move) {
  s21::Array<int, 3> E = std::move(A);
  ASSERT_EQ(E.size(), A.size());
}

TEST_F(ArrayTest, At) { ASSERT_EQ(A.at(1), origA.at(1)); }

TEST_F(ArrayTest, Index) { ASSERT_EQ(A[1], origA[1]); }

TEST_F(ArrayTest, Front) { ASSERT_EQ(A.front(), origA.front()); }

TEST_F(ArrayTest, Back) { ASSERT_EQ(A.back(), origA.back()); }

TEST_F(ArrayTest, Data) { ASSERT_EQ(*(A.data()), *(origA.data())); }

TEST_F(ArrayTest, Begin) { ASSERT_EQ(*(A.begin()), *(origA.begin())); }

TEST_F(ArrayTest, End) { ASSERT_EQ(*(A.end()), *(origA.end())); }

TEST_F(ArrayTest, Empty) {
  array<int, 0> E;
  ASSERT_EQ(E.empty(), !A.empty());
}

TEST_F(ArrayTest, MaxSize) { ASSERT_EQ(A.max_size(), origA.max_size()); }

TEST_F(ArrayTest, Swap) {
  C.swap(D);
  origC.swap(origD);
  for (auto i = 0; i < 7; ++i) {
    ASSERT_EQ(C[i], origC[i]);
    ASSERT_EQ(D[i], origD[i]);
  }
}

TEST_F(ArrayTest, Fill) {
  B.fill(100);
  origB.fill(100);
  for (auto i = 0; i < B.size(); ++i) {
    ASSERT_EQ(B[i], origB[i]);
  }
}

}  // namespace ArraySpace
