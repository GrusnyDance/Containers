
// #include <gtest/gtest.h>

#include <initializer_list>
#include <queue>
#include <vector>

#include "../s21_queue.hpp"

template <class T>
void queueCheck(s21::queue<T> test, std::queue<T> norm) {
  ASSERT_EQ(norm.empty(), test.empty());
  ASSERT_EQ(norm.size(), test.size());
  if (!test.empty()) {
    ASSERT_EQ(norm.back(), test.back());
    ASSERT_EQ(norm.front(), test.front());
  }
}

TEST(QueueTest, newQueue) {
  using type = int;
  std::queue<type> norm;
  s21::queue<type> test;
  queueCheck<type>(test, norm);
}

TEST(QueueTest, initializerList1) {
  using type = float;
  std::queue<type> norm({1.12, 2.45, 3.01});
  s21::queue<type> test({1.12, 2.45, 3.01});
  queueCheck<type>(test, norm);
}

TEST(QueueTest, initializerList2) {
  using type = std::string;
  std::queue<type> norm({"juipp"});
  s21::queue<type> test({"juipp"});
  queueCheck<type>(test, norm);
}

TEST(QueueTest, initializerList3) {
  using type = std::pair<int, char>;
  std::queue<type> norm({{3, 'e'}, {-455, 'Q'}});
  s21::queue<type> test({{3, 'e'}, {-455, 'Q'}});
  queueCheck<type>(test, norm);
}

TEST(QueueTest, newCopyQueue) {
  using type = long double;
  std::queue<type> norm({12, 34e-1, 56e65, 7892341346245});
  s21::queue<type> test({12, 34e-11, 56e65, 7892341346245});
  queueCheck<type>(test, norm);
  std::queue<type> normCopy(norm);
  s21::queue<type> testCopy(test);
  queueCheck<type>(testCopy, normCopy);
  queueCheck<type>(test, norm);
}

TEST(QueueTest, operatorCopy1) {
  using type = bool;
  std::queue<type> norm({1, 0, 1, 1});
  s21::queue<type> test({1, 0, 1, 1});
  queueCheck<type>(test, norm);
  std::queue<type> normCopy({1});
  s21::queue<type> testCopy({1});
  normCopy = norm;
  testCopy = test;
  queueCheck<type>(testCopy, normCopy);
  queueCheck<type>(test, norm);
}

TEST(QueueTest, operatorCopy2) {
  using type = char;
  std::queue<type> norm({'r', 'e', 'q'});
  s21::queue<type> test({'r', 'e', 'q'});
  queueCheck<type>(test, norm);
  std::queue<type> normCopy = norm;
  s21::queue<type> testCopy = test;
  queueCheck<type>(testCopy, normCopy);
  queueCheck<type>(test, norm);
}

TEST(QueueTest, newMoveQueue) {
  using type = float;
  std::queue<type> norm({1.1, 2.2, 3.3, 4.4, 5.5});
  s21::queue<type> test({1.1, 2.2, 3.3, 4.4, 5.5});
  queueCheck<type>(test, norm);
  std::queue<type> normMove(std::move(norm));
  s21::queue<type> testMove(std::move(test));
  queueCheck<type>(test, norm);
  queueCheck<type>(testMove, normMove);
}

TEST(QueueTest, operatorMove1) {
  using type = float;
  std::queue<type> norm({1.1, 2.2, 3.3, 4.4, 5.5});
  s21::queue<type> test({1.1, 2.2, 3.3, 4.4, 5.5});
  queueCheck<type>(test, norm);
  std::queue<type> normMove = std::move(norm);
  s21::queue<type> testMove = std::move(test);
  queueCheck<type>(test, norm);
  queueCheck<type>(testMove, normMove);
}

TEST(QueueTest, operatorMove2) {
  using type = float;
  std::queue<type> norm({1.1, 2.2, 3.3, 4.4, 5.5});
  s21::queue<type> test({1.1, 2.2, 3.3, 4.4, 5.5});
  queueCheck<type>(test, norm);
  std::queue<type> normMove;
  s21::queue<type> testMove;
  testMove = std::move(test);
  normMove = std::move(norm);
  queueCheck<type>(test, norm);
  queueCheck<type>(testMove, normMove);
}

TEST(QueueTest, pushTest1) {
  using type = std::vector<int>;
  std::queue<type> norm({{1}, {2}, {-1, -43, -76, -999}});
  s21::queue<type> test({{1}, {2}, {-1, -43, -76, -999}});
  queueCheck<type>(test, norm);
  norm.push({3, 5});
  test.push({3, 5});
  queueCheck<type>(test, norm);
}

TEST(QueueTest, pushTest2) {
  using type = double;
  std::queue<type> norm;
  s21::queue<type> test;
  queueCheck<type>(test, norm);
  for (int k = 0; k < 1000; k++) {
    double l = (double)rand() / (double)k;
    norm.push(l);
    test.push(l);
    queueCheck<type>(test, norm);
  }
}

TEST(QueueTest, popTest1) {
  using type = char;
  std::queue<type> norm;
  s21::queue<type> test;
  norm.pop();
  test.pop();
}

TEST(QueueTest, popTest2) {
  using type = float;
  std::queue<type> norm({1.1, 2.2, -3.3, -4.4, 0.0001234, 2, 4, 88});
  s21::queue<type> test({1.1, 2.2, -3.3, -4.4, 0.0001234, 2, 4, 88});
  queueCheck<type>(test, norm);
  while (!test.empty()) {
    norm.pop();
    test.pop();
    queueCheck<type>(test, norm);
  }
}

TEST(QueueTest, popPushTest) {
  using type = int;
  std::queue<type> norm;
  s21::queue<type> test;
  queueCheck<type>(test, norm);
  for (int k = 123; k > 0; k--) {
    norm.push(k);
    test.push(k);
    queueCheck<type>(test, norm);
  }
  norm.pop();
  test.pop();
  queueCheck<type>(test, norm);
  while (!test.empty()) {
    norm.pop();
    test.pop();
    queueCheck<type>(test, norm);
  }
}

TEST(QueueTest, swap) {
  using type = s21::list<char>;
  std::queue<type> norm1({{'q'}, {'W', '^'}, {'$', '&', '\t'}});
  s21::queue<type> test1({{'q'}, {'W', '^'}, {'$', '&', '\t'}});
  std::queue<type> norm2({{'Y', '_'}, {'y'}});
  s21::queue<type> test2({{'Y', '_'}, {'y'}});
  queueCheck<type>(test1, norm1);
  queueCheck<type>(test2, norm2);
  norm1.swap(norm2);
  test1.swap(test2);
  queueCheck<type>(test1, norm1);
  queueCheck<type>(test2, norm2);
}

TEST(QueueTest, emplaceBack) {
  using type = int;
  std::queue<type> norm({1, 2, 3, 88, 89, 90, 100});
  s21::queue<type> test({1, 2, 3});
  test.emplace_back(88, 89, 90);
  test.emplace_back(100);
  queueCheck<type>(test, norm);
}

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
