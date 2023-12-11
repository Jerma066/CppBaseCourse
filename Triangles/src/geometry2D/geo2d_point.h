#pragma once

namespace geometry2D {

struct Point final {
  Point() = default;
  Point(float x, float y) : x(x), y(y) {}

  float x, y;
};

} // namespace geometry2D
