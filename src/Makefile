CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lm

SRC_DIR = src
BUILD_DIR = build
CLANG_FORMAT = ../build/.clang-format

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
TARGET = $(BUILD_DIR)/graph

# Основная цель (форматируем -> компилируем)
all: format $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Форматирование всех исходников
format:
	@if [ -f "$(CLANG_FORMAT)" ]; then \
		$(CLANG_FORMAT) -i $(SRC_DIR)/*.c $(SRC_DIR)/*.h; \
		echo "Форматирование завершено"; \
	else \
		echo "Ошибка: clang-format не найден по пути $(CLANG_FORMAT)"; \
		exit 1; \
	fi

# Полная очистка
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean format