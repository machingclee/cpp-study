#pragma once
#include "pch.h"



struct Vector3 {
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int* m_MemoryBlock;
	Vector3() {
		m_MemoryBlock = new int[5];
	}
	Vector3(float scalar)
		: x(scalar), y(scalar), z(scalar)
	{
		m_MemoryBlock = new int[5];
	}
	Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
		m_MemoryBlock = new int[5];
	}

	Vector3(const Vector3& other) :
		x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Copy\n";
		m_MemoryBlock = new int[5];
	}
	~Vector3() {
		std::cout << "Destroy\n";
		delete[] m_MemoryBlock;
	}

	//Vector3& operator=(const Vector3& other) {
	//	
	//	std::cout << "Copy\n";
	//	x = other.x;
	//	y = other.y;
	//	z = other.z;
	//	return *this;
	//}

	Vector3& operator=(Vector3&& other) noexcept {
		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;
		std::cout << "Move\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
};

std::ostream& operator<<(std::ostream& stream, const Vector3& vec3) {
	stream << "(" << vec3.x << ", " << vec3.y << ", " << vec3.z << ")";
	return stream;
}



template<typename Vector>
class VectorIterator {
public:
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

public:
	VectorIterator(PointerType ptr) : m_Ptr(ptr) {
	}
	// prefix
	VectorIterator& operator++() {
		m_Ptr++;
		return *this;
	}
	// postfix
	//VectorIterator& operator++(int) {
	//	VectorIterator iterator = *this;
	//	++(*this);
	//	return iterator;
	//}
	// prefix
	//VectorIterator& operator--() {
	//	m_Ptr--;
	//	return *this;
	//}
	//// postfix
	//VectorIterator& operator--(int) {
	//	VectorIterator iterator = *this;
	//	--(*this);
	//	return iterator;
	//}

	//ReferenceType operator[](int index) {
	//	return *(m_Ptr + index);
	//}

	//PointerType operator->() {
	//	return m_Ptr;
	//}

	ReferenceType operator*() {
		return *m_Ptr;
	}
	bool operator ==(const VectorIterator& other) const {
		return m_Ptr == other.m_Ptr;
	}
	bool operator !=(const VectorIterator& other) const {
		return !(*this == other);
	}

private:
	PointerType m_Ptr;
};


template<typename T>
class Vector {
public:
	using ValueType = T;
	using Iterator = VectorIterator<Vector<T>>;

public:
	Vector() {
		ReAlloc(2);
	}
	~Vector() {
		ClearByIndividualDestructor();
		::operator delete(m_Data, m_Capacity * sizeof(T));
	}

	size_t Size() {
		return m_Size;
	}
	T& operator [] (int index) {
		if (index >= m_Size) {
			__debugbreak();
		}
		return m_Data[index];
	}

	const T& operator [] (int index) const {
		return m_Data[index];
	}

	template<typename... Args>

	T& EmplaceBack(Args&&... args) {
		std::cout << "EmplaceBack\n";
		if (m_Size >= m_Capacity) {
			m_Capacity = (size_t)(m_Capacity * 1.5);
			ReAlloc(m_Capacity);
		}

		//m_Data[m_Size] = T(std::forward<Args>(args)...);
		new(&m_Data[m_Size])T(std::forward<Args>(args)...);
		m_Size++;
		return m_Data[m_Size];
	}

	void PopBack() {
		if (m_Size > 0) {
			m_Size--;
			m_Data[m_Size].~T();
		}
	}

	void ClearByIndividualDestructor() {
		for (size_t i = 0; i < m_Size; i++) {
			m_Data[i].~T();
		}
		m_Size = 0;
	}

	void PushBack(const T& value) {
		LOG("here");
		if (m_Size >= m_Capacity) {
			m_Capacity = (size_t)(m_Capacity * 1.5);
			ReAlloc(m_Capacity);
		}
		m_Data[m_Size] = value;
		m_Size++;
	}

	void PushBack(const T* valuePtr) {
		if (m_Size >= m_Capacity) {
			m_Capacity = (size_t)(m_Capacity * 1.5);
			ReAlloc(m_Capacity);
		}

		m_Data[m_Size] = std::move((T)*valuePtr);
		m_Size++;
	}

	void PushBack(T&& value) {
		if (m_Size >= m_Capacity) {
			m_Capacity = (size_t)(m_Capacity * 1.5);
			ReAlloc(m_Capacity);
		}
		// when value (being a Rvalue) goes into this function, value itself become an Lvalue inside this function
		// we need to convert value into a temporary value by std::move
		m_Data[m_Size] = std::move(value);
		m_Size++;
	}

	Iterator begin() {
		return Iterator(m_Data);
	}

	Iterator end() {
		return Iterator(m_Data + m_Size);
	}
private:
	T* m_Data = 0;
	size_t m_Size = 0;
	size_t m_Capacity = 0;


	void ReAlloc(size_t newCapacity) {
		T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

		if (newCapacity < m_Size) {
			m_Size = newCapacity;
		}

		for (size_t i = 0; i < m_Size; i++) {
			//newBlock[i] = std::move(m_Data[i]);
			new(&newBlock[i]) T(std::move(m_Data[i]));
		}

		for (size_t i = 0; i < m_Size; i++) {
			m_Data[i].~T();
		}

		// this will not call the destructor of all object inside the array
		// therefore allocated memory will not be deleted twice 
		::operator delete(m_Data, m_Capacity * sizeof(T));


		m_Data = newBlock;
		m_Capacity = newCapacity;
	}
};

template<typename T>
void PrintVector(Vector<T>& vector) {
	for (size_t i = 0; i < vector.Size(); i++) {
		std::cout << vector[i] << std::endl;
	}
	std::cout << "---------------------------" << std::endl;
}

