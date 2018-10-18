#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include <vector>
#include "Drawable.h"

class CoordinateTransformer {
public:
  CoordinateTransformer(Graphics &gfx) : gfx(gfx) {}

  void Draw(std::vector<Vec2>* model, Drawable& dw) const
  {
    const Vec2 offset = {float(Graphics::ScreenWidth / 2),float(Graphics::ScreenHeight / 2)};
 
	 dw.ScaleIndependent(1.0f, -1.0f);
	 dw.Translate(offset);
	 dw.PRender(model, gfx);
  }

private:
  Graphics &gfx;
};
