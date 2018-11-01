#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <math.h>

class Circle : public Shape{
public:
  Circle(double r){
    redius = r;
  }

  double perimeter() {
    return M_PI*redius*2;
  }

  double area() {
    return M_PI*redius*redius;
  }

private:
  double redius;
};

#endif
