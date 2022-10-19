
#include <gtest/gtest.h>
#include <queue>
#include <initializer_list>
#include <vector>
#include "s21_queue.h"

template <class T>
void queueCheck(s21::queue<T> test, std::queue<T> norm) {
    ASSERT_EQ(norm.empty(), test.empty());
    ASSERT_EQ(norm.size(), test.size());
    if (!test.empty()) {
        ASSERT_EQ(norm.back(), test.back());
        ASSERT_EQ(norm.front(), test.front());
    }
}

TEST(queueTest, newQueue) {
    using type = int;
    std::queue<type> norm;
    s21::queue<type> test;
    queueCheck<type>(test, norm);
}

TEST(queueTest, initializerList1) {
    using type = float;
    std::queue<type> norm({1.12, 2.45, 3.01});
    s21::queue<type> test({1.12, 2.45, 3.01});
    queueCheck<type>(test, norm);
}

TEST(queueTest, initializerList2) {
    using type = std::string;
    std::queue<type> norm({"juipp"});
    s21::queue<type> test({"juipp"});
    queueCheck<type>(test, norm);
}

TEST(queueTest, initializerList3) {
    using type = std::pair<int, char>;
    std::queue<type> norm({{3, 'e'}, {-455, 'Q'}});
    s21::queue<type> test({{3, 'e'}, {-455, 'Q'}});
    queueCheck<type>(test, norm);
}

TEST(queueTest, newCopyQueue) {
    using type = s21::queue<bool>;
    std::queue<type> norm({{0, 1, 1}, {0, 0, 0}, {1, 1}});
    s21::queue<type> test({{0, 1, 1}, {0, 0, 0}, {1, 1}});
    queueCheck<type>(test, norm);
}

TEST(queueTest, pushTest1) {
    using type = std::vector<int>;
    std::queue<type> norm({{1}, {2}, {-1, -43, -76, -999}});
    s21::queue<type> test({{1}, {2}, {-1, -43, -76, -999}});
    queueCheck<type>(test, norm);
    norm.push({3, 5});
    test.push({3, 5});
    queueCheck<type>(test, norm);
}

TEST(queueTest, pushTest2) {
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

TEST(queueTest, popTest1) {
    using type = char;
    std::queue<type> norm;
    s21::queue<type> test;
    norm.pop();
    test.pop();
}

TEST(queueTest, popTest2) {
    using type = float;
    std::queue<type> norm({1.1, 2.2, -3.3, -4.4, 0.0001234, 2, 4, 88});
    s21::queue<type> test({1.1, 2.2, -3.3, -4.4, 0.0001234, 2, 4, 88});
    queueCheck<type>(test, norm);
    while(!test.empty()) {
        norm.pop();
        test.pop();
        queueCheck<type>(test, norm);
    }
}

TEST(queueTest, popPushTest) {
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
    while(!test.empty()) {
        norm.pop();
        test.pop();
        queueCheck<type>(test, norm);
    }
}

TEST(queueTest, swap) {
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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
