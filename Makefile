APPNAME := mp3tagger
CXX := g++
CXXFLAGS := -Wall -g

SRC := src
INC := include
OBJ := obj
DIRECTORIES := mp3files/ images/ obj/
OBJECTS := $(OBJ)/Main.o $(OBJ)/FileExtension.o $(OBJ)/FileNames.o $(OBJ)/Files.o $(OBJ)/Genre.o $(OBJ)/Tag.o

compile: $(OBJECTS)

$(OBJECTS): $(OBJ)/%.o: $(SRC)/%.cpp

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(INC)

run:
	$(CXX) $(CXXFLAGS) -o $(OBJ)/$(APPNAME) $(OBJECTS)
	./$(OBJ)/$(APPNAME)

install:
	rm -rf $(DIRECTORIES)
	mkdir $(DIRECTORIES)

clean:
	rm -rf $(DIRECTORIES)