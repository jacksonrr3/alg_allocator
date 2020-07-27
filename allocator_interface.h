#pragma once
#pragma once
#include <iostream>
#include <new>

#include "test_allocator.h"
#include "block_alg.h"
#include "linear_alg.h"
#include "stack_alg.h"
#include "first_fit.h"
#include "list_alg.h"

#define DEBAG

template <typename T, typename Allocator_Algorithm>
class Allocator_Interface {

	Allocator_Algorithm* _algorythm;
public:
	template<typename U>
	struct rebind
	{
		using other = Allocator_Interface<U, Allocator_Algorithm>;
	};


	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;


	Allocator_Interface() : _algorythm(new Allocator_Algorithm()) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
	~Allocator_Interface() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		delete _algorythm;
	}


	T* allocate(std::size_t n) {
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		if (_algorythm == nullptr) { throw std::bad_alloc(); }
		return reinterpret_cast<T*>(_algorythm->allocate(n * sizeof(T)));
	}

	void deallocate(void* p, std::size_t n)
	{
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		if (_algorythm == nullptr) { throw std::bad_alloc(); }
		_algorythm->deallocate(reinterpret_cast<char*>(p), n * sizeof(T));
	}

	template<typename U, typename ...Args>
	void construct(U* p, Args&&...args) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		new(p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U* p) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		p->~U();
	}


	const Allocator_Algorithm* get_alg() const {
		return _algorythm;
	}
};

template <typename T, typename U, typename Allocator_Algorithm>
bool operator==(const Allocator_Interface<T, Allocator_Algorithm> a1,
	const Allocator_Interface<U, Allocator_Algorithm> a2) {

	return a1.get_alg() == a2.get_alg();
}

template <typename T, typename U, typename Allocator_Algorithm>
bool operator!=(const Allocator_Interface<T, Allocator_Algorithm> a1,
	const Allocator_Interface<U, Allocator_Algorithm> a2) {

	return a1.get_alg() = !a2.get_alg();
}
