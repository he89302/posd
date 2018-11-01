#ifndef SHAP_H
#define SHAP_H
#include <string>

class Shape {
public:
  virtual double perimeter() = 0;
  virtual double area() = 0;

  double compactness() {
    double _perimeter = perimeter();
    double _area = area();
    if(_area == 0.0){
       throw std::string("Division by zero");
    }else{
      return _perimeter*_perimeter/_area;
    }
  }
};

#endif
