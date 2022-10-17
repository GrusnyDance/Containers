#ifndef _SRC_S21_SORT_H_
#define _SRC_S21_SORT_H_

template <class iterator, class type>
void swap(iterator a, iterator b) {
    type S = *a;
    *a = *b;
    *b = S;
}

template <class iterator, class type>
iterator partToSort(iterator start, iterator end) {
    iterator point = start;
    while (start != end) {
        if (*start < *end) {
            swap<iterator, type>(start, point);
            point++;
        }
        start++;
    }
    swap<iterator, type>(point, end);
    return point;
}

template <class iterator, class type>
void QSort(iterator start, iterator end) {
    // if (start == end) return;
    iterator next = partToSort<iterator, type>(start, end), prev = next;
    if (start != prev) {
        prev--;
        QSort<iterator, type>(start, prev);
    }
    if (next != end) {
        next++;
        QSort<iterator, type>(next, end);
    }
}

#endif // _SRC_S21_SORT_H_
