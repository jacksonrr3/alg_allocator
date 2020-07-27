
#ifndef UNTITLED_TEST_MY_ALLOCATOR_H
#define UNTITLED_TEST_MY_ALLOCATOR_H

#pragma once
#include <list>

template<int N>
class block_alg {

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
  
    block_alg() :_data() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    block_alg(block_alg&& other) :_data(std::move(other._data)) {}

    ~block_alg() {
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