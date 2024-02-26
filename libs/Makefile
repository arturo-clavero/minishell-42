# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/28 11:49:44 by ugolin-olle       #+#    #+#              #
#    Updated: 2023/10/10 23:42:06 by ugolin-olle      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = srcs
OBJ_DIR = objs
INC_DIR = includes

SRC_DIRS = str nbr file misc mem
SRC_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(SRC_DIR)/$(dir)/*.c))
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC_FLAGS = -I $(INC_DIR)

NAME = libft.a

AR = ar rcs
RM = rm -rf
MKDIR = mkdir -p

RESET = \033[0m
BLUE = \033[0;94m
GREEN = \033[0;92m

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(AR) $@ $^
	@echo "$(GREEN)[OK] - Libft has been created successfully.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@
	@echo "$(BLUE)[INFO] - Compiling: $<$(RESET)"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)[OK] - Object files have been removed.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)[OK] - Libft has been removed correctly.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
