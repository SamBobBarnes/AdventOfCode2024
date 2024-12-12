//
// Created by Samuel Barnes on 12/12/24.
//

#ifndef GARDENPLOT_H
#define GARDENPLOT_H
#include "../Point.h"

struct GardenPlot {
  GardenPlot(const char plant, const Point pos): Plant(plant), Position(pos) {
  }

  char Plant;
  Point Position;
  int group{-1};

  [[nodiscard]] bool hasGroup() const {
    return group >= 0;
  }
};

#endif //GARDENPLOT_H
