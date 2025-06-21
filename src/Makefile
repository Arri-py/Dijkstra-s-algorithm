CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -std=c11 -g
LDFLAGS = -lm

SRC_DIR = .
BUILD_DIR = ../build
CLANG_FORMAT = clang-format
STYLE_FILE = ../materials/linters/.clang-format

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
TARGET = $(BUILD_DIR)/graph

all: format $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

format:
	@if [ -f "$(STYLE_FILE)" ]; then \
		$(CLANG_FORMAT) -style=file:$(STYLE_FILE) -i $(SRC_DIR)/*.c $(SRC_DIR)/*.h 2>/dev/null || echo "Форматирование завершено"; \
	else \
		echo "Ошибка: файл стиля не найден по пути $(STYLE_FILE)"; \
		exit 1; \
	fi

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean format