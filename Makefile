# Compilador e flags
CC = gcc
CFLAGS = -Wall -Iinclude

# Arquivos-fonte (todos os .c da pasta src)
SRC = $(wildcard src/*.c)

# Nome base do executável
EXEC_BASE = leitura_mapa

# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    EXEC = $(EXEC_BASE).exe
    RM = del /f /q
    RUN = $(EXEC)
else
    EXEC = $(EXEC_BASE)
    RM = rm -f
    RUN = ./$(EXEC)
endif

# Alvo padrão
all: $(EXEC)

# Regra de compilação
$(EXEC): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(EXEC)

# Executar o programa
run: all
	$(RUN)

# Limpar os arquivos gerados
clean:
	$(RM) $(EXEC)
