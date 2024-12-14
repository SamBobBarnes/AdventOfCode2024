//
// Created by Samuel Barnes on 12/14/24.
//

#ifndef ROBOT_H
#define ROBOT_H
#include <string>
#include "../Helpers.h"
#include "../Point.h"


class Robot {
public:
  explicit Robot(const std::string &line) {
    const auto p = Helpers::split(line, ' ')[0];
    const auto v = Helpers::split(line, ' ')[1];

    const auto ps = Helpers::split(p.substr(2), ',');
    const auto vs = Helpers::split(v.substr(2), ',');

    pos = {stoi(ps[0]), stoi(ps[1])};
    speed = {stoi(vs[0]), stoi(vs[1])};

    // std::cout << p << v << std::endl;
  }

  Point pos;
  Point speed;
};


#endif //ROBOT_H
