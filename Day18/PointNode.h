//
// Created by Samuel Barnes on 12/15/24.
//

#ifndef POINTSCORE2_H
#define POINTSCORE2_H

#include "../Point.h"

struct PointNode : Point {
  PointNode(const int x, const int y, const int score): Point(x, y), Score(score) {
  }

  PointNode(const Point p, const int score): Point(p.x, p.y), Score(score) {
  }

  int Score;

  bool operator<(const PointNode &other) const {
    return Score > other.Score;
  }
};

#endif //POINTSCORE2_H
