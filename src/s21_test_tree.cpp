#include <iostream>
#include <map>
#include <string>
#include <utility>

// #include "s21_tree.h"

using namespace std;

// int main() {
//   // pair<int, string>(3, "sobak");
//   TreeNode<std::pair<int, std::string>> a(pair<int, string>(3, "sobak"));
// }

int main() {
  map<int, string> test;
  //   map<int, string> test(pair<int, string>(3, "sobak"));
  // pair<int, string> a(3, "sobak");
  // cout << a.first;
  // test[10] = "lalala";
  // test[3] = "am testing map";

  for (auto x = test.begin(); x != test.end(); ++x) {
    cout << x->first << endl;
  }
  // auto my_it = test.begin();
  // auto my_it1 = ++my_it;

  // if (less<std::pair<int, string>>{}(my_it, my_it1)) {
  //   cout << "false";
  // } else {
  //   cout << "true";
  // }
}