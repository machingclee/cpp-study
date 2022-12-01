#pragma once
#include "pch.h"

class String {
private:
	size_t m_size;
	char* m_buffer;

public:
	String(const char* string) {
		m_size = strlen(string);
		m_buffer = new char[m_size + 1];
		memcpy(m_buffer, string, m_size);
		m_buffer[m_size] = 0;
	}
	~String() {
		delete[] m_buffer;
	}
	String(const String& other)
		: m_size(other.m_size)
	{
		m_buffer = new char[m_size + 1];
		memcpy(m_buffer, other.m_buffer, m_size);
		m_buffer[m_size] = 0;
	}

	char& operator[](int index) {
		return m_buffer[index];
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);

};

std::ostream& operator<<(std::ostream& stream, const String& string) {
	stream << string.m_buffer;
	return stream;
}