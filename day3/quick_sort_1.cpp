#include <vector>


template <typename T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
int partition(std::vector<T>& vec, int start, int end)
{
    int i = start + 1;
    int j = end;

    while (i < j) {
        while (vec[i] <= vec[start]) {
            ++i;
        }
        while (vec[j] > vec[start]) {
            --j;
        }
        if (i < j) {
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[j], vec[start]);
    return j;
}

template <typename T>
void quick_sort(std::vector<T>& vec, int start, int end)
{
    if (start < end) {
        int p_index = partition(vec, start, end);

        quick_sort(vec, start, p_index - 1);
        quick_sort(vec, p_index + 1, end);
    }
}




















