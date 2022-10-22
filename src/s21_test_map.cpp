#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "s21_map.h"

using namespace std;

// int main() {
//   // pair<int, string>(3, "sobak");
//   TreeNode<std::pair<int, std::string>> a(pair<int, string>(3, "sobak"));
// }

int main() {
  // map<int, int> test;
  // s21::Map<int, int> myMap;

  map<int, string> test;
  s21::Map<int, string> myMap;
  pair<int, int> a(3, 100);
  pair<int, int> b(7, 200);
  pair<int, string> c(-1, "lalala");
  pair<int, string> d(10, "hahaha");
  pair<int, string> e(-10, "princess");

  // test.insert(a);
  // test.insert(b);
  test.insert(c);
  test.insert(d);
  // myMap.insert(a);
  // myMap.insert(b);
  myMap.insert(c);
  myMap.insert(d);
  // myMap.insert(e);

  // cout << "my map   " << myMap.at(50) << endl;
  // cout << "my map   " << myMap.at(7) << endl;
  // cout << "my map   " << myMap.at(-1) << endl;
  // cout << "my map   " << myMap.at(10) << endl;
  // cout << "my map   " << myMap.at(-10) << endl;
  cout << "my map   " << myMap[12] << endl;
  cout << "orig map " << test[234] << endl;
  // myMap.clear();
  // cout << "my map   " << myMap.size() << endl;

  // cout << "orig map " << test.at(3) << endl;
  // cout << "orig map " << test.size() << endl;
  // cout << "orig map " << test.max_size() << endl;

  // map<int, string> test(pair<int, string>(3, "sobak"));
  // pair<int, string> a(3, "sobak");
  // cout << a.first;
  // test[10] = "lalala";
  // test[3] = "am testing map";
  // cout << test.size();
  // test.insert_or_assign(3, "sobak");
  // test.insert(3, "sobak");

  // cout << test[3];
  // cout << test.size();
  // cout << test.max_size();

  // for (auto x = test.begin(); x != test.end(); ++x) {
  //   cout << x->first << endl;
  // }
  // auto my_it = test.begin();
  // auto my_it1 = ++my_it;

  // if (less<std::pair<int, string>>{}(my_it, my_it1)) {
  //   cout << "false";
  // } else {
  //   cout << "true";
  // }
}
