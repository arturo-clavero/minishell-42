# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 10:29:34 by ugolin-olle       #+#    #+#              #
#    Updated: 2024/02/26 10:34:22 by ugolin-olle      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -- Variables
HDRDIR       = includes
SRCSDIR      = srcs
LIBSDIR      = libs
OBJDIR       = objs

SRC_FILES = $(wildcard $(SRCSDIR)/**/*.c)
OBJ_FILES = $(patsubst $(SRCSDIR)/%.c,$(OBJDIR)/%.o,$(SRC_FILES))

CC = cc
C_FLAGS = -Werror -Wall -Wextra
HDR_FLAG = includes/minishell.h
INC_FLAGS = -I $(HDRDIR)
RM = rm -rf
MKDIR = mkdir -p

NAME = minishell

RESET = \033[0m
BLUE = \033[0;94m
GREEN = \033[0;92m

.PHONY: all clean fclean re

$(NAME): $(OBJ_FILES)
	@echo "$(COLOR_INFO)Linking: $(NAME) $(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJ_FILES) -L$(LIBSDIR) -lft -o $(NAME)
	@echo "$(COLOR_SUCCESS)$(NAME) has been successfully compiled$(COLOR_RESET)"

$(OBJDIR)/%.o: $(SRCSDIR)/%.c $(HDRFLAG) | $(OBJDIR) libft
	@echo "$(COLOR_INFO)Compiling: $< $(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(OBJDIR):
	@$(MKDIR) $(OBJDIR)

libft:
	@make -C $(LIBSDIR)

clean:
	@$(RM) $(OBJDIR)
	@make clean -C $(LIBSDIR)
	@echo "$(COLOR_INFO)$(NAME) object files cleaned!$(COLOR_RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBSDIR)
	@echo "$(COLOR_SUCCESS)$(NAME) executable has been cleaned!$(COLOR_RESET)"

norm:
	@norminette $(SRCSDIR) $(HDRDIR)

re: fclean all
	@echo "$(COLOR_SUCCESS)Cleaned and rebuilt successfully!$(COLOR_RESET)"
