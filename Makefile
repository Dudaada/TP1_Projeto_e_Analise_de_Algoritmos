CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/entrada.c
EXEC = leitura_mapa

all:
	$(CC) $(SRC) $(CFLAGS) -o $(EXEC)

run:
	./$(EXEC)

clean:
	del $(EXEC).exe


