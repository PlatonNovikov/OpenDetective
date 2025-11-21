# Установки для компилятора
CC = gcc
CFLAGS = -Wall -Wextra -g

# Папки
OBJ_DIR = obj
BIN_DIR = bin

# Исходные и объектные файлы
SRC = structures.c city.c npc.c generators.c saveload.c ui.c OpenDetective.c 
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Имя конечной программы
TARGET = $(BIN_DIR)/OpenDetective

# Правило по умолчанию
all: $(TARGET)

# Правило для компиляции конечной программы
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)  # Создаём папку bin, если её нет
	$(CC) $(OBJ) -o $@

# Правило для компиляции каждого .c файла в .o
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)  # Создаём папку obj, если её нет
	$(CC) $(CFLAGS) -c $< -o $@

# Команда для запуска программы
run: $(TARGET)
	@$(BIN_DIR)/OpenDetective

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Очистка только объектных файлов
clean-obj:
	rm -rf $(OBJ_DIR)

# Очистка только исполнимого файла
clean-bin:
	rm -rf $(BIN_DIR)

# Псевдоним для очистки
.PHONY: all clean clean-obj clean-bin run
