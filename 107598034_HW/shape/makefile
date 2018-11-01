.PHONY: clean

hw3: test/ut_main.cpp test/ut_shape.cpp test/ut_sort.cpp src/circle.h src/rectangle.h src/triangle.h src/sort.h src/main.cpp
	g++ -std=c++11 src/main.cpp -o bin/test -lgtest -lpthread

clean:
	rm bin/test
