# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR)

# Ficheiros fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Nome do executável
TARGET = $(BIN_DIR)/main

# Regra principal
all: $(TARGET)

# Como construir o executável
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compilar os .c para .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Garantir diretórios
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# executar o programa
run: all
	./bin/main

# Limpar
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# Limpeza completa
mrproper: clean
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean mrproper