#pragma once


template<typename T, size_t N>
class Array {
private:
	T m_data[N];

public:
	Array() {
		//signature: memset(T*, int value, int (size of the array))
		//memset(data(), 0, size() * sizeof(T));
		//or
		memset(&data()[0], 0, size() * sizeof(T));
		//as C style arrays are always continguous in memory
	}
	constexpr size_t size() const {
		return N;
	}

	T& operator[](size_t index) {
		if (index >= N) {
			LOG("hey??");
			__debugbreak();
		}
		return m_data[index];
	}
	const T& operator[]  (size_t index) const {
		if (index >= N) {
			__debugbreak();
		}
		return m_data[index];
	}

	T* data() {
		return m_data;
	}
};




