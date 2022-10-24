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
  stack<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  stack<int> a(b);

  for (int i = 10; i > 0; i--) {
    // ASSERT_EQ(a.top(), i);
    CT a.top() << EN
    a.pop();
  }
}

TEST(stack, PushPop) {
  stack<int> a;
  for (int i = 0; i < 1000; i++) {
    a.push(i);
  }

  for (int i = 1000 - 1; i >= 0; i--) {
    ASSERT_EQ(a.top(), i);
    a.pop();
  }
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
