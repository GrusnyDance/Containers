#ifndef _SRC_S21_SORT_HPP_
#define _SRC_S21_SORT_HPP_

namespace s21 {

template <class iterator>
void swap(iterator a, iterator b) {
  auto S = *a;
  *a = *b;
  *b = S;
}

template <class iterator>
iterator partToSort(iterator start, iterator end) {
  iterator point = start;
  while (start != end) {
    if (*start < *end) {
      swap<iterator>(start, point);
      point++;
    }
    start++;
  }
  swap<iterator>(point, end);
  return point;
}

template <class iterator>
void QSort(iterator start, iterator end) {
  // if (start == end) return;
  iterator next = partToSort<iterator>(start, end), prev = next;
  if (start != prev) {
    prev--;
    QSort<iterator>(start, prev);
  }
  if (next != end) {
    next++;
    QSort<iterator>(next, end);
  }
}

}  // namespace s21

#endif  // _SRC_S21_SORT_HPP_
