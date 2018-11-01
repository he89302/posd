#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <math.h>
#include "shape.h"
#include <exception>
#include <string>

class Triangle : public Shape{
public:
  Triangle(double _x1, double _y1, double _x2, double _y2, double _x3, double _y3) {
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;
    x3 = _x3;
    y3 = _y3;

    isTriangle();
  }

  double perimeter() {
    setLength();
    return lengthAB + lengthBC + lengthCA;
  }

  double area() {
    setLength();
    double s = perimeter()/2;
    return sqrt(s*(s - lengthAB)*(s - lengthBC)*(s - lengthCA));
  }

  void  setLength() {
    lengthAB = sqrt(pow((x2-x1), 2) + pow((y2-y1), 2));
    lengthBC = sqrt(pow((x3-x2), 2) + pow((y3-y2), 2));
    lengthCA = sqrt(pow((x1-x3), 2) + pow((y1-y3), 2));
  }

  bool isTriangle() {
    setLength();
    if(lengthAB + lengthBC > lengthCA &&
       lengthBC + lengthCA > lengthAB &&
       lengthCA + lengthAB > lengthBC)
       return true;
    else {
      throw std::string("Not a triangle.");
    }
  }

private:
  double x1, y1, x2, y2, x3, y3;
  double lengthAB, lengthBC, lengthCA;
};

#endif
