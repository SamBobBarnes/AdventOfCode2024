//
// Created by Samuel Barnes on 11/30/2024.
//

#ifndef POINT_H
#define POINT_H

struct Point {
    Point() {
    }

    Point(const int x, const int y) {
        this->x = x;
        this->y = y;
    }

    [[nodiscard]] bool equals(const Point &b) const {
        return this->x == b.x && this->y == b.y;
    }

    bool operator<(const Point &other) const {
        if (y == other.y) return x < other.x;
        return y < other.y;
    }

    bool operator>(const Point &other) const {
        if (x == other.x) return y > other.y;
        return x > other.x;
    }

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    friend Point operator+(Point lhs, // passing lhs by value helps optimize chained a+b+c
                           const Point &rhs) // otherwise, both parameters may be const references
    {
        lhs.x += rhs.x; // reuse compound assignment
        lhs.y += rhs.y;
        return lhs; // return the result by value (uses move constructor)
    }

    int x;
    int y;
};

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

struct PointScoreDir : PointScore {
    PointScoreDir(const int x, const int y, const int score, const int dir): PointScore(x, y, score), Dir(dir) {
    }

    PointScoreDir(const Point p, const int score, const int dir): PointScore(p.x, p.y, score), Dir(dir) {
    }

    int Dir;

    bool operator<(const PointScoreDir &other) const {
        return Score > other.Score;
    }
};

struct Point3 : Point {
    Point3() {
    }

    Point3(const int x, const int y, const int z): Point(x, y) {
        this->z = z;
    }

    int z;

    bool operator<(const Point3 &other) const {
        if (z == other.z) {
            if (y == other.y) return x < other.x;
            return y < other.y;
        }
        return z < other.z;
    }


    bool operator==(const Point3 &other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

#endif //POINT_H
