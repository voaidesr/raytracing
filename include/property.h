#ifndef PROPERTY_H
#define PROPERTY_H

#include <iostream>

template <typename T>
class Property {
    T value_;
public:
    explicit Property(const T& v = T{}) : value_(v) {}

    operator T() const { return value_; }

    Property& operator=(const T& v) {
        value_ = v;
        return *this;
    }

    T& get() {
        return value_;
    }

    const T& get() const {
        return value_;
    }

    void set(const T& v) {
        value_ = v;
    }

    void print() const {
        std::cout << "Property value: " << value_ << std::endl;
    }
};

template <typename T>
void clamp(Property<T>& prop, T min_val, T max_val) {
    T value = prop.get();
    if (value < min_val) value = min_val;
    if (value > max_val) value = max_val;
    prop.set(value);
}

#endif
