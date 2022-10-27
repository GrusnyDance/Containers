#include <array>
#include <iostream>

using namespace std;

int main() {
  array<int, 5> a = {1, 2, 3};
  array<int, 3> b = {7, 6, 5, 4, 3, 2, 1};

  a.swap(7);

  //   cout << a.max_size();
  //   for (int i = 0; i < 5; i++) {
  //     cout << a[i] << " ";
  //   }

  return 0;
}