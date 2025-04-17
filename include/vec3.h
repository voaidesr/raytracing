#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
    double e[3]; // x, y, z
public:
    vec3();
    vec3(double x, double y, double z);
    vec3(const vec3& v);
    double x() const;// necessary to use const to prevent modification
    double y() const; // if it didn't have const and we used it for a const obj, error
    double z() const;
    vec3 operator-() const;
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

bool fp_eq(double a, double b);

std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 operator+(const vec3& v, const vec3& u);
vec3 operator-(const vec3& v, const vec3& u);
vec3 operator*(double a, const vec3& v);
vec3 operator*(const vec3& v, double a);
vec3 operator/(const vec3& v, double a);
double dot(const vec3& u, const vec3& v);
vec3 cross(const vec3& u, const vec3& v);
vec3 unit_vector(const vec3& v);

#endif