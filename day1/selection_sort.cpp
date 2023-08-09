#include <vector>

using size_t = std::size_t;

template <typename T>
void selection_sort(std::vector<T>& vec)
{
    size_t n = vec.size();

    for (size_t i = 0; i < n - 1; ++i) {
        size_t ind = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (vec[j] < vec[ind]) {
                ind = j;
            }
        }
        T tmp = vec[i];
        vec[i] = vec[ind];
        vec[ind] = tmp;
    }
}
