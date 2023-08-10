#include <vector>
#include <limits>

using size_t = std::size_t;

template <typename T>
T max(const T& a, const T& b, const T& c)
{
    return std::max(std::max(a, b), c);
}


template <typename T>
T max_crossing_sum(std::vector<T>& vec, int s, int m, int e)
{
    T sum = 0;
    T left_sum = -std::numeric_limits<T>::infinity();
    for (int i = m; i >= s; --i) {
        sum += vec[i];
        if (sum > left_sum) {
            left_sum = sum;
        }
    }
    sum = 0;
    T right_sum = -std::numeric_limits<T>::infinity();
    for (int i = m; i <= e; ++i) {
        sum += vec[i];
        if (sum > right_sum) {
            right_sum = sum;
        }
    }

    return max(left_sum + right_sum - vec[m], left_sum, right_sum);
}


template <typename T>
T maximum_subarray(std::vector<T>& vec, int start, int end)
{
    if (end < start) {
        return -std::numeric_limits<T>::infinity();
    }

    if (start == end) {
        return vec[start];
    }

    int mid = start + (end - start) / 2;

    return max(maximum_subarray(vec, start, mid - 1),
               maximum_subarray(vec, mid + 1, end),
               max_crossing_sum(vec, start, mid, end));
}










