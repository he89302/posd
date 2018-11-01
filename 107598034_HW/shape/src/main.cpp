#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <vector>
#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "sort.h"

using namespace std;



int main(int argc, char *argv[]){

      std::vector<string> shape(30);
      std::vector<string> v(30);
      std::vector<Shape*>* sortShape = new vector<Shape*>;

      string inputPath = argv[1];
      string outputPath = argv[2];
      string method = argv[3];
      string order = argv[4];

      fstream myShape;
      ofstream output;
      output.open(outputPath);

  if (myShape.open(inputPath), ios::in){
    int i=0;
    while (!myShape.eof()){
      myShape >> shape[i] >> v[i];

      if(shape[i] == "Circle"){
        double circleVertex;
        string str1 = v[i].substr (v[i].find("(")+1, v[i].find(")")-v[i].find("(")-1);
        circleVertex = stod(str1);
        sortShape->push_back(new Circle(circleVertex));
      }

      if(shape[i] == "Rectangle"){
        std::vector<double> rectangleVertex(2);
        std::vector<string> data1;
        string str2 = v[i].substr (v[i].find("(")+1, v[i].find(")")-v[i].find("(")-1);
        istringstream input1(str2);
        string temp;
        while (getline(input1, temp, ',')) {
          data1.push_back(temp);
          }
        for (int i = 0;i < rectangleVertex.size();i++) {
          rectangleVertex[i] = stod(data1[i]);
          }
        sortShape->push_back(new Rectangle(rectangleVertex[0], rectangleVertex[1]));
        input1.clear();
      }

      if(shape[i] == "Triangle"){
        std::vector<double> triangleVertex(6);
        std::vector<string> data2;
        string str3 = v[i].substr (v[i].find("(")+1, v[i].find(")")-v[i].find("(")-1);
        istringstream input2(str3);
        string temp;
        while (getline(input2, temp, ',')) {
          data2.push_back(temp);
        }
        for (int i = 0;i < triangleVertex.size();i++) {
          triangleVertex[i] = stod(data2[i]);
          }
        sortShape->push_back(new Triangle(triangleVertex[0], triangleVertex[1], triangleVertex[2], triangleVertex[3], triangleVertex[4], triangleVertex[5]));
        input2.clear();
      }

      i++;
    }

    myShape.clear();
    myShape.seekg(0);
    myShape.close();
  }else
    cout << "Unable to open file";

    if(method == "area"){
      if(order == "inc"){
        Sort shapeSort(sortShape);
        shapeSort.sortArea([](Shape *a, Shape *b) {
          return a->area() < b->area();
        });
      }else if(order == "dec"){
        Sort shapeSort(sortShape);
        shapeSort.sortArea([](Shape *a, Shape *b) {
          return a->area() > b->area();
        });
      }

      output << "[";
      for (int i = 0; i < sortShape->size(); i++) {
        if(i<sortShape->size()-1)
          output << (*sortShape)[i]->area() << ',';
        else
          output << (*sortShape)[i]->area();
      }output << "]" << '\n';
      output.close();

    }else if(method == "perimeter"){
      if(order == "inc"){
        Sort shapeSort(sortShape);
        shapeSort.sortPerimeter(perimeterAscendingComparison);
      }else if(order == "dec"){
        Sort shapeSort(sortShape);
        shapeSort.sortPerimeter(perimeterDescendingComparison);
      }

      output << "[";
      for (int i = 0; i < sortShape->size(); i++) {
        if(i<sortShape->size()-1)
          output << (*sortShape)[i]->perimeter() << ',';
        else
          output << (*sortShape)[i]->perimeter();
      }output << "]" << '\n';
      output.close();
    }


  return 0;
}
