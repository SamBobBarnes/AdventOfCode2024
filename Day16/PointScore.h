//
// Created by Samuel Barnes on 12/15/24.
//

#ifndef POINTSCORE_H
#define POINTSCORE_H

#include "../Point.h"

struct PointScore : Point {
    PointScore(const int x, const int y, const int score, const int dir): Point(x, y), Score(score), Dir(dir) {
    }

    PointScore(const Point p, const int score, const int dir): Point(p.x, p.y), Score(score), Dir(dir) {
    }

    int Score;
    int Dir;

    bool operator<(const PointScore &other) const {
        return Score > other.Score;
    }
};

#endif //POINTSCORE_H
