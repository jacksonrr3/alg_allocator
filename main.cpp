#include <iostream>
#include <vector>
#include <list>
#include "my_container.h"

#include "allocator_interface.h"

int main() {
/*
    std::list<int, Allocator_Interface<int, linear_alg<100 * sizeof(int)>>> lin;
    for (int i = 0; i < 5; i++) {
        lin.push_back(i);
    }

    std::list<int, Allocator_Interface<int, stack_alg<100 * sizeof(int)>>> sta;
    for (int i = 0; i < 5; i++) {
        sta.push_back(i);
    }
*/
    std::list<std::uint32_t, Allocator_Interface<int, List_alg<int, 100 * sizeof(std::uint32_t)>>> lis;
    for (int i = 0; i < 5; i++) {
        lis.push_back(i);
    }
/*
    std::list<int, Allocator_Interface<int, first_fit<100 * sizeof(int)>>> fir;
    for (int i = 0; i < 5; i++) {
        fir.push_back(i);
    }*/
    return 0;
}