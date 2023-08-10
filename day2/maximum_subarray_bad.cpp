#include <vector>
#include <limits>

using size_t = std::size_t;

template <typename T>
T maximum_subarray(std::vector<T>& vec)
{
    size_t n = vec.size();
    T max_sum = -std::numeric_limits<T>::infinity();
    for (size_t i = 0; i < n; ++i) {
        T sum = -std::numeric_limits<T>::infinity();

        for (size_t j = i; j < n; ++j) {
            sum += vec[j];
            max_sum = std::max(max_sum, sum);
        }
    }
    return max_sum;
}
