#include <gtest/gtest.h>
#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <exception>

using namespace std;

TEST (ShapeTest, first)
{
  ASSERT_TRUE(true);
}

TEST (ShapeTest, Circle)
{
  Circle c(10.0);
  ASSERT_NEAR(314.159, c.area(), 0.001);
  ASSERT_NEAR(62.831, c.perimeter(), 0.001);
}

TEST (ShapeTest, Retangle) {
  Rectangle r(3.0, 4.0);
  ASSERT_NEAR(12.0, r.area(), 0.001);
  ASSERT_NEAR(14.0, r.perimeter(), 0.001);
}

TEST (ShapeTest, Triangle_Area_Perimeter) {
  Triangle t(0.0, 0.0, 8.0, 0.0, 0.0, 15.0);
  ASSERT_NEAR(60.0, t.area(), 0.001);
  ASSERT_NEAR(40.0, t.perimeter(), 0.001);
}

TEST (ShapeTest, Triangle_Compactness) {
  Triangle t(1.0, 1.0, 3.0, 1.0, 1.0, 3.0);
  try{
    ASSERT_NEAR(23.313, t.compactness(), 0.001);
  }catch(const string & e){
    string compactnessErrorMsg = e;
    EXPECT_EQ("Division by zero", compactnessErrorMsg);
  }
}

TEST(ShapeTest, Triangle_isTriangle) {
  try{
    Triangle t(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  }catch(const string & ex){
    EXPECT_EQ("Not a triangle.", ex);
  }
}
