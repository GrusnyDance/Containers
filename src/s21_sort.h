#ifndef _SRC_S21_SORT_H_
#define _SRC_S21_SORT_H_

template <class T, class type>
void swap(T a, T b) {
    type S = *a;
    *a = *b;
    *b = S;
}

template <class T, class type>
T partToSort(T start, T end, int *size) {
    T start_ = start;
    T point = start;
    int k = *size;
    while (k > 0) {
        if (*start_ < *end) {
            swap<T, type>(start_, point);
            point++;
            *size -= 1;
        }
        start_++;
        k--;
    }
    swap<T, type>(point, end);
    return point;
}

template <class T, class type>
void QSort(T start, T end, int size) {
    if (size <= 1) return;
    int R = size;
    T next = partToSort<T, type>(start, end, &R);
    T prev = next;
    next++;
    prev--;
    QSort<T, type>(start, prev, size - R);
    QSort<T, type>(next, end, R - 1);
}

#endif // _SRC_S21_SORT_H_
