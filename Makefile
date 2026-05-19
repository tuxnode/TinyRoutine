.PHONY: all clean lib example run

CC      = gcc
CFLAGS := -Wall -Wextra -Werror -Wpedantic -O0 -g
CFLAGS += -I./include

AR      = ar
ARFLAGS = rcs

BUILD_DIR = build
LIB       = $(BUILD_DIR)/libuthread.a

LIB_OBJS  = $(BUILD_DIR)/uthread.o \
            $(BUILD_DIR)/switch.o

EXAMPLE_SRC = example/main.c
EXAMPLE_BIN = $(BUILD_DIR)/example

all: $(EXAMPLE_BIN)

lib: $(LIB)

lib: $(LIB)

# --- compile C ---
$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# --- assemble ---
$(BUILD_DIR)/%.o: src/%.S
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# --- archive ---
$(LIB): $(LIB_OBJS)
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $^

# --- example binary (links against libuthread.a) ---
$(EXAMPLE_BIN): $(EXAMPLE_SRC) $(LIB)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $< -L$(BUILD_DIR) -luthread -static

example: $(EXAMPLE_BIN)

run: $(EXAMPLE_BIN)
	./$(EXAMPLE_BIN)

# --- clean ---
clean:
	rm -rf $(BUILD_DIR)
