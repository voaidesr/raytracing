#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
    double e[3]; // x, y, z
public:
    vec3();
    vec3(double x, double y, double z);
    double x() const;// necessary to use const to prevent modification
    double y() const; // if it didn't have const and we used it for a const obj, error
    double z() const;
    vec3 operator-() const; // unary operator
    double operator[](int i) const;
    double& operator[] (int i);
    bool operator==(const vec3& v) const;
    bool operator!=(const vec3& v) const;
    vec3& operator+=(const vec3& v);
    vec3& operator-=(const vec3& v);
    vec3& operator*= (double a);
    vec3& operator/= (double a);
    double length() const;
};

// alias
using point3 = vec3;

inline vec3::vec3(): e{0, 0, 0} {};
inline vec3::vec3(double x, double y, double z): e{x, y, z} {};
inline double vec3::x() const { return e[0]; }
inline double vec3::y() const { return e[1]; }
inline double vec3::z() const { return e[2]; }
inline vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }

inline double vec3::operator[](int i) const {
    if (i >= 0 && i <= 2)
        return e[i];
    else
        throw std::out_of_range("vec3 index out of range");
}
inline double& vec3::operator[] (int i) {
    if (i >= 0 && i <= 2)
        return e[i];
    else
        throw std::out_of_range("vec3 index out of range");
}

inline bool fp_eq(double a, double b) {
    double epsilon = 1e-9;
    return std::fabs(a-b) < epsilon;
}

inline bool vec3::operator== (const vec3& v) const {
    return fp_eq(e[0], v.e[0]) && fp_eq(e[1], v.e[1]) && fp_eq(e[2], v.e[2]);
}

inline bool vec3::operator!= (const vec3& v) const {
    return !(*this == v);
}

inline vec3& vec3::operator+= (const vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline vec3& vec3::operator-= (const vec3& v) {
    return (*this) += (-v);
}

inline vec3& vec3::operator*= (double a) {
    e[0] *= a;
    e[1] *= a;
    e[2] *= a;
    return (*this);
}

inline vec3& vec3::operator/= (double a) {
    if (fp_eq(a, 0.0)) {
        throw std::invalid_argument("Division by zero in vec3::operator/=");
    }
    return (*this) *= 1/a;
}

inline double vec3::length() const {
    return std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2] * e[2]);
}

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(const vec3& v, const vec3& u) {
    return vec3(v[0] + u[0], v[1] + u[1], v[2] + u[2]);
}

inline vec3 operator-(const vec3& v, const vec3& u) {
    return v + (-u);
}

inline vec3 operator*(double a, const vec3& v) {
    return vec3(a * v[0], a * v[1], a * v[2]);
}

inline vec3 operator*(const vec3& v, double a) { return a * v; }

inline vec3 operator/(const vec3& v, double a) { return v * (1/a); }

inline double dot(const vec3& u, const vec3& v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / (v.length());
}

#endif