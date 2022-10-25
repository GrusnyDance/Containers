#include "s21_stack.h"
#include "gtest/gtest.h"
#include <stack>

#define CT std::cout << "            " <<
#define EN std::endl;

template <class T>
using stack = s21::stack<T>;

template <class T>
using original_stack = std::stack<T>;

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
    CT "b = " << b.top() << "   a = " << a.top() << EN
    a.pop();
    b.pop();
  }
}

TEST(stack, PushPop) {
  stack<int> a;
  original_stack<int>b;
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
