#include "../s21_multiset.hpp"
#include <set>

class TestMultiset {
 public:
  // s21::multiset<int> s21_set_empty;
  s21::multiset<int> s21_set_ten{1, 123, 123, 2, 56, 76, 123, 53, 78, 43, 21, 1, 1, 1, 1, 53, 53, 76, 53, 100};
  // std::multiset<int> std_set_ten{1, 123, 123, 2, 56, 76, 123, 53, 78, 43, 21, 1, 1, 1, 1, 53, 53, 76, 53, 100};
  s21::multiset<int> s21_set_copy;
  // std::multiset<int> std_set_copy;
  // s21::multiset<int> s21_move;
  // std::multiset<int> std_move;
  // s21::multiset<int> s21_set_swap{95, 95, 95, 95, 94, 93, 93, 93, 94, 94, 94, 92};
  // std::multiset<int> std_set_swap{95, 95, 95, 95, 94, 93, 93, 93, 94, 94, 94, 92};
  // s21::multiset<int> s21_set_merge{1, 2, 3, 5, 2, 1, 4, 5, 5, 1, 3, 4, 5};
  // std::multiset<int> std_set_merge{1, 2, 3, 5, 2, 1, 4, 5, 5, 1, 3, 4, 5};
  // std::multiset<int> std_set_empty;
};

// TEST(MultisetTest, constructor_initialazer) {
//   TestMultiset tester;

//   EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
//   EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
//   EXPECT_EQ(tester.s21_set_ten.find(1) != tester.s21_set_ten.end(),
//             tester.std_set_ten.find(1) != tester.std_set_ten.end());
//   EXPECT_EQ(tester.s21_set_ten.find(2) != tester.s21_set_ten.end(),
//             tester.std_set_ten.find(2) != tester.std_set_ten.end());
//   EXPECT_EQ(tester.s21_set_ten.find(3) != tester.s21_set_ten.end(),
//             tester.std_set_ten.find(3) != tester.std_set_ten.end());
//   EXPECT_EQ(tester.s21_set_ten.find(4) != tester.s21_set_ten.end(),
//             tester.std_set_ten.find(4) != tester.std_set_ten.end());
// }

// TEST(MultisetTest, constructor_default) {
//   TestMultiset tester;
//   EXPECT_EQ(tester.s21_set_empty.size(), tester.std_set_empty.size());
//   EXPECT_EQ(tester.s21_set_empty.empty(), tester.std_set_empty.empty());
// }

// TEST(MultisetTest, constructor_copy) {
//   TestMultiset tester;
//   s21::multiset<int> s21_empty(tester.s21_set_ten);
//   std::multiset<int> std_empty(tester.std_set_ten);
//   EXPECT_EQ(s21_empty.find(1) != s21_empty.end(),
//             std_empty.find(1) != std_empty.end());
//   EXPECT_EQ(s21_empty.find(2) != s21_empty.end(),
//             std_empty.find(2) != std_empty.end());
//   EXPECT_EQ(s21_empty.find(3) != s21_empty.end(),
//             std_empty.find(3) != std_empty.end());
//   EXPECT_EQ(s21_empty.find(4) != s21_empty.end(),
//             std_empty.find(4) != std_empty.end());
//   EXPECT_EQ(s21_empty.size(), std_empty.size());
//   EXPECT_EQ(s21_empty.empty(), std_empty.empty());
// }

// TEST(MultisetTest, construct_move) {
//   TestMultiset tester;
//   s21::multiset<int> s21_move = std::move(tester.s21_set_ten);
//   std::multiset<int> std_move = std::move(tester.std_set_ten);
//   EXPECT_EQ(s21_move.find(1) != s21_move.end(),
//             std_move.find(1) != std_move.end());
//   EXPECT_EQ(s21_move.find(2) != s21_move.end(),
//             std_move.find(2) != std_move.end());
//   EXPECT_EQ(s21_move.find(3) != s21_move.end(),
//             std_move.find(3) != std_move.end());
//   EXPECT_EQ(s21_move.find(4) != s21_move.end(),
//             std_move.find(4) != std_move.end());
//   EXPECT_EQ(s21_move.size(), std_move.size());
//   EXPECT_EQ(s21_move.empty(), std_move.empty());
// }

// TEST(MultisetTest, operator_move) {
//   TestMultiset tester;
//   tester.s21_move = std::move(tester.s21_set_ten);
//   tester.std_move = std::move(tester.std_set_ten);
//   EXPECT_EQ(tester.s21_move.find(1) != tester.s21_move.end(),
//             tester.std_move.find(1) != tester.std_move.end());
//   EXPECT_EQ(tester.s21_move.find(2) != tester.s21_move.end(),
//             tester.std_move.find(2) != tester.std_move.end());
//   EXPECT_EQ(tester.s21_move.find(3) != tester.s21_move.end(),
//             tester.std_move.find(3) != tester.std_move.end());
//   EXPECT_EQ(tester.s21_move.find(4) != tester.s21_move.end(),
//             tester.std_move.find(4) != tester.std_move.end());
//   EXPECT_EQ(tester.s21_move.size(), tester.std_move.size());
//   EXPECT_EQ(tester.s21_move.empty(), tester.std_move.empty());
// }

TEST(MultisetTest, operator_copy) {
  TestMultiset tester;
  tester.s21_set_copy = tester.s21_set_ten;
  // tester.std_set_copy = tester.std_set_ten;
  std::cout <<  std::endl;

  // for (auto it : tester.s21_set_copy) {
  //   std::cout << it << " " << std::endl;
  // }
  // EXPECT_EQ(tester.s21_set_copy.find(1) != tester.s21_set_copy.end(),
  //           tester.std_set_copy.find(1) != tester.std_set_copy.end());
  // EXPECT_EQ(tester.s21_set_copy.find(2) != tester.s21_set_copy.end(),
  //           tester.std_set_copy.find(2) != tester.std_set_copy.end());
  // EXPECT_EQ(tester.s21_set_copy.find(3) != tester.s21_set_copy.end(),
  //           tester.std_set_copy.find(3) != tester.std_set_copy.end());
  // EXPECT_EQ(tester.s21_set_copy.find(4) != tester.s21_set_copy.end(),
  //           tester.std_set_copy.find(4) != tester.std_set_copy.end());
  // EXPECT_EQ(tester.s21_set_copy.size(), tester.std_set_copy.size());
  // EXPECT_EQ(tester.s21_set_copy.empty(), tester.std_set_copy.empty());
}

// TEST(MultisetTest, function_not_empty) {
//   TestMultiset tester;
//   EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
//   EXPECT_EQ(tester.s21_set_ten.empty(), tester.std_set_ten.empty());
// }

// TEST(MultisetTest, function_empty) {
//   TestMultiset tester;
//   EXPECT_EQ(tester.s21_set_empty.size(), tester.std_set_empty.size());
//   EXPECT_EQ(tester.s21_set_empty.empty(), tester.std_set_empty.empty());
// }

// TEST(MultisetTest, function_size_empty) {
//   TestMultiset tester;
//   EXPECT_EQ(tester.s21_set_empty.size(), tester.std_set_empty.size());
// }

// TEST(MultisetTest, function_size_not_empty) {
//   TestMultiset tester;
//   EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
// }

// TEST(MultisetTest, function_max_size_empty) {
//   TestMultiset tester;
//   EXPECT_EQ(tester.s21_set_empty.max_size(), tester.std_set_empty.max_size());
// }

// TEST(MultisetTest, function_max_size_not_empty) {
//   TestMultiset tester;
//   EXPECT_EQ(tester.s21_set_ten.max_size(), tester.std_set_ten.max_size());
// }

// TEST(MultisetTest, function_max_size_float_empty) {
//   s21::multiset<float> s21_float_empty;
//   std::multiset<float> std_float_empty;
//   EXPECT_EQ(s21_float_empty.max_size(), std_float_empty.max_size());
// }

// TEST(MultisetTest, function_swap_not_empty) {
//   TestMultiset tester;
//   tester.s21_set_swap.swap(tester.s21_set_ten);
//   tester.std_set_swap.swap(tester.std_set_ten);
//   EXPECT_EQ(tester.s21_set_swap.find(1) != tester.s21_set_swap.end(),
//             tester.std_set_swap.find(1) != tester.std_set_swap.end());
//   EXPECT_EQ(tester.s21_set_swap.find(56) != tester.s21_set_swap.end(),
//             tester.std_set_swap.find(56) != tester.std_set_swap.end());
//   EXPECT_EQ(tester.s21_set_swap.find(76) != tester.s21_set_swap.end(),
//             tester.std_set_swap.find(76) != tester.std_set_swap.end());
//   EXPECT_EQ(tester.s21_set_ten.find(95) != tester.s21_set_ten.end(),
//             tester.std_set_ten.find(95) != tester.std_set_ten.end());
//   EXPECT_EQ(tester.s21_set_ten.find(94) != tester.s21_set_ten.end(),
//             tester.std_set_ten.find(94) != tester.std_set_ten.end());
//   EXPECT_EQ(tester.s21_set_ten.find(93) != tester.s21_set_ten.end(),
//             tester.std_set_ten.find(93) != tester.std_set_ten.end());
//   EXPECT_EQ(tester.s21_set_swap.size(), tester.std_set_swap.size());
//   EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
// }

// TEST(MultisetTest, function_swap_empty) {
//   TestMultiset tester;
//   tester.s21_set_empty.swap(tester.s21_set_swap);
//   tester.std_set_empty.swap(tester.std_set_swap);

//   EXPECT_EQ(tester.s21_set_empty.find(95) != tester.s21_set_empty.end(),
//             tester.std_set_empty.find(95) != tester.std_set_empty.end());
//   EXPECT_EQ(tester.s21_set_empty.find(94) != tester.s21_set_empty.end(),
//             tester.std_set_empty.find(94) != tester.std_set_empty.end());
//   EXPECT_EQ(tester.s21_set_empty.find(93) != tester.s21_set_empty.end(),
//             tester.std_set_empty.find(93) != tester.std_set_empty.end());

//   EXPECT_EQ(tester.s21_set_empty.size(), tester.std_set_empty.size());
//   EXPECT_EQ(tester.s21_set_empty.empty(), tester.std_set_empty.empty());
//   EXPECT_EQ(tester.s21_set_swap.size(), tester.std_set_swap.size());
//   EXPECT_EQ(tester.s21_set_swap.empty(), tester.std_set_swap.empty());
// }

// TEST(MultisetTest, function_merge_with_duplicates) {
//   TestMultiset tester;
//   tester.s21_set_merge.merge(tester.s21_set_ten);
//   tester.std_set_merge.merge(tester.std_set_ten);

//   EXPECT_EQ(tester.s21_set_merge.find(1) != tester.s21_set_merge.end(),
//             tester.std_set_merge.find(1) != tester.std_set_merge.end());
//   EXPECT_EQ(tester.s21_set_merge.find(2) != tester.s21_set_merge.end(),
//             tester.std_set_merge.find(2) != tester.std_set_merge.end());
//   EXPECT_EQ(tester.s21_set_merge.find(76) != tester.s21_set_merge.end(),
//             tester.std_set_merge.find(76) != tester.std_set_merge.end());

//   EXPECT_EQ(tester.s21_set_merge.size(), tester.std_set_merge.size());
//   EXPECT_EQ(tester.std_set_merge.empty(), tester.std_set_merge.empty());
// }

// TEST(MultisetTest, function_merge_wihout_duplicates) {
//   TestMultiset tester;
//   tester.s21_set_ten.merge(tester.s21_set_swap);
//   tester.std_set_ten.merge(tester.std_set_swap);

//   EXPECT_EQ(tester.s21_set_ten.find(95) != tester.s21_set_ten.end(),
//             tester.std_set_ten.find(95) != tester.std_set_ten.end());
//   EXPECT_EQ(tester.s21_set_ten.find(1) != tester.s21_set_ten.end(),
//             tester.std_set_ten.find(1) != tester.std_set_ten.end());
//   EXPECT_EQ(tester.s21_set_ten.find(94) != tester.s21_set_ten.end(),
//             tester.std_set_ten.find(94) != tester.std_set_ten.end());
//   EXPECT_EQ(tester.s21_set_ten.find(76) != tester.s21_set_ten.end(),
//             tester.std_set_ten.find(76) != tester.std_set_ten.end());

//   EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
//   EXPECT_EQ(tester.std_set_ten.empty(), tester.std_set_ten.empty());
//   EXPECT_EQ(tester.s21_set_swap.size(), tester.std_set_swap.size());
//   EXPECT_EQ(tester.s21_set_swap.empty(), tester.std_set_swap.empty());
// }

// TEST(MultisetTest, function_clear_not_empty) {
//   TestMultiset tester;
//   tester.s21_set_ten.clear();
//   tester.std_set_ten.clear();
//   EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
//   EXPECT_EQ(tester.s21_set_ten.empty(), tester.std_set_ten.empty());
// }

// TEST(MultisetTest, function_clear_empty) {
//   TestMultiset tester;
//   tester.s21_set_empty.clear();
//   tester.std_set_empty.clear();
//   EXPECT_EQ(tester.s21_set_empty.size(), tester.std_set_empty.size());
//   EXPECT_EQ(tester.std_set_empty.empty(), tester.std_set_empty.empty());
// }

// TEST(MultisetTest, function_begin_not_empty) {
//   TestMultiset tester;
//   s21::multiset<int>::iterator i = tester.s21_set_ten.begin();
//   std::multiset<int>::iterator j = tester.std_set_ten.begin();
//   EXPECT_EQ(*i, *j);
// }

// TEST(MultisetTest, function_begin_empty) {  // удалить, валгринд ругается на
// неинициализированные данные
//   TestMultiset tester;
//   s21::multiset<int>::iterator i = tester.s21_set_empty.begin();
//   std::multiset<int>::iterator j = tester.std_set_empty.begin();
//   EXPECT_EQ(*i, *j);
// }

// TEST(MultisetTest, function_const_begin_not_empty) {
//   TestMultiset tester;
//   s21::multiset<int>::const_iterator i = tester.s21_set_ten.cbegin();
//   std::multiset<int>::const_iterator j = tester.std_set_ten.cbegin();
//   EXPECT_EQ(*i, *j);
// }

// TEST(MultisetTest, function_const_begin_empty) {  // удалить, валгринд ругается на
// неинициализированные данные
//   TestMultiset tester;
//   s21::multiset<int>::const_iterator i = tester.s21_set_empty.cbegin();
//   std::multiset<int>::const_iterator j = tester.std_set_empty.cbegin();
//   EXPECT_EQ(*i, *j);
// }

// TEST(MultisetTest, function_end_not_empty) {
//   TestMultiset tester;
//   s21::multiset<int>::iterator i = tester.s21_set_ten.end();
//   std::multiset<int>::iterator j = tester.std_set_ten.end();
//   --i;
//   --j;
//   EXPECT_EQ(*i, *j);
// }

// TEST(MultisetTest, function_end_empty) {  // удалить, валгринд ругается на
// неинициализированные данные
//   TestMultiset tester;
//   s21::multiset<int>::iterator i = tester.s21_set_empty.end();
//   std::multiset<int>::iterator j = tester.std_set_empty.end();
//   EXPECT_EQ(*i, *j);
// }

// TEST(MultisetTest, function_const_end_empty) {  // удалить, валгринд ругается на
// неинициализированные данные
//   TestMultiset tester;
//   s21::multiset<int>::const_iterator i = tester.s21_set_empty.cend();
//   std::multiset<int>::const_iterator j = tester.std_set_empty.cend();
//   EXPECT_EQ(*i, *j);
// }

// TEST(MultisetTest, operator_plus) {
//   TestMultiset tester;
//   s21::multiset<int>::iterator i = tester.s21_set_ten.begin();
//   std::multiset<int>::iterator j = tester.std_set_ten.begin();
//   while (i != tester.s21_set_ten.end() && j != tester.std_set_ten.end()) {
//     EXPECT_EQ(*i, *j);
//     ++i;
//     ++j;
//   }
//   EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
//   EXPECT_EQ(tester.std_set_ten.empty(), tester.std_set_ten.empty());
// }

// TEST(MultisetTest, operator_minus) {
//   TestMultiset tester;
//   s21::multiset<int>::iterator i = tester.s21_set_ten.end();
//   std::multiset<int>::iterator j = tester.std_set_ten.end();
//   while (i != tester.s21_set_ten.begin() && j != tester.std_set_ten.begin())
//   {
//     --i;
//     --j;
//     EXPECT_EQ(*i, *j);
//   }
//   EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
//   EXPECT_EQ(tester.s21_set_ten.empty(), tester.std_set_ten.empty());
// }

// TEST(MultisetTest, operation_assignment) {
//   TestMultiset tester;
//   s21::multiset<int>::iterator iter_1 = tester.s21_set_ten.begin();
//   s21::multiset<int>::iterator iter_3 = iter_1;
//   std::multiset<int>::iterator iter_2 = tester.std_set_ten.begin();
//   std::multiset<int>::iterator iter_4 = iter_2;
//   ASSERT_EQ(*iter_1, *iter_3);
//   ASSERT_EQ(*iter_2, *iter_4);
// }

// TEST(MultisetTest, operation_equal) {
//   TestMultiset tester;
//   s21::multiset<int>::iterator it1 = tester.s21_set_ten.begin();
//   s21::multiset<int>::iterator it3 = tester.s21_set_ten.begin();
//   std::multiset<int>::iterator it2 = tester.std_set_ten.begin();
//   std::multiset<int>::iterator it4 = tester.std_set_ten.begin();
//   ASSERT_EQ(it1 == it3, it2 == it4);
// }

// TEST(MultisetTest, operation_not_equal) {
//   TestMultiset tester;
//   s21::multiset<int>::iterator iter_1 = tester.s21_set_ten.begin();
//   std::multiset<int>::iterator iter_2 = tester.std_set_ten.begin();
//   ASSERT_EQ(iter_1 != tester.s21_set_ten.end(),
//             iter_2 != tester.std_set_ten.end());
// }

// TEST(MultisetTest, function_insert) {
//   TestMultiset tester;
//   std::pair<s21::multiset<int>::iterator, bool> iter_1 =
//       tester.s21_set_ten.insert(45);
//   std::pair<std::multiset<int>::iterator, bool> iter_2 =
//       tester.std_set_ten.insert(45);
//   EXPECT_EQ(*(iter_1.first), *(iter_2.first));
//   EXPECT_EQ(iter_1.second, iter_2.second);
// }

// TEST(MultisetTest, function_find_have) {
//   TestMultiset tester;
//   s21::multiset<int>::iterator i = tester.s21_set_ten.find(1);
//   std::multiset<int>::iterator j = tester.std_set_ten.find(1);
//   EXPECT_EQ(i != tester.s21_set_ten.end(), j != tester.std_set_ten.end());
// }

// TEST(MultisetTest, function_find_dont_have) {
//   TestMultiset tester;
//   s21::multiset<int>::iterator i = tester.s21_set_ten.find(100);
//   std::multiset<int>::iterator j = tester.std_set_ten.find(100);
//   EXPECT_EQ(i == tester.s21_set_ten.end(), j == tester.std_set_ten.end());
// }

// TEST(MultisetTest, function_erase) {
//   TestMultiset tester;
//   tester.s21_set_ten.erase(tester.s21_set_ten.begin());
//   tester.std_set_ten.erase(tester.std_set_ten.begin());
//   s21::multiset<int>::iterator iter_1 = tester.s21_set_ten.find(1);
//   std::multiset<int>::iterator iter_2 = tester.std_set_ten.find(1);
//   ASSERT_EQ(iter_1 == tester.s21_set_ten.end(),
//             iter_2 == tester.std_set_ten.end());
// }

// TEST(MultisetTest, functions_erase_alot) {
//   TestMultiset tester;

//   s21::multiset<int>::iterator it1 = tester.s21_set_ten.find(76);
//   std::multiset<int>::iterator it2 = tester.std_set_ten.find(76);
//   tester.s21_set_ten.erase(it1);
//   tester.std_set_ten.erase(it2);
//   EXPECT_EQ(tester.s21_set_ten.find(76) == tester.s21_set_ten.end(),
//           tester.std_set_ten.find(76) == tester.std_set_ten.end());
//   ASSERT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());

//   it1 = tester.s21_set_ten.find(123);
//   it2 = tester.std_set_ten.find(123);
//   tester.s21_set_ten.erase(it1);
//   tester.std_set_ten.erase(it2);
//   EXPECT_EQ(tester.s21_set_ten.find(123) == tester.s21_set_ten.end(),
//           tester.std_set_ten.find(123) == tester.std_set_ten.end());
//   ASSERT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());

//   it1 = tester.s21_set_ten.find(43);
//   it2 = tester.std_set_ten.find(43);
//   tester.s21_set_ten.erase(it1);
//   tester.std_set_ten.erase(it2);
//   EXPECT_EQ(tester.s21_set_ten.find(43) == tester.s21_set_ten.end(),
//           tester.std_set_ten.find(43) == tester.std_set_ten.end());
//   ASSERT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());

//   it1 = tester.s21_set_ten.find(2);
//   it2 = tester.std_set_ten.find(2);
//   tester.s21_set_ten.erase(it1);
//   tester.std_set_ten.erase(it2);
//   EXPECT_EQ(tester.s21_set_ten.find(2) == tester.s21_set_ten.end(),
//           tester.std_set_ten.find(2) == tester.std_set_ten.end());
//   ASSERT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
// }
