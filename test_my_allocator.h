//
// Created by evgeniy on 23.07.2020.
//

#ifndef UNTITLED_TEST_MY_ALLOCATOR_H
#define UNTITLED_TEST_MY_ALLOCATOR_H

#pragma once
#include <list>

template<int N>
class my_allocator {

    //вспомогательная структура одного блока аллоцированных данных
    //template <typename U>
    struct alloc_part {
        std::size_t _size = 0;		// количество занятых участков
        char* _array;			// указатель на область памяти

        alloc_part(size_t n) {		//конструктор, вызов malloc
            _array = reinterpret_cast<char*>(std::malloc(n * sizeof(char)));
        }

        ~alloc_part() {    		//деструктор, освобождение выделенного блока памяти
            std::free(_array);
        }
    };

public:
    /*
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = my_allocator<U, N>;
    };
*/

    my_allocator() :_data() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    my_allocator(my_allocator&& other):_data(std::move(other._data)) {}

    ~my_allocator() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    };

    char* allocate(std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        if (n > N) { throw std::bad_alloc(); }
        if (_data.empty() || size_less_n(n)) {
            _data.emplace_back(N);
        }
        return alloc_t(n);
    }

    void deallocate([[maybe_unused]] char* p, [[maybe_unused]] std::size_t n) const {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args&&...args) const {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    };

    template <typename U>
    void destroy(U* p) const {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~U();
    }

private:

    bool size_less_n(std::size_t n) {
        return _data.back()._size + n > N;
    }

    char* alloc_t(std::size_t n) {
        char* ret = (_data.back()._array) + _data.back()._size;
        _data.back()._size += n;
        return ret;
    }

    std::list<alloc_part> _data;  //контейнер для хранения объектов аллоцированных блоков памяти
};
#endif //UNTITLED_TEST_MY_ALLOCATOR_H
