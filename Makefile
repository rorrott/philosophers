# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g3

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source and object files
SRC = src/main.c src/philo_msg.c src/philo_routine.c src/philo_utils.c \
		src/utils.c src/val_args.c
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
NAME = philo

GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RESET = \033[0m

# Include dependencies
.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}


# Default target
all: $(NAME)

# Linking the final executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)Compilation completed successfully!$(RESET)"

# Compiling each .c file into .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS) 
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $< 

# Clean up object files and the executable
clean:
	@rm -rf $(OBJ_DIR) $(NAME)
	@echo "$(YELLOW)Cleaned up object files and executable.$(RESET)"
	@clear

# Full clean up
fclean: clean
	@echo "$(BLUE)Full clean completed.$(RESET)"
# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re