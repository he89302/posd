#ifndef Rectangle_h
#define Rectangle_h
#include <stdexcept>
#include <iostream>
#include <string>
#include "shape.h"
//std::out_of_range ifAreaIsZero("Division by zero");

class Rectangle : public Shape {
public:
  Rectangle(double length, double width): _length(length), _width(width){}

  double area() {
    return _length * _width;
  }

  double perimeter() {
    return 2*(_length + _width);
  }

private:
    double _length;
    double _width;
};

#endif
