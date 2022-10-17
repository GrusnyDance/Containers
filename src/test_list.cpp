
#include <gtest/gtest.h>
#include <list>
#include <initializer_list>
#include <vector>
#include "s21_list.h"

template <class T, class tIter, class nIter>
void fullListCheck(s21::list<T> test, std::list<T> norm) {
    ASSERT_EQ(test.size(), norm.size());
    ASSERT_EQ(test.empty(), norm.empty());
    ASSERT_EQ(test.max_size(), norm.max_size());
    ASSERT_EQ(*test.begin(), *norm.begin());
    ASSERT_EQ(test.front(), norm.front());
    ASSERT_EQ(test.back(), norm.back());
    tIter testIter = test.begin();
    nIter normIter = norm.begin();
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

TEST(listTest, newList) {
    using type = int;
    std::list<type> norm;
    s21::list<type> test;
    shortListCheck<type>(test, norm);
}
 
TEST(listTest, newSizeList1) {
    using type = int;
    std::list<type> norm(5);
    s21::list<type> test(5);
    shortListCheck<type>(test, norm);
}

TEST(listTest, newSizeList2) {
    using type = float;
    std::list<type> norm(0);
    s21::list<type> test(0);
    shortListCheck<type>(test, norm);
}

TEST(listTest, newSizeList3) {
    using type = std::pair<int, char>;
    std::list<type> norm(123456);
    s21::list<type> test(123456);
    shortListCheck<type>(test, norm);
}

TEST(listTest, initializerList1) {
    using type = double;
    std::list<type> norm{1, 2, -4, 5.55};
    s21::list<type> test{1, 2, -4, 5.55};
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
}

TEST(listTest, initializerList2) {
    using type = char;
    std::list<type> norm{'a', 'r', 't', 'y'};
    s21::list<type> test{'a', 'r', 't', 'y'};
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
}

TEST(listTest, initializerList3) {
    using type = std::string;
    std::list<type> norm{"qwerty", "asdf", ""};
    s21::list<type> test{"qwerty", "asdf", ""};
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
}

TEST(listTest, newCopyList) {
    using type = double;
    std::list<type> copyNorm{1.45, 2, -4, 5.55, -65.56, 0, 11};
    s21::list<type> copyTest{1.45, 2, -4, 5.55, -65.56, 0, 11};
    std::list<type> norm(copyNorm);
    s21::list<type> test(copyTest);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(copyTest, copyNorm);
}

TEST(listTest, newMoveList) {
    using type = std::string;
    std::list<type> moveNorm{"qwerty", "asdf", " "};
    s21::list<type> moveTest{"qwerty", "asdf", " "};
    std::list<type> norm = moveNorm;
    s21::list<type> test = moveTest;
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(moveTest, moveNorm);
}

TEST(listTest, clearList) {
    using type = std::pair<int, char>;
    std::list<type> norm(123456);
    s21::list<type> test(123456);
    ASSERT_EQ(test.empty(), norm.empty());
    ASSERT_EQ(test.size(), norm.size());
    norm.clear();
    test.clear();
    shortListCheck<type>(test, norm);
}

TEST(listTest, pushBack) {
    using type = std::pair<int, char>;
    std::list<type> norm;
    s21::list<type> test;
    for (int k = 0; k < 10; k++) {
        char A = 'a';
        norm.push_back({k, A});
        test.push_back({k, A});
        A += 1;
        fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    }
    norm.clear();
    test.clear();
    shortListCheck<type>(test, norm);
}

TEST(listTest, pushFront) {
    using type = long long int;
    std::list<type> norm;
    s21::list<type> test;
    for (int k = 0; k < 11; k++) {
        norm.push_front(k * 123456789);
        test.push_front(k * 123456789);
        fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    }
    norm.clear();
    test.clear();
    shortListCheck<type>(test, norm);
}

TEST(listTest, popBack) {
    using type = bool;
    std::list<type> norm{0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1};
    s21::list<type> test{0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1};
    for (int k = 0; k < test.size(); k++) {
        fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
        norm.pop_back();
        test.pop_back();
    }
    shortListCheck<type>(test, norm);
}

TEST(listTest, popFront) {
    using type = char;
    std::list<type> norm{'a', 'b', 'c', 'T', '1'};
    s21::list<type> test{'a', 'b', 'c', 'T', '1'};
    for (int k = 0; k < test.size(); k++) {
        fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
        norm.pop_front();
        test.pop_front();
    }
    shortListCheck<type>(test, norm);
}

TEST(listTest, insert) {
    using type = float;
    std::list<type> norm{0, -1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11};
    s21::list<type> test{0, -1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11};
    std::list<type>::iterator normIter = norm.end();
    s21::list<type>::iterator testIter = test.end();
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    for (int k = 0; k < 45; k++) {
        normIter = norm.insert(normIter, (float)k / 12.12);
        testIter = test.insert(testIter, (float)k / 12.12);
        fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    }
}

TEST(listTest, erase) {
    using type = std::pair<int, bool>;
    std::list<type> norm{{5, 1}, {0, 0}, {3, 1}, {-7, 0}, {8890, 1}, {-123, 0}, {0, 0}, {1, 1}};
    s21::list<type> test{{5, 1}, {0, 0}, {3, 1}, {-7, 0}, {8890, 1}, {-123, 0}, {0, 0}, {1, 1}};
    std::list<type>::iterator normIter = norm.end();
    s21::list<type>::iterator testIter = test.end();
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    while (test.size()) {
        if (testIter != test.end()) {
            normIter = norm.erase(normIter);
            testIter = test.erase(testIter);
        }
        fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
        for (int k = 0; k < 3; k++) {
            testIter++;
            normIter++;
        }
    }
}

TEST(listTest, swap) {
    using type = int;
    std::list<type> norm{1, 2, 3};
    s21::list<type> test{1, 2, 3};
    std::list<type> normSwap{4, 5, 6, 7, 8};
    s21::list<type> testSwap{4, 5, 6, 7, 8};
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(testSwap, normSwap);
    norm.swap(normSwap);
    test.swap(testSwap);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(testSwap, normSwap);
}

TEST(listTest, swap_merge) {
    using type = long double;
    std::list<type> norm{1.111, 2.222, 3.333};
    s21::list<type> test{1.111, 2.222, 3.333};
    std::list<type> normSwap;
    s21::list<type> testSwap;
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    shortListCheck<type>(testSwap, normSwap);
    norm.swap(normSwap);
    test.swap(testSwap);
    shortListCheck<type>(test, norm);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(testSwap, normSwap);
    norm.merge(normSwap);
    test.merge(testSwap);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    shortListCheck<type>(testSwap, normSwap);
}

TEST(listTest, merge) {
    using type = int;
    std::list<type> norm{1, 3, 5, 7, 9};
    s21::list<type> test{1, 3, 5, 7, 9};
    std::list<type> normMerge{-9, -4, -1, 0, 5, 123};
    s21::list<type> testMerge{-9, -4, -1, 0, 5, 123};
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(testMerge, normMerge);
    norm.merge(normMerge);
    test.merge(testMerge);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    shortListCheck<type>(testMerge, normMerge);
}

TEST(listTest, splice) {
    using type = char;
    std::list<type> norm1{'a', 'v', 'm'};
    s21::list<type> test1{'a', 'v', 'm'};
    std::list<type> norm2{'3', '6'};
    s21::list<type> test2{'3', '6'};
    std::list<type> norm3{'&', '@', '(', '\t'};
    s21::list<type> test3{'&', '@', '(', '\t'};
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test1, norm1);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test2, norm2);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test3, norm3);
    std::list<type>::iterator normIter = norm1.end();
    s21::list<type>::iterator testIter = test1.end();
    normIter--;
    testIter--;
    norm1.splice(normIter, norm2);
    test1.splice(testIter, test2);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test1, norm1);
    norm1.splice(norm1.begin(), norm3);
    test1.splice(test1.begin(), test3);
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test1, norm1);
    shortListCheck<type>(test2, norm2);
    shortListCheck<type>(test3, norm3);
}

TEST(listTest, reverse) {
    using type = s21::list<int>;
    std::list<type> norm{{1, 2, 3}, {5, 6}, {0, 0, 0, 0}};
    s21::list<type> test{{1, 2, 3}, {5, 6}, {0, 0, 0, 0}};
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    norm.reverse();
    test.reverse();
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
}

TEST(listTest, unique) {
    using type = std::vector<int>;
    std::list<type> norm{{1, 2}, {0, 0}, {0, 0}, {1}, {2}, {2}, {1, 2}, {0, 0}, {6}, {2}, {2}};
    s21::list<type> test{{1, 2}, {0, 0}, {0, 0}, {1}, {2}, {2}, {1, 2}, {0, 0}, {6}, {2}, {2}};
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    norm.unique();
    test.unique();
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
}

TEST(listTest, sort) {
    using type = int;
    std::list<type> norm{1, 3, 8, 0, -123, -4, 5, 7, 9, -9, -4, -1, 0, 5, 123};
    s21::list<type> test{1, 3, 8, 0, -123, -4, 5, 7, 9, -9, -4, -1, 0, 5, 123};
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    norm.sort();
    test.sort();
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    norm.reverse();
    test.reverse();
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
    norm.sort();
    test.sort();
    fullListCheck<type, s21::list<type>::iterator, std::list<type>::iterator>(test, norm);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}