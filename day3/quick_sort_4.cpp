#include <vector>
#include <random>

template <typename T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

int random_from_range(int start, int end)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> range(start, end);

    return range(gen);
}

template <typename T>
int partition(std::vector<T>& vec, int start, int end)
{
    int ind = random_from_range(start, end);
    swap(vec[start], vec[ind]);

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




















