#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3
{
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

};

inline vec3::vec3(): e{0, 0, 0} {};
inline vec3::vec3(double x, double y, double z): e{x, y, z} {};
inline double vec3::x() const { return e[0]; }
inline double vec3::y() const { return e[1]; }
inline double vec3::z() const { return e[2]; }
inline vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }
inline double vec3::operator[](int i) const { return e[i]; }
inline double& vec3::operator[] (int i) { return e[i]; }

#endif