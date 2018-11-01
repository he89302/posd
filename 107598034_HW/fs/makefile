.PHONY: clean dirs

BIN=bin
SRC=src
TEST=test
OBJ=obj
LIBS=-lgtest -lpthread

all: dirs $(BIN)/ut_fs

$(BIN)/ut_fs: $(TEST)/ut_fs.cpp $(TEST)/ut_fs.h $(SRC)/node.h $(SRC)/folder.h $(SRC)/file.h $(OBJ)/findvisitor.o
	g++ -std=c++11 $< $(OBJ)/findvisitor.o -o $@ $(LIBS)

$(OBJ)/findvisitor.o: $(SRC)/findvisitor.cpp $(SRC)/findvisitor.h
	g++ -std=c++11 -c $< -o $@

dirs:
	mkdir -p $(SRC) $(TEST) $(BIN) $(OBJ)

clean:
	rm -rf $(BIN) $(OBJ)

stat:
	wc src/* test/*
