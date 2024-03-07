# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 10:29:34 by ugolin-olle       #+#    #+#              #
#    Updated: 2024/03/07 21:19:06 by ugolin-olle      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -- Variables
HDRDIR       = includes
SRCSDIR      = srcs
LIBSDIR      = libs
OBJDIR       = objs

SRC_FILES = $(wildcard $(SRCSDIR)/**/*.c)
OBJ_FILES = $(patsubst $(SRCSDIR)/%.c,$(OBJDIR)/%.o,$(SRC_FILES))
HDR_FILES    = $(wildcard $(HDRDIR)/*.h)

CC = cc
C_FLAGS = -Werror -Wall -Wextra
HDR_FLAG = $(HDR_FILES)
INC_FLAGS = -I $(HDRDIR)
RM = rm -rf
MKDIR = mkdir -p

NAME = minishell

RESET = \033[0m
BLUE = \033[0;94m
GREEN = \033[0;92m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJ_FILES) -L$(LIBSDIR) -lft -o $(NAME)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c $(HDR_FLAG) | $(OBJDIR) libft
	@echo "$(COLOR_INFO)Compiling: $< $(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(OBJDIR):
	@$(MKDIR) $(OBJDIR)
	@$(MKDIR) $(dir $(OBJ_FILES))

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
