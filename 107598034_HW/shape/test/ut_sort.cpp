#include <gtest/gtest.h>
#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/sort.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

TEST(Shape, SortingByLambda) {
  std::vector<Shape*>* sortShape = new vector<Shape*>;
  sortShape->push_back(new Circle(1.0));
  sortShape->push_back(new Rectangle(3.0, 4.0));
  sortShape->push_back(new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 4.0));
  Sort shapeSort(sortShape);
  shapeSort.sortArea([](Shape *a, Shape *b) {
    return a->area() < b->area();
  });
  ASSERT_NEAR(3.14159, (*sortShape)[0]->area(), 0.001);
  ASSERT_NEAR(6, (*sortShape)[1]->area(), 0.001);
  ASSERT_NEAR(12, (*sortShape)[2]->area(), 0.001);
}

TEST(Shape, SortingByDescendingFunction) {
  std::vector<Shape*>* sortShape = new vector<Shape*>;
  sortShape->push_back(new Circle(1.0));
  sortShape->push_back(new Rectangle(3.0, 4.0));
  sortShape->push_back(new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 4.0));
  Sort shapeSort(sortShape);
  shapeSort.sortPerimeter(perimeterDescendingComparison);
  ASSERT_NEAR(14, (*sortShape)[0]->perimeter(), 0.001);
  ASSERT_NEAR(12, (*sortShape)[1]->perimeter(), 0.001);
  ASSERT_NEAR(6.28318, (*sortShape)[2]->perimeter(), 0.001);
}

TEST(Shape, SortingByAscendingFunction) {
  std::vector<Shape*>* sortShape = new vector<Shape*>;
  sortShape->push_back(new Circle(1.0));
  sortShape->push_back(new Rectangle(3.0, 4.0));
  sortShape->push_back(new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 4.0));
  Sort shapeSort(sortShape);
  shapeSort.sortPerimeter(perimeterAscendingComparison);
  ASSERT_NEAR(14, (*sortShape)[2]->perimeter(), 0.001);
  ASSERT_NEAR(12, (*sortShape)[1]->perimeter(), 0.001);
  ASSERT_NEAR(6.28318, (*sortShape)[0]->perimeter(), 0.001);
}

TEST(Shape, SortingByDescendingObject) {
  std::vector<Shape*>* sortShape = new vector<Shape*>;
  sortShape->push_back(new Circle(1.0));
  sortShape->push_back(new Rectangle(3.0, 4.0));
  sortShape->push_back(new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 4.0));
  Sort shapeSort(sortShape);
  shapeSort.sortCompactness(CompactnessDescendingComparison());
  ASSERT_NEAR(24, (*sortShape)[0]->compactness(), 0.001);
  ASSERT_NEAR(16.3333, (*sortShape)[1]->compactness(), 0.001);
  ASSERT_NEAR(12.56637, (*sortShape)[2]->compactness(), 0.001);
}

TEST(Shape, SortingByAscendingObject) {
  std::vector<Shape*>* sortShape = new vector<Shape*>;
  sortShape->push_back(new Circle(1.0));
  sortShape->push_back(new Rectangle(3.0, 4.0));
  sortShape->push_back(new Triangle(0.0, 0.0, 3.0, 0.0, 0.0, 4.0));
  Sort shapeSort(sortShape);
  shapeSort.sortCompactness(CompactnessAscendingComparison());
  ASSERT_NEAR(24, (*sortShape)[2]->compactness(), 0.001);
  ASSERT_NEAR(16.3333, (*sortShape)[1]->compactness(), 0.001);
  ASSERT_NEAR(12.56637, (*sortShape)[0]->compactness(), 0.001);
}
