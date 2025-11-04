# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = obj

# Arquivos
TARGET = main.exe
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/TAD_mapa.c
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/TAD_mapa.o

# Regra padrão
all: $(TARGET)

# Compila o executável
$(TARGET): $(OBJS)
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(CC) $(OBJS) -o $(TARGET)
	@echo ✅ Programa compilado com sucesso: $(TARGET)

# Compila cada .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza (compatível com Windows)
clean:
	if exist "$(OBJ_DIR)\*.o" del /q "$(OBJ_DIR)\*.o"
	if exist "$(TARGET)" del /q "$(TARGET)"
	@echo 🧹 Limpeza concluída.

# Executar
run:
