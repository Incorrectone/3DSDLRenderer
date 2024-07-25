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
        inline Vector3D& operator+=(const Vector3D<D> a);

    template<typename D>
        inline Vector3D& operator-=(const Vector3D<D> a);

    Vector3D& operator*=(const double a);

    T modulus() const;

    template<typename D>
        T dot(Vector3D<D> a) const;

    Vector3D& colorFit();

};

template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vector3D<T> &A){
        return os << "<Vector3D[" << &A << "](" << A.x << ", " << A.y << ", " << A.z << ")>";
    }

template <typename T>
template <typename D>
    inline Vector3D<T> &Vector3D<T>::operator+=(const Vector3D<D> a){
        this->x += a.x;
        this->y += a.y;
        this->z += a.z;
        return *this;
    }

template <typename T>
template <typename D>
    inline Vector3D<T> &Vector3D<T>::operator-=(const Vector3D<D> a){
        this->x -= a.x;
        this->y -= a.y;
        this->z -= a.z;
        return *this;
    }

template <typename T>
    inline Vector3D<T> &Vector3D<T>::operator*=(const double a){
        this->x *= a;
        this->y *= a;
        this->z *= a;
        return *this;
    }

template<typename T, typename D>
    Vector3D<T> operator+(Vector3D<T> a, Vector3D<D> b){
        return a+=b;
    }

template<typename T, typename D>
    Vector3D<T> operator-(Vector3D<T> a, Vector3D<D> b){
        return a-=b;
    }

template<typename T>
    Vector3D<T> operator*(Vector3D<T> a, double b){
        return a*=b;
    }

template<typename T>
    Vector3D<T> operator*(double a, Vector3D<T> b){
        return b*=a;
    }

template<typename T>
    inline T Vector3D<T>::modulus() const{
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }

template<typename T>
template<typename D>
        inline T Vector3D<T>::dot(Vector3D<D> a) const{
            return a.x * x + a.y * y + a.z * z;
        }

template<typename T>
    Vector3D<T>& Vector3D<T>::colorFit(){
            if(this->x > 255){
                this->x = 255;
            }else if(this->x < 0){
                this->x = 0;
            }
            if(this->y > 255){
                this->y = 255;
            }else if(this->y < 0){
                this->y = 0;
            }
            if(this->z > 255){
                this->z = 255;
            }else if(this->z < 0){
                this->z = 0;
            }
            return *this;   
        }

struct Vector2D{
    double x, y;
};
    
#endif