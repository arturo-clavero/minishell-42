# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 10:29:34 by ugolin-olle       #+#    #+#              #
#    Updated: 2024/03/10 16:20:35by ugolin-olle      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -- Compilation
INCDIR       = includes
SRCSDIR      = srcs
LIBSDIR      = libs
OBJDIR       = objs
SRC_FILES    = $(wildcard $(SRCSDIR)/*.c) $(wildcard $(SRCSDIR)/**/*.c)
HDR_FILES    = $(wildcard $(INCDIR)/*.h)
OBJ_FILES    = $(patsubst $(SRCSDIR)/%.c, $(OBJDIR)/%.o, $(SRC_FILES))
INC_FILES    = -I $(INCDIR) -I $(LIBSDIR)/includes #-I/opt/homebrew/Cellar/readline/8.2.10/include
LIBS_FLAGS   = -L$(LIBSDIR) -lft -lreadline #-L/opt/homebrew/Cellar/readline/8.2.10/lib

# -- Compilation flags
CC = cc
C_FLAGS = -Werror -Wall -Wextra
RL_FLAGS = -l readline
RM = rm -rf
MKDIR = mkdir -p
NAME = minishell

# -- Colors
RESET = \033[0m
BLUE = \033[0;94m
GREEN = \033[0;92m
PURPLE = \033[0;95m

.PHONY: all re clean fclean norm

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(C_FLAGS) $(OBJ_FILES) $(INC_FILES) $(LIBS_FLAGS) $(RL_FLAGS) -o $@

$(OBJDIR)/%.o: $(SRCSDIR)/%.c $(HDR_FILES) | libft
	@$(MKDIR) $(dir $@)
	@$(CC) $(C_FLAGS) $(INC_FILES) -c $< -o $@
	@echo "$(BLUE)[COMPILING] - $< $(RESET)"
libft:
	@make -C $(LIBSDIR)

clean:
	@$(RM) $(OBJDIR)
	@make clean -C $(LIBSDIR)
	@echo "$(PURPLE)[INFO] -				$(NAME) object files cleaned!$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBSDIR)
	@echo "$(PURPLE)[INFO] -				$(NAME) executable has been cleaned!$(RESET)"

norm:
	@norminette $(SRCSDIR) $(INCDIR)

re: fclean all
	@echo "$(PURPLE)[INFO] -				Cleaned and rebuilt successfully!$(RESET)"
