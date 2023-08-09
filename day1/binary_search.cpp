#include <vector>

using size_t = std::size_t;

template <typename T>
bool is_sorted(std::vector<T>& vec)
{
    size_t n = vec.size();
    if (n < 2) {
        return true;
    }

    for (size_t i = 0; i < n - 1; ++i) {
        if (vec[i] > vec[i + 1]) {
            return false;
        }
    }
    return true;
}

template <typename T>
int search_rec(std::vector<T>& vec, size_t start, size_t end, T target)
{
    if (start > end) {
        return -1;
    }
    size_t mid = start + (end - start) / 2;
    if (vec[mid] == target) {
        return mid;
    }
    if (vec[mid] < target) {
        return search(vec, mid + 1, end, target);
    }
    else {
        return search(vec, start, mid-1, target);
    }
}

template <typename T>
int search_recursive(std::vector<T>& vec, T target)
{
    if (!is_sorted(vec)) {
        throw std::invalid_argument("vector not sorted");
    }
    return search_rec(vec, 0, vec.size() - 1, target);
}

template <typename T>
int search_iterative(std::vector<T>& vec, T target)
{
    if (!is_sorted(vec)) {
        throw std::invalid_argument("vector not sorted");
    }
    size_t start = 0;
    size_t end = vec.size();
    
    while (start < end) {
        size_t mid = start + (end - start) / 2;

        if (vec[mid] == target) {
            return mid;
        }
        if (vec[mid] > target) {
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }
    return -1;
}

















