# ==============================================================================
# MAKEFILE MULTIPLATAFORMA - SPACE DEFENDER: RETRO EDITION (RAYLIB 2D)
# ==============================================================================

# 1. COMPILADOR E FLAGS DE COMPILAÇÃO
CC       := gcc
CFLAGS   := -Wall -Wextra -std=c99 -g -Iinclude
LDFLAGS  :=

# 2. DIRETÓRIOS DO PROJETO
SRC_DIR  := src
INC_DIR  := include
OBJ_DIR  := obj
BIN_DIR  := bin

# 3. NOME DO EXECUTÁVEL FINAL
TARGET   := $(BIN_DIR)/space_defender

# 4. DETECÇÃO DO SISTEMA OPERACIONAL E CONFIGURAÇÃO DA RAYLIB
UNAME_S := $(shell uname -s)

ifeq ($(OS),Windows_NT)
    # Configuração para Windows (MinGW / MSYS2)
    TARGET   := $(BIN_DIR)/space_defender.exe
    LIBS     := -lraylib -lopengl32 -lgdi32 -lwinmm
    RM       := del /Q /F
    MD       := mkdir
    FixPath   = $(subst /,\,$1)
else
    RM       := rm -rf
    MD       := mkdir -p
    FixPath   = $1

    ifeq ($(UNAME_S),Linux)
        # Configuração para Linux (Ubuntu/Debian/Fedora/Arch)
        LIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    endif
    ifeq ($(UNAME_S),Darwin)
        # Configuração para macOS (Homebrew)
        CFLAGS  += -I/opt/homebrew/include -I/usr/local/include
        LDFLAGS += -L/opt/homebrew/lib -L/usr/local/lib
        LIBS    := -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    endif
endif

# 5. MAPEAMENTO AUTOMÁTICO DE ARQUIVOS FONTE E OBJETOS
SOURCES  := $(wildcard main.c) $(wildcard $(SRC_DIR)/*.c)
OBJECTS  := $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SOURCES)))

# Instruição de busca para o Make localizar arquivos .c na raiz e em src/
vpath %.c . $(SRC_DIR)

# ==============================================================================
# REGRAS DE COMPILAÇÃO
# ==============================================================================

# Regra principal (Default)
all: create_dirs $(TARGET)

# Linkagem do executável final
$(TARGET): $(OBJECTS)
	@echo "==> Linkando executavel final: $@"
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) $(LIBS)
	@echo "==> Compilacao do Space Defender concluida com sucesso!"

# Compilação dos arquivos de código fonte (.c) para objetos (.o)
$(OBJ_DIR)/%.o: %.c
	@echo "==> Compilando modulo: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Criação das pastas bin/ e obj/
create_dirs:
	@$(MD) $(call FixPath,$(OBJ_DIR))
	@$(MD) $(call FixPath,$(BIN_DIR))

# Limpeza de binários e objetos
clean:
	@echo "==> Limpando arquivos compilados e objetos..."
	@$(RM) $(call FixPath,$(OBJ_DIR)/*)
	@$(RM) $(call FixPath,$(BIN_DIR)/*)
	@echo "==> Limpeza concluida."

# Compila e executa o jogo
run: all
	@echo "==> Executando Space Defender..."
	@./$(TARGET)

.PHONY: all clean run valgrind create_dirs