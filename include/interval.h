#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
    double min, max;
public:
    interval();
    interval(double min, double max);

    double inf() const;
    double sup() const;
    bool is_empty() const;
    double size() const;
    double contains(double x) const;
    bool surrounds(double x) const;
    double clamp(double x) const;
    static const interval empty, universe;
};

#endif