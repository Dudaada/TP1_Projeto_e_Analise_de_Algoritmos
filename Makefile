CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/entrada.c src/controleNave.c src/Pecas.c
EXEC = bin/leitura_mapa

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(EXEC)
run:
	./$(EXEC)

clean:
	del $(EXEC).exe
