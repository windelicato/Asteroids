CC = g++ -I ./include
CFLAGS =  -g -lGL -lGLU -lglui  -lglut -lglm -lpng12 -ljpeg -lm -lalut -lopenal

INC = ./include
SRC = ./src
OBJ = ./obj
BIN = ./bin
GLM = ./glm

vpath %.h ./include
vpath %.c ./src

EXECS = $(BIN)/game

all: $(EXECS)


$(OBJ)/audioLoader.o: $(INC)/audioLoader.h $(SRC)/audioLoader.cpp
	$(CC) $(CFLAGS) -c $(SRC)/audioLoader.cpp -o $(OBJ)/audioLoader.o

$(OBJ)/modelLoader.o: $(INC)/modelLoader.h $(SRC)/modelLoader.cpp
	$(CC) $(CFLAGS) -c $(SRC)/modelLoader.cpp -o $(OBJ)/modelLoader.o

$(OBJ)/character.o: $(INC)/character.h $(SRC)/character.cpp
	$(CC) $(CFLAGS) -c $(SRC)/character.cpp -o $(OBJ)/character.o

$(OBJ)/asteroid.o: $(INC)/asteroid.h $(SRC)/asteroid.cpp
	$(CC) $(CFLAGS) -c $(SRC)/asteroid.cpp -o $(OBJ)/asteroid.o

$(OBJ)/laser.o: $(INC)/laser.h $(SRC)/laser.cpp
	$(CC) $(CFLAGS) -c $(SRC)/laser.cpp -o $(OBJ)/laser.o

$(OBJ)/ship.o: $(INC)/ship.h $(SRC)/ship.cpp
	$(CC) $(CFLAGS) -c $(SRC)/ship.cpp -o $(OBJ)/ship.o

$(OBJ)/top_scores.o: $(INC)/top_scores.h $(SRC)/top_scores.cpp
	$(CC) $(CFLAGS) -c $(SRC)/top_scores.cpp -o $(OBJ)/top_scores.o

$(OBJ)/gameText.o: $(INC)/gameText.h $(SRC)/gameText.cpp
	$(CC) $(CFLAGS) -c $(SRC)/gameText.cpp -o $(OBJ)/gameText.o

$(BIN)/game: $(SRC)/game.cpp $(OBJ)/character.o $(OBJ)/asteroid.o $(OBJ)/ship.o $(OBJ)/modelLoader.o $(OBJ)/laser.o $(OBJ)/audioLoader.o $(OBJ)/top_scores.o $(OBJ)/gameText.o
	$(CC)  -o $(BIN)/game $(SRC)/game.cpp  $(OBJ)/character.o $(OBJ)/ship.o $(OBJ)/asteroid.o $(OBJ)/laser.o $(OBJ)/modelLoader.o  $(OBJ)/audioLoader.o $(OBJ)/top_scores.o $(OBJ)/gameText.o $(CFLAGS) 

doc: $(INC)/asteroid.h $(INC)/character.h $(INC)/laser.h $(INC)/ship.h $(INC)/audioLoader.h $(INC)/gameText.h $(INC)/modelLoader.h $(INC)/top_scores.h
	doxygen

clean:
	rm obj/*
	rm bin/*
	rm -rf doc/*

