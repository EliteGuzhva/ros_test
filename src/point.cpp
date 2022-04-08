#include <ros_test/point.h>

#include <cmath>

using namespace std;

namespace rt {

Point::Point(double _x, double _y)
    : x(_x)
    , y(_y)
{
}

Point Point::operator-(const Point& rhs) const noexcept {
    return Point(x - rhs.x, y - rhs.y);
}

double distance(const Point& pt) {
    return sqrt(pow(pt.x, 2) + pow(pt.y, 2));
}

} // namespace rt