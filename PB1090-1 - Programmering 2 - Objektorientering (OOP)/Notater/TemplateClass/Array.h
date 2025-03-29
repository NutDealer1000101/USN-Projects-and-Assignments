#pragma once

import std;

template<typename T>
class Array {
public:
	// Constructors
	explicit Array(std::size_t size)
		:
		size{ size },
		data{ new T[size] }
	{
		std::println("Array(size_t) called.");
	}
	explicit Array(const std::initializer_list<T> init) 
		:
		size{ init.size() },
		data{ new T[init.size()]}
	{
		std::println("Array(initializer_list) called.");

		for (std::size_t i = 0; i < size; i++) {
			data[i] = *(init.begin() + i);
		}
	}
	Array(const Array<T>& other) 
		:
		Array<T>(other.size)
	{
		std::println("Array(Array) called.");

		for (std::size_t i = 0; i < size; i++) {
			data[i] = other[i];
		}
	}

	// Destructors
	~Array() {
		delete[] data;
		data = nullptr;
	}

	// Access
	const T& operator[](std::size_t index) const {
		if (index >= Size()) {
			throw std::out_of_range("Index " + std::to_string(index) + " out of bounds.");
		}
		return data[index];
	}
	T& operator[](std::size_t index) {
		return const_cast<T&>(std::as_const((*this)[index]));
	}

	// Iterators
	T* begin() {
		return data;
	}
	T* end() {
		return data + size;
	}

	// Getters
	std::size_t Size() const {
		return size;
	}
private:
	std::size_t size;
	T* data;
};