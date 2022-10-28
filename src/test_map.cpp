#include <gtest/gtest.h>

#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "s21_map.hpp"

using namespace std;

namespace TestSpace {
// To use a test fixture, derive a class from testing::Test.
class MyTest : public testing::Test {
 protected:  // You should make the members protected s.t. they can be
             // accessed from sub-classes.
  // virtual void SetUp() will be called before each test is run.  You
  // should define it if you need to initialize the variables.
  // Otherwise, this can be skipped.
  void SetUp() override {
    pair<int, string> a(3, "Never gonna give you up");
    pair<int, string> b(7, "Never gonna let you down");
    pair<int, string> c(-1, "Never gonna run around ");
    pair<int, string> d(10, "and desert you");
    pair<int, string> e(-10, "Never gonna make you cry");
    pair<int, string> f(1234, "Never gonna say goodbye");
    pair<int, string> g(12, "Never gonna tell a lie");
    pair<int, string> h(2, "and hurt you");
    myMap1.emplace(a, b, c, d, e, f, g, h);
    origMap.insert(a);
    origMap.insert(b);
    origMap.insert(c);
    origMap.insert(d);
    origMap.insert(e);
    origMap.insert(f);
    origMap.insert(g);
    origMap.insert(h);

    j = make_pair(111, "We're no strangers to love");
    k = make_pair(222, "You know the rules and so do I");
    l = make_pair(-111, "A full commitment's what I'm thinking of");
    m = make_pair(-222, "You wouldn't get this from any other guy");
  }

  // virtual void TearDown() will be called after each test is run.
  // You should define it if there is cleanup work to do.  Otherwise,
  // you don't have to provide it.

  // Declares the variables your tests want to use.
  map<int, string> origMap;
  s21::Map<int, string> myMap1;
  s21::Map<int, string> myMap2;

  pair<int, string> j;
  pair<int, string> k;
  pair<int, string> l;
  pair<int, string> m;
};

TEST_F(MyTest, Emplace) { ASSERT_EQ(myMap1[3], "Never gonna give you up"); }

TEST_F(MyTest, InitializationList) {
  s21::Map<int, string> b = {j, k, l, m};
  map<int, string> a = {j, k, l, m};
  ASSERT_EQ(a.size(), b.size());
}

TEST_F(MyTest, Copy) {
  s21::Map<int, string> b(myMap1);
  ASSERT_EQ(b[1], myMap1[1]);
}

TEST_F(MyTest, Move) {
  s21::Map<int, string> b = std::move(myMap1);
  ASSERT_EQ(b.size(), 8);
  ASSERT_EQ(myMap1.size(), 0);
}

TEST_F(MyTest, Begin) {
  auto it1 = myMap1.begin();
  auto it2 = origMap.begin();
  ASSERT_EQ((*it1).first, (*it2).first);
}

TEST_F(MyTest, End) {
  auto it1 = myMap1.end();
  auto it2 = origMap.end();
  --it1;
  --it2;
  ASSERT_EQ((*it1).first, (*it2).first);
}

TEST_F(MyTest, EmptyAndClear) {
  myMap1.clear();
  s21::Map<int, string> a;
  ASSERT_EQ(myMap1.empty(), a.empty());
}

TEST_F(MyTest, MaxSize) { ASSERT_EQ(myMap1.max_size(), origMap.max_size()); }

TEST_F(MyTest, Insert) {
  size_t size1 = myMap1.size();
  myMap1.insert(j);
  myMap1.insert(123, "lalala");
  size_t size2 = myMap1.size();
  ASSERT_EQ(size2 - size1, 2);
}

TEST_F(MyTest, InsertOrAssign) {
  myMap1.insert_or_assign();
  s21::Map<int, string> a;
  ASSERT_EQ(myMap1.empty(), a.empty());
}

}  // namespace TestSpace

GTEST_API_ int main(int argc, char** argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
