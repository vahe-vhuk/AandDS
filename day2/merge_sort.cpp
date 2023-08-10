#include <vector>

using size_t = std::size_t;

template <typename T>
void merge(std::vector<T>& vec, size_t s, size_t m, size_t e)
{
    size_t s1 = s;
    size_t e1 = m;
    size_t s2 = m + 1;
    size_t e2 = e;

    std::vector<T> tmp(e - s + 1);
    size_t ind = 0;

    while (s1 <= e1 && s2 <= e2) {
        if (vec[s1] <= vec[s2]) {
            tmp[ind++] = vec[s1++];
        }
        else {
            tmp[ind++] = vec[s2++];
        }
    }
    while (s1 <= e1) {
        tmp[ind++] = vec[s1++];
    }
    while (s2 <= e2) {
        tmp[ind++] = vec[s2++];
    }

    for (T i : tmp) {
        vec[s++] = i;
    }
}

template <typename T>
void merge_sort(std::vector<T>& vec, size_t start, size_t end)
{
    if (end <= start) {
        return;
    }
    size_t mid = start + (end - start) / 2;

    merge_sort(vec, start, mid);
    merge_sort(vec, mid + 1, end);
    merge(vec, start, mid, end);
}
