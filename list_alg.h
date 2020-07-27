#pragma once

template<typename T, int N> //T - ��� ���������, N - ���������� ���������
class List_alg {


public:

	List_alg() :_free_size(N) {
		_data = reinterpret_cast<std::uint8_t*>(std::malloc(N * (sizeof(T))));
		//_end_data = _data + N;
		for (int i = 0; i < N - 1; i++) {
			std::uint8_t* temp = _data + (i * sizeof(T));
			*((std::uint8_t**)temp) = temp + sizeof(T);
		}
		*((std::uint8_t**)&_data[(N - 1) * sizeof(T)]) = nullptr; /* terminating NULL */
		_head = _data;
	
	}

	~List_alg() {
		std::free(_data);
	};

	T* allocate(std::size_t n) {
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		if (!_free_size || !_head || _data) { throw std::bad_alloc(); }
		T* res = reinterpret_cast<T*>(_head);
		_head = (*((uint8_t**)(_head)));
		_free_size -= 1;
		return res;
	}

	void deallocate([[maybe_unused]] void* p, [[maybe_unused]] std::size_t n) {
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		if (!p) { return; }
		if ((std::uint8_t*)p < _data || 
			(std::uint8_t*)p > _data + N * sizeof(T)) {
			return;
		}
		*((uint8_t**)p) = _head;
		_head = (uint8_t*)p;
		return;

	}

private:
	std::size_t _free_size;
	//std::uint8_t* _end_data;
	std::uint8_t* _head;
	std::uint8_t* _data;
};
