#ifndef Circle_h
#define Circle_h
#include<math.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include "shape.h"
//std::out_of_range ifAreaIsZero("Division by zero");

class Circle: public Shape {
public:
  Circle(double r):_r(r){}

  double area(){
    return M_PI * _r * _r;
  }

  double perimeter(){
    return 2 * M_PI * _r;
  }

private:
  double _r;
};

#endif
