#include <vector>


void counting_sort_by_order(std::vector<int>& vec, int order)
{
    int size = vec.size();


    std::vector<int> tmp(10, 0);

    for (int i = 0; i < size; ++i) {
        int val = (vec[i] / order) % 10;
        ++tmp[val];
    }

    for (int i = 1; i < 10; ++i) {
        tmp[i] += tmp[i - 1];
    }

    std::vector<int> res(size);
    for (int i = size - 1; i >= 0; --i) {
        int val = (vec[i] / order) % 10;
        res[tmp[val] - 1] = vec[i];
        --tmp[val];
    }
    
    for (int i = 0; i < size; ++i) {
        vec[i] = res[i];
    }
}

int max_of_array(std::vector<int>& vec)
{
    int size = vec.size();
    if (size == 0) {
        throw std::invalid_argument("array must not be empty");
    }
    int max = vec[0];
    for (int i = 0; i < size; ++i) {
        if (vec[i] > max) {
            max = vec[i];
        }
    }
    return max;
}

void radix_sort(std::vector<int>& vec)
{
    int max = max_of_array(vec);

    for (int order = 1; max / order > 0; order *= 10) {
        counting_sort_by_order(vec, order);
    } 
}



