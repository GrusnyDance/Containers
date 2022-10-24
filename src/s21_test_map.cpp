#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "map.hpp"

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
  s21::Map<int, string> myMap2;
  pair<int, int> a(3, 100);
  pair<int, int> b(7, 200);
  pair<int, string> c(-1, "lalala");
  pair<int, string> d(10, "hahaha");
  pair<int, string> e(-10, "princess");
  pair<int, string> f(1234, "floppa");
  pair<int, string> g(12, "steppa");
  pair<int, string> h(2, "juice");
  pair<int, string> j(6, "hurricane");

  // test.insert(a);
  // test.insert(b);
  // test.insert(c);
  // cout << "my map   " << myMap.size() << endl;
  // test.insert(d);
  // myMap.insert(a);
  // myMap.insert(b);
  myMap.insert(c);
  myMap.insert(d);
  myMap.insert(e);
  myMap.insert(f);
  myMap.insert(g);
  myMap.insert(h);
  myMap.insert(j);

  // myMap2.insert(c);
  // myMap2.insert(f);
  // myMap2.insert(g);

  // s21::Map<int, string> lala(myMap2);
  // myMap.erase(++it);

  // test.insert(c);
  // test.insert(d);
  // test.insert(e);
  // test.insert(f);
  // test.insert(g);
  // test.insert(h);
  // test.insert(j);
  // cout << myMap.size() << endl;

  for (auto it = myMap.begin(); it != myMap.end(); ++it) {
    myMap.erase(it);
    cout << myMap.size() << endl;
  }

  // cout << myMap.root_->data_.first << endl;

  // for (auto it = test.begin(); it != test.end(); ++it) {
  //   cout << (*it).first << endl;
  // }

  // auto it = myMap.begin();
  // ++it;
  // myMap.erase(it);

  // cout << "my map   " << myMap.at(-10) << endl;
  // cout << "my map   " << myMap.at(7) << endl;
  // cout << "my map   " << myMap.at(-1) << endl;
  // cout << "my map   " << myMap.at(10) << endl;
  // cout << "my map   " << myMap.at(-10) << endl;
  // cout << "my map   " << myMap[12] << endl;
  // cout << "orig map " << test[234] << endl;
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
