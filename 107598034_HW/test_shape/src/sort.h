#ifndef SORT_H
#define SORT_H

#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include <vector>
class Sort {
public:
  Sort(std::vector<Shape*>* _v) {
    v = _v;
  }

  template<class lanmbda>
  void sortArea(lanmbda sortArea) {
    std::sort(v->begin(), v->end(), sortArea);
  }

  template<class function>
  void sortPerimeter(function sortPerimeter) {
    std::sort(v->begin(), v->end(), sortPerimeter);
  }

  template<class classFuntion>
  void sortCompactness(classFuntion sortCompactness) {
    std::sort(v->begin(), v->end(), sortCompactness);
  }

private:
  std::vector<Shape*>* v;
};

bool perimeterAscendingComparison(Shape* a, Shape* b) {
  return a->perimeter() < b->perimeter();
}

bool perimeterDescendingComparison(Shape* a, Shape* b) {
  return a->perimeter() > b->perimeter();
}

class CompactnessDescendingComparison {
public:
  bool operator()(Shape* a, Shape* b) {
    return a->compactness() > b->compactness();
  }
};

class CompactnessAscendingComparison {
public:
  bool operator()(Shape* a, Shape* b) {
    return a->compactness() < b->compactness();
  }
};

#endif
