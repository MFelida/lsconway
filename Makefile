SRC_DIR := src
OBJ_DIR := obj
INC_DIR := inc
BIN_DIR := bin

BIN := conway
TARGET := $(BIN_DIR)/$(BIN)
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CC := cc
CPPFLAGS := -Iinc -MMD -MP
CFLAGS := -Wall -Wextra -g
LDLIBS := -lSDL2

.PHONY: all re clean fclean

-include $(DEPS)

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	@ rm -f $(OBJS)

fclean: clean
	@ rm -f $(TARGET)

re: clean all