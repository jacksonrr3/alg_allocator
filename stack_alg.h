#pragma once
#include <list>

template<int N>
class stack_alg {


public:

	stack_alg() :_free_size(N) {
		_data = reinterpret_cast<char*>(std::malloc(N));
		_ptr = _data;
		_data_end = _data + N;
	}

	~stack_alg() {
		std::free(_data);
	};

	char* allocate(std::size_t n) {
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		if ((n > _free_size) || (!_data)) { throw std::bad_alloc(); }
		
		*((std::size_t*)_ptr) = n;
		_ptr += 2;
		char* res = _ptr;
		_ptr = _ptr + n;
		_free_size -= n + 2;
		return res;
	}

	void deallocate([[maybe_unused]] char* p, [[maybe_unused]] std::size_t n) {
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		if (p < _data || p >= _data_end) { throw std::bad_alloc(); }
		std::size_t size = (std::size_t)(p - 2);
		_ptr = p - 2;
		_free_size += (size + 2);


	}

private:
	std::size_t _free_size;
	char* _ptr;
	char* _data;
	char* _data_end;
};