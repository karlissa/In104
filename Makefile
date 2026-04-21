# Variables
CC = gcc
CFLAGS = -g -Wall -I include/
SRC = src
INC = include
OBJ = $(SRC)/main.o $(SRC)/functions.o $(SRC)/mazeEnv.o $(SRC)/Qlearning.o 
TARGET = $(SRC)/main

# Règle par défaut
all: $(TARGET)

# Exécutable final
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

# Compilation des fichiers .c en .o

$(SRC)/functions.o: $(SRC)/functions.c $(INC)/functions.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(SRC)/mazeEnv.o: $(SRC)/mazeEnv.c $(INC)/mazeEnv.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(SRC)/Qlearning.o: $(SRC)/Qlearning.c $(INC)/Qlearning.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Nettoyage
clean:
	rm -f $(SRC)/*.o *~

realclean: clean
	rm -f $(TARGET)