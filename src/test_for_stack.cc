#include "s21_stack.h"
#include "gtest/gtest.h"
#include <stack>

#define CT std::cout << "            " <<
#define EN std::endl;

template <class T> using stack = s21::stack<T>;

template <class T> using original_stack = std::stack<T>;

TEST(stack, constructors) {
  stack<int> a;
  const stack<int> AA;
  original_stack<int> B;
  const original_stack<int> BB;

  stack<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i = 10; i > 0; i--) {
    ASSERT_EQ(b.top(), i);
    b.pop();
  }
}

TEST(stack, copy) {
  stack<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  b.push(4);

  stack<int> a(b);

  for (int i = 4; i > 0; i--) {
    ASSERT_EQ(a.top(), i);
    a.pop();
    b.pop();
  }

  stack<int> lol{1, 2, 3, 4, 5};
  stack<int> kek = std::move(lol);
}

TEST(S21StackTest, DefaultConstructor) {
  stack<int> A;
  const stack<int> AA;
  original_stack<int> B;
  const original_stack<int> BB;
}

TEST(S21StackTest, Constructors) {
  stack<int> A;
  original_stack<int> B;
  for (int i = 0; i < 100; i++) {
    A.push(i);
    B.push(i);
  }
  stack<int> A_copy(A);
  stack<int> A_move(std::move(A));
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(A_copy.top(), A_move.top());
    A_copy.pop();
    A_move.pop();
  }
}

TEST(S21StackTest, InitializerConstructor) {
  stack<int> A({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  original_stack<int> B({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  while (B.size() != 0) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
}

TEST(S21StackTest, PushAndPop) {
  stack<int> A;
  original_stack<int> B;
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

TEST(S21StackTest, PushPop2) {
  stack<int> A;
  original_stack<int> B;
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

TEST(stack, PushPop) {
  stack<int> a;
  original_stack<int> b;
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

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
