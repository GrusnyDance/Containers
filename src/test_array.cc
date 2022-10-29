#include <array>
#include <iostream>

#include "s21_array.h"

using namespace std;

int main() {
  array<int, 5> a = {1, 2, 3};
  array<int, 5> b = {4, 5, 6};
  //   array<int, 3> a;
  s21::Array<int, 7> c = {7, 6, 5, 4, 3};
  s21::Array<int, 7> d = {-7, -6, -5, -4, -3};
  //   s21::Array<int, 2> b;
  a.fill(1);
  c.fill(2);

  for (auto i : a) {
    cout << i << "  ";
  }
  cout << endl;

  for (auto i : c) {
    cout << i << "  ";
  }

  //   cout << a[1] << endl;
  //   cout << b[1] << endl;

  //   cout << a.max_size();
  //   for (int i = 0; i < 5; i++) {
  //     cout << a[i] << " ";
  //   }

  return 0;
}