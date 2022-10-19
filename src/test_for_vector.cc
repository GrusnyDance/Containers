#include "s21_vector.h"
#include "gtest/gtest.h"
#include <string.h>

#define CT std::cout << "            " <<
#define EN std::endl;

template <class T>
using vector = s21::vector<T>;

template <class T>
using original_vector = std::vector<T>;

TEST(vector, constructor) {
    vector<int>a{555, 1, 2, 3, 4};
    vector<int>b(a);

    std::cout << "            a[0] = " << a[0] << std::endl;

    std::cout << "            b[0] = " << b[0] << std::endl;
    
    ASSERT_EQ(a[0], b[0]);
}

TEST(vector, at) {
    vector<int>a{1, 2, 3, 4};
    CT "a.at(3) = " << a.at(3) << EN
    a.at(3) = 5;
    ASSERT_EQ(5, a.at(3));
}

TEST(vector, FrontBack) {
    vector<int>a{1, 2, 3, -555};
    ASSERT_EQ(a.front(), 1);
    ASSERT_EQ(a.back(), -555);
}

TEST(vector, data) {
    vector<int>a{213, 4, 432, 42, 4, 2341};
    CT a.data();
}

TEST(vector, reserve_shrink_to_fit) {
    vector<int>a{1, 2, 3, 4, 5, 6};
    a.reserve(10);
    a[10] = 10;
    CT "THAN = " << a[10] << EN
    ASSERT_EQ(a[10], 10);
    a.shrink_to_fit(3);
    CT "NOW  = " << a[10] << EN
}

TEST(vector, clear) {
    vector<int>a{1, 2, 3, 4, 5, 6};
    vector<int>b{-1, -2, -3, -4, -5, -6};
    for (int i = 0; i < 6; i++) {
        CT "a = " << a[i] << " " << "b =" << b[i] << EN
    }
    CT EN
    a.swap(b);
    for (int i = 0; i < 6; i++) {
        CT "a = " << a[i] << " " << "b =" << b[i] << EN
        ASSERT_TRUE(a[i] < 0);
    }
    a.clear();
    b.clear();
}

TEST(vector, PushPop) {
    vector<int>a;
    a.push_back(5);
    
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
