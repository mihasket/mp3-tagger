APPNAME := mp3tagger
CXX := g++
CXXFLAGS := -Wall -g

SRC := src
INC := include
OBJ := obj
DIRECTORIES := mp3files/ images/ obj/
OBJECTS := $(OBJ)/main.o $(OBJ)/fileExtension.o $(OBJ)/fileNames.o $(OBJ)/files.o $(OBJ)/genre.o $(OBJ)/tag.o

compile: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/$(APPNAME) $(OBJECTS)

$(OBJECTS): $(OBJ)/%.o: $(SRC)/%.cpp

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(INC)

run:
	./$(OBJ)/$(APPNAME)

install:
	rm -rf $(DIRECTORIES)
	mkdir $(DIRECTORIES)

clean:
	rm -rf $(DIRECTORIES)
