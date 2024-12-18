//
// Created by Samuel Barnes on 12/15/24.
//

#ifndef POINTSCORE_H
#define POINTSCORE_H

#include "../Point.h"

struct PointScore : Point {
  PointScore(const int x, const int y, const int score): Point(x, y), Score(score) {
  }

  PointScore(const Point p, const int score): Point(p.x, p.y), Score(score) {
  }

  int Score;

  bool operator<(const PointScore &other) const {
    return Score > other.Score;
  }
};

#endif //POINTSCORE_H
