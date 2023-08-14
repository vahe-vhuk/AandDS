#include <vector>


int max_of_vector(std::vector<int>& vec)
{
    int size = vec.size();
    if (size == 0) {
        throw std::invalid_argument("array must not be empty");
    }
    int max = vec[0];
    for (int i = 1; i < size; ++i) {
        if (vec[i] > max) {
            max = vec[i];
        }
    }
    return max;
}

void counting_sort(std::vector<int>& vec)
{
    int size = vec.size();

    int max = max_of_vector(vec);

    std::vector<int> tmp(max, 0);

    for (int i = 0; i < size; ++i) {
        ++tmp[vec[i]];
    }

    for (int i = 1; i <= max; ++i) {
        tmp[i] += tmp[i - 1];
    }

    std::vector<int> res(size);
    for (int i = 0; i < size; ++i) {
        res[tmp[vec[i]] - 1] = vec[i];
        --tmp[vec[i]];
    }
    
    for (int i = 0; i < size; ++i) {
        vec[i] = res[i];
    }
}





