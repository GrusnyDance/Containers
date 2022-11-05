#include <stack>

#include "../s21_stack.hpp"

#define CT std::cout << "            " <<
#define EN std::endl;

// template <class T>
// using stack = s21::stack<T>;

// template <class T>
// using std::stack = std::stack<T>;

TEST(StackTest, constructors) {
  s21::stack<int> a;
  const s21::stack<int> AA;
  std::stack<int> B;
  const std::stack<int> BB;

  s21::stack<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i = 10; i > 0; i--) {
    ASSERT_EQ(b.top(), i);
    b.pop();
  }
}

TEST(StackTest, copy) {
  s21::stack<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  b.push(4);

  s21::stack<int> a(b);

  for (int i = 4; i > 0; i--) {
    ASSERT_EQ(a.top(), i);
    a.pop();
    b.pop();
  }

  s21::stack<int> lol{1, 2, 3, 4, 5};
  s21::stack<int> kek = std::move(lol);
}

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> A;
  const s21::stack<int> AA;
  std::stack<int> B;
  const std::stack<int> BB;
}

TEST(StackTest, Constructors) {
  s21::stack<int> A;
  std::stack<int> B;
  for (int i = 0; i < 100; i++) {
    A.push(i);
    B.push(i);
  }
  s21::stack<int> A_copy(A);
  s21::stack<int> A_move(std::move(A));
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(A_copy.top(), A_move.top());
    A_copy.pop();
    A_move.pop();
  }
}

TEST(StackTest, InitializerConstructor) {
  s21::stack<int> A({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  std::stack<int> B({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  while (B.size() != 0) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
}

TEST(StackTest, PushAndPop) {
  s21::stack<int> A;
  std::stack<int> B;
  for (int i = 0; i < 100; i++) {
    A.push(i);
    B.push(i);
  }
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
}

TEST(StackTest, PushPop2) {
  s21::stack<int> A;
  std::stack<int> B;
  for (int i = 0; i < 100; i++) {
    A.push(i);
    B.push(i);
  }
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
}

TEST(StackTest, PushPop) {
  s21::stack<int> a;
  std::stack<int> b;
  for (int i = 0; i < 1000; i++) {
    a.push(i);
    b.push(i);
  }

  for (int i = 1000 - 1; i >= 0; i--) {
    ASSERT_EQ(a.top(), b.top());
    a.pop();
    b.pop();
  }
}

TEST(StackTest, emplace) {
  s21::stack<int> a;
  std::stack<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  b.push(4);
  b.emplace(5);

  a.push(1);
  a.push(2);
  a.push(3);
  a.push(4);
  a.emplace_front(5);
  int i = 5;
  while (i > 0) {
    ASSERT_EQ(a.top(), b.top());
    a.pop();
    b.pop();
    i--;
  }
}
