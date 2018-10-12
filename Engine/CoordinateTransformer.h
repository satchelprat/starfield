#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include <vector>

class CoordinateTransformer {
public:
  CoordinateTransformer(Graphics &gfx) : gfx(gfx) {}
  void DrawClosedPolyline(std::vector<Vec2> poly, Color c) {
    Vec2 offset = {float(Graphics::ScreenWidth / 2),
                   float(Graphics::ScreenHeight / 2)};
    for (auto &v : poly) {
      v.y *= -1;
      v += offset;
    }

    gfx.DrawClosedPolyline(poly, c);
  }

private:
  Graphics &gfx;
};
