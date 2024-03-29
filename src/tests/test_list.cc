
#include <initializer_list>
#include <list>
#include <vector>

#include "../s21_list.hpp"

template <class T>
void fullListCheck(s21::list<T> test, std::list<T> norm) {
  ASSERT_EQ(test.size(), norm.size());
  ASSERT_EQ(test.empty(), norm.empty());
  ASSERT_EQ(test.max_size(), norm.max_size());
  ASSERT_EQ(*test.begin(), *norm.begin());
  ASSERT_EQ(test.front(), norm.front());
  ASSERT_EQ(test.back(), norm.back());
  auto testIter = test.begin();
  auto normIter = norm.begin();
  while (testIter != test.end()) {
    ASSERT_EQ(*testIter, *normIter);
    testIter++;
    normIter++;
  }
}

template <class T>
void shortListCheck(s21::list<T> test, std::list<T> norm) {
  ASSERT_EQ(test.size(), norm.size());
  ASSERT_EQ(test.empty(), norm.empty());
  ASSERT_EQ(test.max_size(), norm.max_size());
}

TEST(ListTest, newList) {
  using type = int;
  std::list<type> norm;
  s21::list<type> test;
  shortListCheck<type>(test, norm);
}

TEST(ListTest, newSizeList1) {
  using type = int;
  std::list<type> norm(5);
  s21::list<type> test(5);
  shortListCheck<type>(test, norm);
}

TEST(ListTest, newSizeList2) {
  using type = float;
  std::list<type> norm(0);
  s21::list<type> test(0);
  shortListCheck<type>(test, norm);
}

TEST(ListTest, newSizeList3) {
  using type = std::pair<int, char>;
  std::list<type> norm(123456);
  s21::list<type> test(123456);
  shortListCheck<type>(test, norm);
}

TEST(ListTest, initializerList1) {
  using type = double;
  std::list<type> norm{1, 2, -4, 5.55};
  s21::list<type> test{1, 2, -4, 5.55};
  fullListCheck<type>(test, norm);
}

TEST(ListTest, initializerList2) {
  using type = char;
  std::list<type> norm{'a', 'r', 't', 'y'};
  s21::list<type> test{'a', 'r', 't', 'y'};
  fullListCheck<type>(test, norm);
}

TEST(ListTest, initializerList3) {
  using type = std::string;
  std::list<type> norm{"qwerty", "asdf", ""};
  s21::list<type> test{"qwerty", "asdf", ""};
  fullListCheck<type>(test, norm);
}

TEST(ListTest, newCopyList1) {
  using type = double;
  std::list<type> copyNorm{1.45, 2, -4, 5.55, -65.56, 0, 11};
  s21::list<type> copyTest{1.45, 2, -4, 5.55, -65.56, 0, 11};
  std::list<type> norm(copyNorm);
  s21::list<type> test(copyTest);
  fullListCheck<type>(test, norm);
  fullListCheck<type>(copyTest, copyNorm);
}

TEST(ListTest, newCopyList2) {
  using type = std::string;
  std::list<type> copyNorm{"qwerty", "asdf", " "};
  s21::list<type> copyTest{"qwerty", "asdf", " "};
  std::list<type> norm = copyNorm;
  s21::list<type> test = copyTest;
  fullListCheck<type>(test, norm);
  fullListCheck<type>(copyTest, copyNorm);
}

TEST(ListTest, newMoveList1) {
  using type = uint;
  std::list<type> moveNorm{1, 2, 3, 4, 5};
  s21::list<type> moveTest{1, 2, 3, 4, 5};
  std::list<type> norm(std::move(moveNorm));
  s21::list<type> test(std::move(moveTest));
  fullListCheck<type>(test, norm);
  shortListCheck<type>(moveTest, moveNorm);
}

TEST(ListTest, newMoveList2) {
  using type = float;
  std::list<type> moveNorm{1.7, 2.8, -0.7, 4.7, -5.66};
  s21::list<type> moveTest{1.7, 2.8, -0.7, 4.7, -5.66};
  std::list<type> norm{1, 2};
  norm = std::move(moveNorm);
  s21::list<type> test{1, 2};
  test = std::move(moveTest);
  fullListCheck<type>(test, norm);
  shortListCheck<type>(moveTest, moveNorm);
}

TEST(ListTest, clearList) {
  using type = std::pair<int, char>;
  std::list<type> norm(123456);
  s21::list<type> test(123456);
  shortListCheck<type>(test, norm);
  norm.clear();
  test.clear();
  shortListCheck<type>(test, norm);
}

TEST(ListTest, clearEmptyList) {
  using type = bool;
  std::list<type> norm;
  s21::list<type> test;
  shortListCheck<type>(test, norm);
  norm.clear();
  test.clear();
  shortListCheck<type>(test, norm);
}

TEST(ListTest, pushBack) {
  using type = std::pair<int, char>;
  std::list<type> norm;
  s21::list<type> test;
  for (int k = 0; k < 10; k++) {
    char A = 'a';
    norm.push_back({k, A});
    test.push_back({k, A});
    A += 1;
    fullListCheck<type>(test, norm);
  }
  norm.clear();
  test.clear();
  shortListCheck<type>(test, norm);
}

TEST(ListTest, pushFront) {
  using type = long long int;
  std::list<type> norm;
  s21::list<type> test;
  for (int k = 0; k < 11; k++) {
    norm.push_front(k * 123456789);
    test.push_front(k * 123456789);
    fullListCheck<type>(test, norm);
  }
  norm.clear();
  test.clear();
  shortListCheck<type>(test, norm);
}

TEST(ListTest, popBack) {
  using type = bool;
  std::list<type> norm{0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1};
  s21::list<type> test{0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1};
  while (test.size()) {
    fullListCheck<type>(test, norm);
    norm.pop_back();
    test.pop_back();
  }
  shortListCheck<type>(test, norm);
}

TEST(ListTest, popFront) {
  using type = char;
  std::list<type> norm{'a', 'b', 'c', 'T', '1'};
  s21::list<type> test{'a', 'b', 'c', 'T', '1'};
  while (test.size()) {
    fullListCheck<type>(test, norm);
    norm.pop_front();
    test.pop_front();
  }
  shortListCheck<type>(test, norm);
}

TEST(ListTest, insert) {
  using type = float;
  std::list<type> norm{0, -1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11};
  s21::list<type> test{0, -1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11};
  std::list<type>::iterator normIter = norm.end();
  s21::list<type>::iterator testIter = test.end();
  *normIter = 111;
  *testIter = 111;
  fullListCheck<type>(test, norm);
  for (int k = 0; k < 45; k++) {
    normIter = norm.insert(normIter, (float)k / 12.12);
    testIter = test.insert(testIter, (float)k / 12.12);
    normIter--;
    testIter--;
    fullListCheck<type>(test, norm);
  }
}

TEST(ListTest, insertEmpty) {
  using type = float;
  std::list<type> norm(0);
  s21::list<type> test(0);
  shortListCheck<type>(test, norm);
  ASSERT_EQ(*norm.insert(norm.begin(), 33.3), *test.insert(test.begin(), 33.3));
  fullListCheck<type>(test, norm);
}

TEST(ListTest, erase) {
  using type = std::pair<int, bool>;
  std::list<type> norm{{5, 1},    {0, 0},    {3, 1}, {-7, 0},
                       {8890, 1}, {-123, 0}, {0, 0}, {1, 1}};
  s21::list<type> test{{5, 1},    {0, 0},    {3, 1}, {-7, 0},
                       {8890, 1}, {-123, 0}, {0, 0}, {1, 1}};
  std::list<type>::iterator normIter = norm.end();
  s21::list<type>::iterator testIter = test.end();
  fullListCheck<type>(test, norm);
  while (test.size()) {
    if (testIter != test.end()) {
      normIter = norm.erase(normIter);
      testIter = test.erase(testIter);
    }
    fullListCheck<type>(test, norm);
    for (int k = 0; k < 3; k++) {
      testIter++;
      normIter++;
    }
  }
}

TEST(ListTest, swap) {
  using type = int;
  std::list<type> norm{1, 2, 3};
  s21::list<type> test{1, 2, 3};
  std::list<type> normSwap{4, 5, 6, 7, 8};
  s21::list<type> testSwap{4, 5, 6, 7, 8};
  fullListCheck<type>(test, norm);
  fullListCheck<type>(testSwap, normSwap);
  norm.swap(normSwap);
  test.swap(testSwap);
  fullListCheck<type>(test, norm);
  fullListCheck<type>(testSwap, normSwap);
}

TEST(ListTest, swap_merge) {
  using type = long double;
  std::list<type> norm{1.111, 2.222, 3.333};
  s21::list<type> test{1.111, 2.222, 3.333};
  std::list<type> normSwap;
  s21::list<type> testSwap;
  fullListCheck<type>(test, norm);
  shortListCheck<type>(testSwap, normSwap);
  norm.swap(normSwap);
  test.swap(testSwap);
  shortListCheck<type>(test, norm);
  fullListCheck<type>(testSwap, normSwap);
  norm.merge(normSwap);
  test.merge(testSwap);
  fullListCheck<type>(test, norm);
  shortListCheck<type>(testSwap, normSwap);
}

TEST(ListTest, merge) {
  using type = int;
  std::list<type> norm{1, 3, 5, 7, 9};
  s21::list<type> test{1, 3, 5, 7, 9};
  std::list<type> normMerge{-9, -4, -1, 0, 5, 123};
  s21::list<type> testMerge{-9, -4, -1, 0, 5, 123};
  fullListCheck<type>(test, norm);
  fullListCheck<type>(testMerge, normMerge);
  norm.merge(normMerge);
  test.merge(testMerge);
  fullListCheck<type>(test, norm);
  shortListCheck<type>(testMerge, normMerge);
}

TEST(ListTest, splice) {
  using type = char;
  std::list<type> norm1{'a', 'v', 'm'};
  s21::list<type> test1{'a', 'v', 'm'};
  std::list<type> norm2{'3', '6'};
  s21::list<type> test2{'3', '6'};
  std::list<type> norm3{'&', '@', '(', '\t'};
  s21::list<type> test3{'&', '@', '(', '\t'};
  fullListCheck<type>(test1, norm1);
  fullListCheck<type>(test2, norm2);
  fullListCheck<type>(test3, norm3);
  std::list<type>::iterator normIter = norm1.end();
  s21::list<type>::iterator testIter = test1.end();
  normIter--;
  testIter--;
  norm1.splice(normIter, norm2);
  test1.splice(testIter, test2);
  fullListCheck<type>(test1, norm1);
  norm1.splice(norm1.begin(), norm3);
  test1.splice(test1.begin(), test3);
  fullListCheck<type>(test1, norm1);
  shortListCheck<type>(test2, norm2);
  shortListCheck<type>(test3, norm3);
}

TEST(ListTest, reverse) {
  using type = std::list<int>;  // leak s21::list
  type a{1, 2, 3};
  type b{5, 6};
  type c{-1, -1, 0, 0};
  std::list<type> norm{c, a, b};
  s21::list<type> test{c, a, b};
  fullListCheck<type>(test, norm);
  norm.reverse();
  test.reverse();
  fullListCheck<type>(test, norm);
}

TEST(ListTest, unique) {
  using type = std::vector<int>;
  std::list<type> norm{{1, 2}, {0, 0}, {0, 0}, {1}, {2}, {2},
                       {1, 2}, {0, 0}, {6},    {2}, {2}};
  s21::list<type> test{{1, 2}, {0, 0}, {0, 0}, {1}, {2}, {2},
                       {1, 2}, {0, 0}, {6},    {2}, {2}};
  fullListCheck<type>(test, norm);
  norm.unique();
  test.unique();
  fullListCheck<type>(test, norm);
}

TEST(ListTest, sort1) {
  using type = int;
  std::list<type> norm{1, 3, 8, 0, -123, -4, 5, 7, 9, -9, -4, -1, 0, 5, 123};
  s21::list<type> test{1, 3, 8, 0, -123, -4, 5, 7, 9, -9, -4, -1, 0, 5, 123};
  fullListCheck<type>(test, norm);
  norm.sort();
  test.sort();
  fullListCheck<type>(test, norm);
  norm.reverse();
  test.reverse();
  fullListCheck<type>(test, norm);
  norm.sort();
  test.sort();
  fullListCheck<type>(test, norm);
}

TEST(ListTest, sort2) {
  using type = long long int;
  std::list<type> norm{1234123412341234, 999, 899, 234, -12, -12356, -44444444,
                       -345645634563456};
  s21::list<type> test{1234123412341234, 999, 899, 234, -12, -12356, -44444444,
                       -345645634563456};
  fullListCheck<type>(test, norm);
  norm.sort();
  test.sort();
  fullListCheck<type>(test, norm);
  norm.reverse();
  test.reverse();
  fullListCheck<type>(test, norm);
  norm.sort();
  test.sort();
  fullListCheck<type>(test, norm);
}

TEST(ListTest, sort3) {
  using type = float;
  std::list<type> norm;
  s21::list<type> test;
  for (int k = -1000; k < 1000; k++) {
    float l = float(k) * float(rand());
    norm.push_back(l);
    test.push_back(l);
  }
  fullListCheck<type>(test, norm);
  norm.sort();
  test.sort();
  fullListCheck<type>(test, norm);
  norm.reverse();
  test.reverse();
  fullListCheck<type>(test, norm);
  norm.sort();
  test.sort();
  fullListCheck<type>(test, norm);
}

TEST(ListTest, operatorCompare) {
  using type = std::pair<size_t, long>;
  s21::list<type> test1{{1, -100000}, {2, 21212121}, {3, 4545}};
  s21::list<type> test2(test1);
  ASSERT_EQ(test1, test2);
}

TEST(ListTest, emplace) {
  using type = int;
  s21::list<type> test{1, 2, 3, 4, 5, 6};
  std::list<type> norm{1, -9, -8, -7, -6, 2, 3, 4, 5, 6};
  s21::list<type>::iterator iter = test.begin();
  iter++;
  test.emplace(iter, -9, -8, -7, -6);
  fullListCheck<type>(test, norm);
}

TEST(ListTest, emplaceOneArg) {
  using type = std::pair<int, char>;
  s21::list<type> test{{1, 'f'}, {123, 'Q'}, {-88, 'p'}};
  std::list<type> norm{{1, 'f'}, {123, 'Q'}, {444, 't'}, {-88, 'p'}};
  s21::list<type>::iterator iter = test.begin();
  iter++;
  iter++;
  test.emplace(iter, {444, 't'});
  fullListCheck<type>(test, norm);
}

TEST(ListTest, emplaceBack) {
  using type = std::string;
  s21::list<type> test;
  std::list<type> norm{"qwerty", "asdfgh", "zxcvbn", "123456"};
  test.emplace_back("qwerty");
  test.emplace_back("asdfgh", "zxcvbn", "123456");
  fullListCheck<type>(test, norm);
}

TEST(ListTest, emplaceFront) {
  using type = double;
  s21::list<type> test{-0.0101, 123098.222};
  std::list<type> norm{1e-34, 123456789, -4e44, 123, -0.0101, 123098.222};
  test.emplace_front(123);
  test.emplace_front(-4e44, 123456789, 1e-34);
  fullListCheck<type>(test, norm);
}
