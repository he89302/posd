.PHONY: clean

test: src/main.cpp src/shape.h src/circle.h src/rectangle.h src/triangle.h
	g++ -std=c++11 src/main.cpp -o bin/test -lgtest -lpthread

clean:
	rm bin/test
