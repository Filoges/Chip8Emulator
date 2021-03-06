#pragma once
#include <cstdint>
void REQUIRE(bool condition, const char* message) {
	if (!condition)throw message;
}

template <class T>
class safe_array {
private:

	T* m_arr = nullptr;

public:
	uint64_t size;

	safe_array(uint64_t s = 0) :size(s) {
		if (s)
			m_arr = new T[size];
	}

	~safe_array() {
		delete[] m_arr;
	}

	safe_array(const safe_array& arr) = delete;
	safe_array(safe_array&& arr) = delete;

	void constructArray(uint64_t size) {
		this->size = size;
		m_arr = new T[size];
	}
	void setArray(T val) {
		memset(m_arr, val, sizeof(T) * size);
	}

	void setArray(T* arr2, size_t size2) {
		if (size == size2) {
			memcpy(m_arr, arr2, sizeof(T) * size);
		}
	}

	inline T& operator[](int index) {
		REQUIRE(index >= 0 && index < size, "Out of Bounds");
		return m_arr[index];
	}
	inline T operator[] (int index) const {
		REQUIRE(index >= 0 && index < size, "Out of Bounds");
		return m_arr[index];
	}

	void clear() {
		memset(m_arr, 0, size * sizeof(T));
	}

	void print(std::ostream& o) {
		for (register int i = 0; i < size; i++) {
			o << m_arr[i] << ' ';
		}
		o << '\n';
	}

	T* getArray() const {
		return m_arr;
	}
};