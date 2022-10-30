#include <string.h>

#include <vector>

// #include "gtest/gtest.h"
#include "../s21_vector.hpp"

#define CT std::cout << "            " <<
#define EN std::endl;

// template <class T>
// using vector = s21::vector<T>;

// template <class T>
// usstd:vector = std::vector<T>;

class VectorTest : public ::testing::Test {};

TEST(VectorTest, Empty) {
  s21::vector<int> A;
  EXPECT_EQ(A.empty(), true);
  A.push_back(1);
  EXPECT_EQ(A.empty(), false);
  const s21::vector<int> B;
  EXPECT_EQ(B.empty(), true);
}

TEST(VectorTest, Size) {
  s21::vector<int> A;
  EXPECT_EQ(A.size(), 0);
  A.push_back(1);
  EXPECT_EQ(A.size(), 1);
  const s21::vector<int> B;
  EXPECT_EQ(B.size(), 0);
}

TEST(VectorTest, FrontBack) {
  s21::vector<int> A({1, 2, 3, 4, 5});
  const s21::vector<int> B({1, 2, 3, 4, 5});
  EXPECT_EQ(A.front(), 1);
  EXPECT_EQ(B.front(), 1);
  EXPECT_EQ(A.back(), 5);
  EXPECT_EQ(B.back(), 5);
}

TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> A;
  const s21::vector<int> C;
  std::vector<int> B;
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> A({1, 2, 3, 4, 5});
  std::vector<int> B({1, 2, 3, 4, 5});
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ(i, *j);
    j++;
  }
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> A({1, 2, 3, 4, 5});
  s21::vector<int> B(A);
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ(i, *j);
    j++;
  }
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> A({1, 2, 3, 4, 5});
  const s21::vector<int> B(std::move(A));
  auto j = B.begin();
  for (int i = 1; i <= 5; i++) {
    EXPECT_EQ(i, *j);
    j++;
  }
}

TEST(VectorTest, CopyAssignment) {
  s21::vector<int> A({1, 2, 3, 4, 5});
  s21::vector<int> B({1, 2, 3});
  B = A;
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ(i, *j);
    j++;
  }
  j = B.begin();
  for (int i = 1; i <= 5; i++) {
    EXPECT_EQ(i, *j);
    j++;
  }
}

TEST(VectorTest, MoveAssignment) {
  s21::vector<int> A({1, 2, 3, 4, 5});
  s21::vector<int> B = std::move(A);
  auto j = B.begin();
  for (int i = 1; i <= 5; i++) {
    EXPECT_EQ(i, *j);
    j++;
  }
}

TEST(VectorTest, PushBack) {
  s21::vector<int> A;
  std::vector<int> B;
  for (int i = 0; i < 100; i++) {
    A.push_back(i);
    B.push_back(i);
  }
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ(i, *j);
    j++;
  }
}

TEST(VectorTest, Capacity) {
  s21::vector<int> A;
  A.reserve(100);
  A.push_back(1);
  A.push_back(2);
  EXPECT_EQ(A.capacity(), 100);
  A.shrink_to_fit();
  EXPECT_EQ(A.capacity(), 2);
}

TEST(VectorTest, At) {
  s21::vector<int> A({1, 2, 3, 4, 5});
  s21::vector<int> B({1, 2, 3, 4, 5});
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(A.at(i), B.at(i));
    A.at(i) = i + 2;
    B.at(i) = i + 2;
    EXPECT_EQ(A.at(i), B.at(i));
  }
  const s21::vector<int> AA({1, 2, 3, 4, 5});
  const s21::vector<int> BB({1, 2, 3, 4, 5});
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(A.at(i), B.at(i));
  }
}

TEST(VectorTest, SquareBrackets) {
  s21::vector<int> A({1, 2, 3, 4, 5});
  s21::vector<int> B({1, 2, 3, 4, 5});
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(A[i], B[i]);
    A[i] = i + 2;
    B[i] = i + 2;
    EXPECT_EQ(A[i], B[i]);
  }
  const s21::vector<int> AA({1, 2, 3, 4, 5});
  const s21::vector<int> BB({1, 2, 3, 4, 5});
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(VectorTest, Data) {
  s21::vector<int> A({1, 2, 3, 4, 5});
  EXPECT_EQ((A.data())[0], 1);
}

TEST(VectorTest, Insert) {
  s21::vector<int> A({1, 4, 5, 6, 7});
  auto i = A.begin();
  i++;
  i = A.insert(i, 3);
  i = A.insert(i, 2);
  i = A.begin();
  for (int j = 1; j <= 7; j++) {
    EXPECT_EQ(*i, j);
    i++;
  }
}

TEST(VectorTest, InsertEfficiency) {
  clock_t my_time = clock();
  s21::vector<int> A;
  for (int i = 0; i < 1000; i++) {
    A.insert(A.begin(), i);
  }
  for (int i = 0; i < 1000; i++) {
    A.insert(A.end(), i);
  }
  auto j = A.begin();
  j++;
  j++;
  for (int i = 0; i < 1000; i++) {
    j = A.insert(j, i);
  }
  my_time = clock() - my_time;

  clock_t original_time = clock();
  std::vector<int> B;
  for (int i = 0; i < 1000; i++) {
    B.insert(B.begin(), i);
  }
  for (int i = 0; i < 1000; i++) {
    B.insert(B.end(), i);
  }
  auto k = B.begin();
  k++;
  k++;
  for (int i = 0; i < 1000; i++) {
    k = B.insert(k, i);
  }
  original_time = clock() - original_time;

  EXPECT_TRUE(my_time < original_time * 5);
  j = A.begin();
  for (auto k : B) {
    EXPECT_EQ(k, *j);
    j++;
  }
}

TEST(VectorTest, Erase) {
  s21::vector<int> A({1, 4, 5, 6, 7});
  auto i = A.end();
  i--;
  A.erase(i);
  EXPECT_EQ(A.back(), 6);
  i = A.begin();
  i++;
  A.erase(i);
  EXPECT_EQ(A[0], 1);
  EXPECT_EQ(A[1], 5);
  A.erase(A.begin());
  EXPECT_EQ(A[0], 5);
  s21::vector<int> B;
  B.erase(B.begin());
}

TEST(VectorTest, Swap) {
  s21::vector<int> A({1, 4, 5, 6, 7});
  s21::vector<int> B({1, 2, 3});
  A.swap(B);
  EXPECT_EQ(A[1], 2);
  EXPECT_EQ(B[1], 4);
  A.clear();
  EXPECT_EQ(A.size(), 0);
}

TEST(VectorTest, Emplace) {
  s21::vector<std::pair<int, char>> A;
  std::vector<std::pair<int, char>> B;
  A.emplace_back(1, 'a');
  A.emplace_back(2, 'b');
  A.emplace_back(3, 'c');
  A.emplace_back(4, 'd');
  A.emplace_back(5, 'e');
  A.emplace(A.begin(), 6, 'd');
  A.emplace(A.end(), 7, 'e');
  A.emplace(--A.end(), 8, 'f');
  A.emplace(A.begin(), 6, 'd');
  A.emplace(A.end(), 7, 'e');
  A.emplace(--A.end(), 8, 'f');

  B.emplace_back(1, 'a');
  B.emplace_back(2, 'b');
  B.emplace_back(3, 'c');
  B.emplace_back(4, 'd');
  B.emplace_back(5, 'e');
  B.emplace(B.begin(), 6, 'd');
  B.emplace(B.end(), 7, 'e');
  B.emplace(--B.end(), 8, 'f');
  B.emplace(B.begin(), 6, 'd');
  B.emplace(B.end(), 7, 'e');
  B.emplace(--B.end(), 8, 'f');

  auto j = A.begin();
  for (auto k : B) {
    EXPECT_EQ(k, *j);
    j++;
  }
}

TEST(VectorTest, constructor) {
  s21::vector<int> a{555, 1, 2, 3, 4};
  s21::vector<int> b(a);

  s21::vector<int> c(b);

  ASSERT_EQ(a[0], c[0]);
}

TEST(VectorTest, at) {
  s21::vector<int> a{1, 2, 3, 4};
  // CT "a.at(3) = " << a.at(3) << EN 
  a.at(3) = 5;
  ASSERT_EQ(5, a.at(3));
}

TEST(VectorTest, FrontBack2) {
  s21::vector<int> a{1, 2, 3, -555};
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), -555);
}

TEST(VectorTest, data) {
  s21::vector<int> a{213, 4, 432, 42, 4, 2341};
  // CT a.data();
}

TEST(VectorTest, reserve_shrink_to_fit) {
  s21::vector<int> a{1, 2, 3, 4, 5, 6};
  a.reserve(10);
  a[10] = 10;
  // CT "THAN = " << a[10] << EN 
  ASSERT_EQ(a[10], 10);
  a.shrink_to_fit();
  // CT "NOW  = " << a[10] << EN
}

TEST(VectorTest, clear) {
  s21::vector<int> a{1, 2, 3, 4, 5, 6};
  s21::vector<int> b{-1, -2, -3, -4, -5, -6};
  for (int i = 0; i < 6; i++) {
  }
  // CT EN 
  a.swap(b);
  for (int i = 0; i < 6; i++) {
    ASSERT_TRUE(a[i] < 0);
  }
  a.clear();
  b.clear();
}

TEST(VectorTest, PushPopInsert) {
  s21::vector<int> a{1, 2, 3, 4, 5};

  a.push_back(6);

  ASSERT_EQ(a[5], 6);

  a.pop_back();

  ASSERT_EQ(a.size(), 5);
}

TEST(VectorTest, erase) {
  s21::vector<int> a{1, 2, 3, 4, 5};
  a.erase(a.begin());
  ASSERT_EQ(a[0], 2);
  a.pop_back();
  ASSERT_EQ(a.size(), 3);
}

// int main() {
//   testing::InitGoogleTest();
//   return RUN_ALL_TESTS();
// }
