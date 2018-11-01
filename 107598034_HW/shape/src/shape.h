#ifndef Shape_h
#define Shape_h

using namespace std;

string ifAreaIsZero = "Division by zero";


class Shape{
public:
  virtual double area() = 0;
  virtual double perimeter() = 0;

  double compactness() {
    double _perimeter = perimeter();
    double _area = area();
    if(_area == 0.0){
       throw ifAreaIsZero;
    }else{
      return _perimeter*_perimeter/_area;
    }
  }
  
};





#endif
