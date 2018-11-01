#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "sort.h"

void getFileData(std::fstream &fs, std::vector<std::string> &myShape, std::vector<std::string> &vetex) {
  int i = 0;
  while (!fs.eof()) {
    fs >> myShape[i] >> vetex[i];
    vetex[i] = vetex[i].substr(vetex[i].find("(")+1, vetex[i].find(")") - vetex[i].find("(") - 1);
    if(myShape[i] == "Rectangle" || myShape[i] == "Triangle") {
      std::size_t pos = vetex[i].find(",");
      while (vetex[i].find(",") != std::string::npos) {
        vetex[i].erase(pos, 1);
        pos = vetex[i].find(",");
      }
    }
    i++;
  }
}

int main(int argc, char * argv[]) {
  std::string openFilePath = argv[1];
  std::string writeFilePath = argv[2];
  std::string method = argv[3];
  std::string order = argv[4];
  std::vector<std::string> myShape(10);
  std::vector<std::string> vetex(10);
  std::vector<Shape*>* sortShape = new std::vector<Shape*>;

  std::fstream fs;
  std::ofstream output;
  output.open(writeFilePath);

  if (fs.open(openFilePath), std::ios::in){
    getFileData(fs, myShape, vetex);
    for(int i = 0;i < myShape.size(); i++) {

      if(myShape[i] == "Circle") {
        double circleVetex = std::stod(vetex[i]);
        sortShape->push_back(new Circle(circleVetex));
      }

      if(myShape[i] == "Rectangle") {
        std::vector<double> rectangleVetex(2);
        for (int j=0; j<vetex[i].length(); j++){
          std::string temp;
          rectangleVetex[j] = std::stod(temp.assign(vetex[i], j ,1));
        }
        sortShape->push_back(new Rectangle(rectangleVetex[0], rectangleVetex[1]));
      }

      if(myShape[i] == "Triangle") {
        std::vector<double> triangleVetex(6);
        for (int j=0; j<vetex[i].length(); j++){
          std::string temp;
          triangleVetex[j] = std::stod(temp.assign(vetex[i], j ,1));
        }
        sortShape->push_back(new Triangle(triangleVetex[0], triangleVetex[1], triangleVetex[2], triangleVetex[3], triangleVetex[4], triangleVetex[5]));
      }
    }

    fs.close();
  }
  else{
    std::cout << "Error opening file";
  }

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
