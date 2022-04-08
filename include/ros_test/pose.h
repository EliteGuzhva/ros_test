#pragma once

#include "point.h"

namespace rt {

struct Pose {
    Point pos;
    double theta = 0.0;
};

} // namespace rt