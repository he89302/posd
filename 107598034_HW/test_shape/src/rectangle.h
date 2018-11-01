#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
public:
  Rectangle(double _length, double _width) {
    length = _length;
    width = _width;
  }

  double perimeter() {
    return 2*(length + width);
  }

  double area() {
    return length*width;
  }

private:
  double length;
  double width;
};

#endif
