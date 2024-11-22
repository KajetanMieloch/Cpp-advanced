#include <iostream>
#include <utility>
#include <type_traits>

namespace cpplab {
    template <typename T>
    class vector {
        T* data;
        size_t size;
        size_t capacity;

    void reallocate(size_t new_capacity) {
        T* new_data = static_cast<T*>(::operator new[](new_capacity * sizeof(T)));
        for (size_t i = 0; i < size; ++i) {
            new (new_data + i) T(std::move(data[i]));
            data[i].~T();
        }
        ::operator delete[](data);
        data = new_data;
        capacity = new_capacity;
    }


    public:
        vector() : data(nullptr), size(0), capacity(0) {}

        vector(const vector& other)
            : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }

        vector& operator=(const vector& other) {
            if (this == &other) return *this;

            delete[] data;

            data = new T[other.capacity];
            size = other.size;
            capacity = other.capacity;
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }

            return *this;
        }

        ~vector() {
            delete[] data;
        }

        vector(vector&& other) noexcept
            : data(other.data), size(other.size), capacity(other.capacity) {
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }

        vector& operator=(vector&& other) noexcept {
            if (this == &other) return *this;

            delete[] data;

            data = other.data;
            size = other.size;
            capacity = other.capacity;

            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;

            return *this;
        }

        void push_back(const T& value) {
            if (size == capacity) {
                reallocate(capacity == 0 ? 1 : capacity * 2);
            }
            data[size++] = value;
        }

        template <typename... Args>
        void emplace_back(Args&&... args) {
            if (size == capacity) {
                reallocate(capacity == 0 ? 1 : capacity * 2);
            }
            data[size++] = T(std::forward<Args>(args)...);
        }

        size_t get_size() const { return size; }
        size_t get_capacity() const { return capacity; }

        T* begin() { return data; }
        T* end() { return data + size; }
        const T* begin() const { return data; }
        const T* end() const { return data + size; }

        T& operator[](size_t index) { return data[index]; }
        const T& operator[](size_t index) const { return data[index]; }
    };
}

class pixel {
    int r, g, b;

public:
    pixel(int red, int green, int blue) : r(red), g(green), b(blue) {}

    friend std::ostream& operator<<(std::ostream& os, const pixel& p) {
        return os << "(" << p.r << "," << p.g << "," << p.b << ")";
    }
};

int main() {
    cpplab::vector<pixel> pixels;
    pixels.emplace_back(255, 0, 0);
    pixels.emplace_back(0, 255, 0);
    pixels.emplace_back(0, 0, 255);

    std::cout << "Pixels in vector: ";
    for (const auto& p : pixels) {
        std::cout << p << " ";
    }
    std::cout << std::endl;

    return 0;
}
