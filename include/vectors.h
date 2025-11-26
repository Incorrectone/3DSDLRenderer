#pragma once

#ifndef VECTORS_H
#define VECTORS_H

#include <iostream>
#include <cmath>

template<typename T>
struct Vector3D{
    T x, y, z;

    Vector3D(T a = 0, T b = 0, T c = 0) : x{a}, y{b}, z{c} {} // Constructor general

    // Constructor for <int> type to <double> type and vice versa
    template <typename D> 
        Vector3D(const Vector3D<D> &other){ 
            x = other.x; 
            y = other.y; 
            z = other.z; 
        }

    template<typename D>
        inline Vector3D& operator+=(const Vector3D<D>& a);

    template<typename D>
        inline Vector3D& operator-=(const Vector3D<D>& a);

    Vector3D& operator*=(const double &a);

    T modulus() const;

    template<typename D>
        T dot(const Vector3D<D>& a) const;

    Vector3D& colorFit();

    Vector3D& normalize();

    template<typename D>
        inline Vector3D cross(const Vector3D<D>& a) const;

    template<typename D>
        inline Vector3D multiply(const Vector3D<D>& a) const;

    Vector3D MatMul(const T m[3][3]) const;
};

template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vector3D<T> &A){
        return os << "<Vector3D[" << &A << "](" << A.x << ", " << A.y << ", " << A.z << ")>";
    }

template <typename T>
template <typename D>
    inline Vector3D<T> &Vector3D<T>::operator+=(const Vector3D<D>& a){
        this->x += a.x;
        this->y += a.y;
        this->z += a.z;
        return *this;
    }

template <typename T>
template <typename D>
    inline Vector3D<T> &Vector3D<T>::operator-=(const Vector3D<D>& a){
        this->x -= a.x;
        this->y -= a.y;
        this->z -= a.z;
        return *this;
    }

template <typename T>
    inline Vector3D<T> &Vector3D<T>::operator*=(const double &a){
        this->x *= a;
        this->y *= a;
        this->z *= a;
        return *this;
    }

template<typename T, typename D>
    Vector3D<T> operator+(Vector3D<T> a, const Vector3D<D>& b){
        return a+=b;
    }

template<typename T, typename D>
    Vector3D<T> operator-(Vector3D<T> a, const Vector3D<D>& b){
        return a-=b;
    }

template<typename T>
    Vector3D<T> operator*(Vector3D<T> a, const double &b){
        return a*=b;
    }

template<typename T>
    Vector3D<T> operator*(const double &a, Vector3D<T> b){
        return b*=a;
    }

template<typename T>
    inline T Vector3D<T>::modulus() const{
        return sqrt(x * x + y * y + z * z);
    }

template<typename T>
template<typename D>
    inline T Vector3D<T>::dot(const Vector3D<D>& a) const{
        return a.x * x + a.y * y + a.z * z;
    }

template<typename T>
    Vector3D<T>& Vector3D<T>::colorFit(){
        if (x > 255) x = 255; else if (x < 0) x = 0;
        if (y > 255) y = 255; else if (y < 0) y = 0;
        if (z > 255) z = 255; else if (z < 0) z = 0;
        return *this;  
    }

template<typename T>
template<typename D>
    inline Vector3D<T> Vector3D<T>::cross(const Vector3D<D>& a) const{
        return Vector3D<T>(
            y * a.z - z * a.y,
            z * a.x - x * a.z,
            x * a.y - y * a.x
        );
    }

template<typename T>
    Vector3D<T>& Vector3D<T>::normalize(){
        T len = modulus();
        if (len > 0) {
            T invLen = 1 / len; 
            x *= invLen;
            y *= invLen;
            z *= invLen;
        }
        return *this;
    }

template<typename T>
template<typename D>
    Vector3D<T> Vector3D<T>::multiply(const Vector3D<D>& b) const {
        return Vector3D<T>(x * b.x, y * b.y, z * b.z);
    }


template<typename T>
    Vector3D<T> Vector3D<T>::MatMul(const T m[3][3]) const {
        return Vector3D<T>(
            m[0][0] * x + m[0][1] * y + m[0][2] * z,
            m[1][0] * x + m[1][1] * y + m[1][2] * z,
            m[2][0] * x + m[2][1] * y + m[2][2] * z
        );
    }

struct Vector2D{
    double x, y;
};
    
#endif