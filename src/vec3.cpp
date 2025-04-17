#include "vec3.h"
#include <cmath>
#include <stdexcept>

vec3::vec3() : e{0, 0, 0} {}
vec3::vec3(double x, double y, double z) : e{x, y, z} {}
vec3::vec3(const vec3& v) : e{v[0], v[1], v[2]} {}

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

vec3 vec3::operator-() const {
    return vec3(-e[0], -e[1], -e[2]);
}

double vec3::operator[](int i) const {
    if (i >= 0 && i <= 2)
        return e[i];
    throw std::out_of_range("vec3 index out of range");
}

double& vec3::operator[](int i) {
    if (i >= 0 && i <= 2)
        return e[i];
    throw std::out_of_range("vec3 index out of range");
}

bool fp_eq(double a, double b) {
    double epsilon = 1e-9;
    return std::abs(a - b) < epsilon;
}

bool vec3::operator==(const vec3& v) const {
    return fp_eq(e[0], v.e[0]) && fp_eq(e[1], v.e[1]) && fp_eq(e[2], v.e[2]);
}

bool vec3::operator!=(const vec3& v) const {
    return !(*this == v);
}

vec3& vec3::operator+=(const vec3& v) {
    e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2];
    return *this;
}

vec3& vec3::operator-=(const vec3& v) {
    return *this += (-v);
}

vec3& vec3::operator*=(double a) {
    e[0] *= a; e[1] *= a; e[2] *= a;
    return *this;
}

vec3& vec3::operator/=(double a) {
    if (fp_eq(a, 0.0)) throw std::invalid_argument("Division by zero in vec3::operator/=");
    return *this *= 1/a;
}

double vec3::length() const {
    return std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
}

// Free functions

std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

vec3 operator+(const vec3& v, const vec3& u) {
    return vec3(v[0] + u[0], v[1] + u[1], v[2] + u[2]);
}

vec3 operator-(const vec3& v, const vec3& u) {
    return v + (-u);
}

vec3 operator*(double a, const vec3& v) {
    return vec3(a * v[0], a * v[1], a * v[2]);
}

vec3 operator*(const vec3& v, double a) {
    return a * v;
}

vec3 operator/(const vec3& v, double a) {
    return v * (1/a);
}

double dot(const vec3& u, const vec3& v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

vec3 unit_vector(const vec3& v) {
    return v / v.length();
}
