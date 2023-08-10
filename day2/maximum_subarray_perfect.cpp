#include <vector>

using size_t = std::size_t;

template <typename T>
T maximum_subarray(std::vector<T>& vec)
{
    T sum = vec[0];
    T max_sum = vec[0];
    for (const T& elem : vec) {
        sum = std::max(elem, sum + elem);
        max_sum = std::max(max_sum, sum);
    }
    return max_sum;
}
