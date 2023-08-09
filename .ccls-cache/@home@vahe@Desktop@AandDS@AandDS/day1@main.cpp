#include <iostream>
#include "insertion_sort.cpp"
#include "binary_search.cpp"

int main()
{
    std::vector<int> vec = {1,6,5,9,7,8,4,5,6,3,2,5,6,9,10,22,35,1,4,7,2,0};

    insertion_sort(vec);

    for (auto i : vec) {
        std::cout << i << " ";
    }

    std::cout << "\n" << search_iterative(vec, 15);
    std::cout << search_iterative(vec, 0);
    std::cout << search_iterative(vec, 5);
    std::cout << search_iterative(vec, 35);

}

