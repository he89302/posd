.PHONY: clean dirs
BIN=bin
SRC=src
TEST=test
OBJ=obj
LIBS=-lgtest -lpthread
HW=hw8

all: dirs $(BIN)/$(HW)

$(BIN)/$(HW):$(SRC)/tree_test.cpp $(SRC)/tree_test.h $(SRC)/tree_frame.h $(SRC)/node_builder.h $(SRC)/node_iterator.h $(SRC)/node.h $(SRC)/null_iterator.h $(SRC)/subject.h $(SRC)/observer.h $(SRC)/file_system.h | $(BIN)
	g++ -std=c++11 $< `wx-config --libs` `wx-config --cxxflags` -o $@
# $(BIN)/$(HW): $(TEST)/ut_fs.cpp $(TEST)/ut_fs.h $(SRC)/node.h $(SRC)/folder.h $(SRC)/file.h $(SRC)/node_builder.h $(SRC)/node_visitor.h $(OBJ)/info_content_visitor.o $(OBJ)/find_visitor.o $(OBJ)/find_link_visitor.o $(OBJ)/find_node_by_pathname_visitor.o
# 	g++ -std=c++11 $< $(OBJ)/info_content_visitor.o $(OBJ)/find_visitor.o $(OBJ)/find_link_visitor.o $(OBJ)/find_node_by_pathname_visitor.o  -o $@ $(LIBS)

# $(OBJ)/info_content_visitor.o: $(SRC)/info_content_visitor.cpp $(SRC)/info_content_visitor.h
# 	g++ -std=c++11 -c $< -o $@
#
# $(OBJ)/find_visitor.o: $(SRC)/find_visitor.cpp $(SRC)/find_visitor.h
# 	g++ -std=c++11 -c $< -o $@
#
# $(OBJ)/find_link_visitor.o: $(SRC)/find_link_visitor.cpp $(SRC)/find_link_visitor.h
# 	g++ -std=c++11 -c $< -o $@
#
# $(OBJ)/find_node_by_pathname_visitor.o: $(SRC)/find_node_by_pathname_visitor.cpp $(SRC)/find_node_by_pathname_visitor.h
# 	g++ -std=c++11 -c $< -o $@

dirs:
	mkdir -p $(SRC) $(TEST) $(BIN) $(OBJ)

clean:
	rm -rf $(BIN) $(OBJ)

stat:
	wc src/* test/*
