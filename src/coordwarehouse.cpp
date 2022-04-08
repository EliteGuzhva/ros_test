#include <ros_test/coordwarehouse.h>

#include <array>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace rt {

CoordWarehouse::CoordWarehouse(Coords&& c)
    : coords(move(c))
{
}

CoordWarehouse CoordWarehouse::fromCSV(const std::string& filename) {
    ifstream file(filename);
  
    vector<Point> coords;
    array<string, 2> row;
    string line, word;
  
    while (getline(file, line)) {
        auto lineStream = stringstream(line);
        for (size_t i = 0; i < row.size(); ++i)
            getline(lineStream, row[i], ',');

        coords.emplace_back(stod(row[0]), stod(row[1]));
    }

    return CoordWarehouse(move(coords));
}

const CoordWarehouse::Coords CoordWarehouse::getCoords() const noexcept {
    return coords;
}

} // namespace rt