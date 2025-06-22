CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
LDFLAGS = -lm

SRC_DIR = .
BUILD_DIR = ../build
TARGET = $(BUILD_DIR)/graph
CLANG_FORMAT = clang-format
CLANG_FORMAT_FILE = ../materials/linters/.clang-format

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
HEADERS = $(wildcard $(SRC_DIR)/*.h)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

format:
	$(CLANG_FORMAT) -i --style=file:$(CLANG_FORMAT_FILE) $(SOURCES) $(HEADERS)

test: $(TARGET)
	@echo "Enter function to test (e.g. 'sin(x)' or 'cos(2*x)') and press Ctrl+D when done:"
	@leaks --atExit -- $(TARGET)
	@cppcheck --enable=all --suppress=missingIncludeSystem ./

leaks: test

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean format test leaks