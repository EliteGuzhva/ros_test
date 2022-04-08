#pragma once

namespace rt {

class Point {
public:
    double x = 0;
    double y = 0;

    Point() = default;
    Point(double _x, double _y);

    Point operator-(const Point& rhs) const noexcept;
};

double distance(const Point& pt);

} // namespace rt