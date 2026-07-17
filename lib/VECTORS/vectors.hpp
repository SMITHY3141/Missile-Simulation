


#ifndef VECTORS_HPP
#define VECTORS_HPP
#include <cstddef>
#include <iostream>
#include <cmath>

// DECLERATIONS

// in cpp there's aggregate initialisation, so you can initilasize structs c style.
// like Vector<2> vec = {1.f, 2.f}, expands out any arrays and fills data with
// what's given, when it runs out it initialises the rest to 0.
// this breaks for private members though.

template <int N>
struct Vector {
    float data[N];

    float dot(const Vector<N> &other) const;
    float length() const;
    Vector<N> normalised() const;

    Vector<N>& operator+=(const Vector<N> &other); // can be outside struct if need be
    Vector<N>& operator-=(const Vector<N> &other);
    Vector<N>& operator*=(float value);
    Vector<N>& operator/=(float value); // assignment in cpp returns val by ref

    float& operator[](size_t index);
    const float& operator[](size_t index) const;

    //static Vector<N> fromPolar(float magnitude, float angle);

};

template<int N>
std::ostream& operator<<(std::ostream& os, const Vector<N> &v);

template <int N>
// trailing const since it does not modify the current object
Vector<N> operator+(const Vector<N> &self, const Vector<N> &other);

template <int N>
Vector<N> operator-(const Vector<N> &self, const Vector<N> &other);

template <int N>
Vector<N> operator*(const Vector<N> &self, float value);

template <int N>
Vector<N> operator*(float value, const Vector<N> &self);

template <int N>
Vector<N> operator/(const Vector<N> &self, float value);

template <int N>
Vector<N> operator/(float value, const Vector<N> &self);

// template <typename... U> // can create using {1.f, 2.f, ...}
// Vector(U...) -> Vector<sizeof...(U)>; // how many types {float, float, float}



// DEFINITIONS
template<int N>
std::ostream& operator<<(std::ostream& os, const Vector<N> &v) {
    os << '(';
    for (int i = 0; i < N; i++) {
        os << v[i];
        if (i == N - 1) {
            break;

        }
        os << ", ";

    }

    os << ')';
    return os;
}


template<int N>
Vector<N> operator+(const Vector<N> &self, const Vector<N> &other) {
    Vector<N> result;
    for (int i = 0; i < N; i++) {
        result[i] = self[i] + other[i];
    }
    return result;

}

template<int N>
Vector<N> operator-(const Vector<N> &self, const Vector<N> &other) {
    Vector<N> result;
    for (int i = 0; i < N; i++) {
        result[i] = self[i] - other[i];
    }
    return result;

}

template<int N>
Vector<N> operator*(const Vector<N> &self, float value) {
    Vector<N> result;
    for (int i = 0; i < N; i++) {
        result[i] = self[i] * value;
    }
    return result;
}

template<int N>
Vector<N> operator*(float value, const Vector<N> &self) {
    return self * value;
}

template<int N>
Vector<N> operator/(const Vector<N> &self, float value) {
    Vector<N> result;
    for (int i = 0; i < N; i++) {
        result[i] = self[i] / value;
    }
    return result;
}

template<int N>
Vector<N> operator/(float value, const Vector<N> &self) {
    return self / value;
}

template<int N>
float Vector<N>::dot(const Vector<N> &other) const {
    float dot = 0.f;
    for (int i = 0; i < N; i++) {
        dot += data[i] * other[i];
    }
    return dot;
}

template<int N>
float Vector<N>::length() const {
    return std::sqrt(this->dot(*this));
}

template<int N>
Vector<N> Vector<N>::normalised() const {
    return Vector<N>(*this) / this->length();
}

template<int N>
Vector<N>& Vector<N>::operator+=(const Vector<N> &other) {
    for (int i = 0; i < N; i++) {
        data[i] += other[i];
    }
    return *this;
}

template<int N>
Vector<N>& Vector<N>::operator-=(const Vector<N> &other) {
    for (int i = 0; i < N; i++) {
        data[i] -= other[i];
    }
    return *this;
}

template<int N>
Vector<N>& Vector<N>::operator*=(float value) {
    for (int i = 0; i < N; i++) {
        data[i] *= value;
    }
    return *this;
}

template<int N>
Vector<N>& Vector<N>::operator/=(float value) {
    for (int i = 0; i < N; i++) {
        data[i] /= value;
    }
    return *this;
}

template<int N>
float& Vector<N>::operator[](size_t index) {
    return data[index];
}

template<int N>
const float& Vector<N>::operator[](size_t index) const {
    return data[index];
}
/*
Vector Vector::fromPolar(float magnitude, float angle) {
    return {std::cos(angle) * magnitude, std::sin(angle) * magnitude};
}
*/

#endif // VECTORS_HPP
