# Установки для компилятора
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm

# Папки
OBJ_DIR = obj
BIN_DIR = bin

# Исходные и объектные файлы
SRC =	src/structures.c \
		src/city.c \
		src/npc.c \
		src/generators.c \
		src/saveload.c \
		src/ui.c \
		src/OpenDetective.c \
		src/rand/zurand.c \
		src/vector/vector.c
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Имя конечной программы
TARGET = $(BIN_DIR)/OpenDetective

# Правило по умолчанию
all: $(TARGET)

# Правило для компиляции конечной программы
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)  # Создаём папку bin, если её нет
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Правило для компиляции каждого .c файла в .o
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)  # Создаём папку obj, если её нет
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

re: clean all

# Псевдоним для очистки
.PHONY: all clean clean-obj clean-bin run
