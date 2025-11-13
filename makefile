# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = obj

# Nome do executável
TARGET = main

# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
	EXE = $(TARGET).exe
	MKDIR = if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	RM = if exist "$(OBJ_DIR)\*.o" del /q "$(OBJ_DIR)\*.o" & if exist "$(EXE)" del /q "$(EXE)"
	RUN = $(EXE)
else
	EXE = $(TARGET)
	MKDIR = mkdir -p $(OBJ_DIR)
	RM = rm -f $(OBJ_DIR)/*.o $(EXE)
	RUN = ./$(EXE)
endif

# Fontes e objetos
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/menu.c \
       $(SRC_DIR)/TAD_mapa.c \
       $(SRC_DIR)/TAD_tempo.c \
       $(SRC_DIR)/TAD_trajeto.c \
       $(SRC_DIR)/GeradorDeMapas.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regra padrão
all: $(EXE)

# Linkagem final
$(EXE): $(OBJS)
	$(MKDIR)
	$(CC) $(OBJS) -o $(EXE)
	@echo ✅ Compilação concluída: $(EXE)

# Compilação dos .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	$(RM)
	@echo 🧹 Limpeza concluída.

# Executar o programa
run: all
	$(RUN)
