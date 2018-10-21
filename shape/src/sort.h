#ifndef Sort_h
#define Sort_h
 #include "shape.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>


class Sort{
    public:
      Sort(std::vector<Shape*>* v): _v(v){}

      // The argument ** Accept comparison ** can accept lambda, function, and object
      void sortArea(std::function<bool(Shape*, Shape*)> sortArea) {
        std::sort(_v->begin(), _v->end(), sortArea);
      }

      void sortPerimeter(std::function<bool(Shape*, Shape*)> perimeterComparison) {
        std::sort(_v->begin(), _v->end(), perimeterComparison);
      }

      template<class CompactnessComparison>
      void sortCompactness(CompactnessComparison compCompar) {
        std::sort(_v->begin(), _v->end(), compCompar);
      }

      /*
      void sortCompactness(std::function<bool(Shape*, Shape*)> compCompar) {
        std::sort(_v->begin(), _v->end(), compCompar);
      }*/





    private:
      std::vector<Shape*>* _v;
};



//You should implement area ascending and descending lamda function as parameter for Sort::sortArea()

//You should use those functions as parameter for Sort::sortPerimeter()

bool perimeterDescendingComparison(Shape *a, Shape *b) {
  return (a->perimeter() > b->perimeter());
}

bool perimeterAscendingComparison(Shape *a, Shape *b) {
  return (a->perimeter() < b->perimeter());
}

//You should use those objects as parameter for Sort::sortCompactness()
class CompactnessAscendingComparison{
public:
  // overload function call "operator()"
    bool operator()(Shape *a, Shape *b) const{
      return a->compactness() < b->compactness();
    }
};

class CompactnessDescendingComparison{
public:
  // overload function call "operator()"
    bool operator()(Shape *a, Shape *b) const{
      return a->compactness() > b->compactness();
    }
};

#endif
