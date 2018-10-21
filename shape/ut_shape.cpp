#include <gtest/gtest.h>
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

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
  ASSERT_NEAR(14, r.perimeter(), 0.001);
}

TEST (ShapeTest, Triangle) {
  Triangle t(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  ASSERT_NEAR(0.0, t.area(), 0.001);
  ASSERT_NEAR(0.0, t.perimeter(), 0.001);
  ASSERT_TRUE(t.isTriangle());
}
