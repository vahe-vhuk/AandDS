#include <vector>

using size_t = std::size_t;

template <typename T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
void insertion_sort(std::vector<T>& vec)
{
    size_t n = vec.size();

    for(size_t i = 1; i < n; ++i) {
        size_t j = i - 1;
        T val = vec[i];
        while (vec[j] > vec[j + 1]) {
            swap(vec[j], vec[j + 1]);
            --j;
        }
        vec[j + 1] = val;
    }
}
