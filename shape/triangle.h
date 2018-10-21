#include <math.h>
class Triangle{
  public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3):
    _x1(x1), _y1(y1), _x2(x2), _y2(y2), _x3(x3), _y3(y3)
    {

    }

    double area() {
      double _perimeter = perimeter();
      double halfSumOfLength = _perimeter/2;
      double area = sqrt(halfSumOfLength*(halfSumOfLength - lengthOfAB)*(halfSumOfLength -lengthOfBC)*(halfSumOfLength - lengthOfCA));
      return area;
    }

    double perimeter() {
      setVectorLength();
      return lengthOfAB + lengthOfBC + lengthOfCA;
    }

    bool isTriangle() const {
    if((lengthOfAB + lengthOfBC >= lengthOfCA &&
        lengthOfAB + lengthOfCA >= lengthOfBC &&
        lengthOfCA + lengthOfBC >= lengthOfAB) ||
        (_x1 == _y1 == _x2 == _y2 == _x3 == _y3)){
           return true;
         }
      else return false;
    }

  private:
    double _x1, _y1, _x2, _y2, _x3, _y3;
    double vectorA_x, vectorA_y, vectorB_x, vectorB_y, vectorC_x, vectorC_y;
    double lengthOfAB, lengthOfBC, lengthOfCA;

    double setVector(double x1, double y1, double x2, double y2, double x3, double y3) {
      vectorA_x = x2-x1;
      vectorA_y = y2-y1;
      vectorB_x = x3-x2;
      vectorB_y = y3-y2;
      vectorC_x = x1-x3;
      vectorC_y = y1-y3;
    }

    double setVectorLength() {
      setVector(_x1, _y1, _x2, _y2, _x3, _y3);
      lengthOfAB = sqrt(vectorA_x*vectorA_x + vectorA_y*vectorA_y);
      lengthOfBC = sqrt(vectorB_x*vectorB_x + vectorB_y*vectorB_y);
      lengthOfCA = sqrt(vectorC_x*vectorC_x + vectorC_y*vectorC_y);
    }
};
