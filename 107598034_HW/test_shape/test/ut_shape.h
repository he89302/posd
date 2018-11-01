#ifndef UT_SHAPE_H
#define UT_SHAPE_H

#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include <string>

TEST (ShapeTest, Circle) {
  Circle circle(1.0);
  ASSERT_NEAR(6.2831, circle.perimeter(), 0.001);
  ASSERT_NEAR(3.1415, circle.area(), 0.001);
}

TEST (ShapeTest, Rectangle) {
  Rectangle rectangle(3.0, 4.0);
  ASSERT_NEAR(14, rectangle.perimeter(), 0.001);
  ASSERT_NEAR(12, rectangle.area(), 0.001);
}

TEST (ShapeTest, Triangle_Area_Perimeter) {
  Triangle t(0.0, 0.0, 8.0, 0.0, 0.0, 15.0);
  ASSERT_NEAR(60.0, t.area(), 0.001);
  ASSERT_NEAR(40.0, t.perimeter(), 0.001);
}

TEST(ShapeTest, Triangle_isNotTriangle) {
  try{
    Triangle t(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  }catch(const std::string & ex){
    EXPECT_EQ("Not a triangle.", ex);
  }
}

TEST(ShapeTest, TriangleIsTriangle) {
  try{
    Triangle t(0.0, 0.0, 8.0, 0.0, 0.0, 15.0);
    ASSERT_TRUE(t.isTriangle());
  }catch(const std::string & ex){
    EXPECT_EQ("Not a triangle.", ex);
  }
}

#endif
