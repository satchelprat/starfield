#pragma once

#include "Vec2.h"
#include <vector>

class Entity {

public:
  Entity(std::vector<Vec2> model) : model(std::move(model)) {}
  Vec2 GetPos() const { return pos; }
  void SetPos(const Vec2 &_pos) { pos = _pos; }
  void TranslateBy(const Vec2 &offset) { pos += offset; }
  std::vector<Vec2> GetPolyLine() const {
    auto poly = model;
    for (auto &v : poly) {
      v += pos;
    }
    return poly;
  }

private:
  Vec2 pos = {0.0f, 0.0f};
  std::vector<Vec2> model;
};
