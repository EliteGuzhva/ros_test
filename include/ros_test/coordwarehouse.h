#pragma once

#include <string>
#include <vector>

#include "point.h"

namespace rt {

class CoordWarehouse {
public:
    using Coords = std::vector<Point>;

    explicit CoordWarehouse(Coords&& c);

    static CoordWarehouse fromCSV(const std::string& filename);

    const Coords getCoords() const noexcept;

private:
    Coords coords;
};

} // namespace rt