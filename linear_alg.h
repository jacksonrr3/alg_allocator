#pragma once

template<int N>
class linear_alg {

public:
	
	linear_alg():_free_size(N) {
		_data = reinterpret_cast<char*>(std::malloc(N));
		_ptr = _data;
	}

	~linear_alg() {
		std::free(_data);
	};

	char* allocate(std::size_t n) {
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		if ((n > _free_size) || (!_data)) { throw std::bad_alloc(); }
		char * res = _ptr;
		_ptr = _ptr + n;
		_free_size -= n;
		return res;
	}

	void deallocate([[maybe_unused]] char* p, [[maybe_unused]] std::size_t n) const {
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
	}

private:
	std::size_t _free_size;
	char* _ptr;
	char* _data;  
};