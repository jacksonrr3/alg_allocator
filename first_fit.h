#pragma once
#include <list>

template<int N>
class first_fit {

	struct Header {
		Header* _parent;
		Header* _next;
		unsigned int _size;
		bool _is_free = true;

		void set(Header* p, Header* n, std::size_t size, bool free = true) {
			_parent = p;
			_next = n;
			_size = size;
			_is_free = free;
		}


	};

public:

	first_fit() {
		char * _data = reinterpret_cast<char*>(std::malloc(N));
		_main_ptr = (Header*)_data;
		_last_ptr = (Header*)((char*)_data + N - sizeof(Header));

		_last_ptr->set(_main_ptr, nullptr, 0, false);
		_main_ptr->set(_main_ptr, _last_ptr, N - sizeof(Header));
	}

	~first_fit() {
		std::free(_data);
	};

	char* allocate(std::size_t n) {
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		Header* temp = _main_ptr;
		Header* res = nullptr;

		while (temp != _last_ptr) {
			if (temp->_is_free) {
				long int temp_size = temp->_size - 2 * sizeof(Header);
				if (temp_size > 0 && temp_size > n) {
					res = temp;
					temp = temp->_next;
					break;
				}
			}
			temp = temp->_next;
		}

		if (res == nullptr) { return NULL; }

		Header* next = (Header*)((char*)res + sizeof(Header) + n);
		next->_next = temp;
		temp->_parent = next;
		next->_size = res->_size - sizeof(Header) - n;
		next->_parent = res;
		next->_is_free = true;
		res->_is_free = false;
		res->_next = next;
		res->_size = res->_size - next->_size;;

		return ((char*)res + sizeof(Header));
	}

	void deallocate([[maybe_unused]] char* p, [[maybe_unused]] std::size_t n) {
		if ((Header*)p < _main_ptr || (Header*)p >= _last_ptr) { throw std::bad_alloc(); }
		
		Header* temp = (Header*)(p - sizeof(Header));
		temp->_is_free = true;
		Header* next = temp->_next;
		Header* parent = temp->_parent;

		if (next->_is_free) {
			next->_next->_parent = temp;
			temp->_size += next->_size;
			temp->_next = next->_next;
		}

		next = temp->_next;
		if (temp != _main_ptr && parent->_is_free) {
			parent->_next = temp->_next;
			parent->_size += temp->_size;
			next->_parent = parent;
		}

	}

private:
	char* _data;
	Header* _main_ptr;
	Header* _last_ptr;
};

