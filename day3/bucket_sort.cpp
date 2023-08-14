#include <vector>
#include "quick_sort_3.cpp"

void bucket_sort(std::vector<double>& vec)
{
    int size = vec.size();
    int bucket_size = 10;

    std::vector<std::vector<double>> bucket(bucket_size);

    for (int i = 0; i < size; ++i) {
        int ind = vec[i] * bucket_size;
        bucket[ind].push_back(vec[i]);
    }
    
    for (int i = 0; i < bucket_size; ++i) {
        quick_sort(bucket[i], 0, bucket[i].size() - 1);
    }

    int ind = 0;
    for (auto i : bucket) {
        for (auto j : i) {
            vec[ind++] = j;
        }
    }

}

