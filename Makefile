# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isojo-go <isojo-go@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/20 16:19:35 by isojo-go          #+#    #+#              #
#    Updated: 2023/03/13 08:25:58 by isojo-go         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Makefile structure ---

## Program Name:
NAME	=	minishell

## Folder Structure:
SRCDIR	=	src
OBJDIR	=	obj
BINDIR	=	bin

## Libraries:
LIBFT	=	./lib/LIBFT

# to compile in Urduliz:
LIBS	=	$(LIBFT)/libft.a -lreadline -L/System/Volumes/Data/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/lib

# to compile in my personal laptop:
# LIBS    =   $(LIBFT)/libft.a -lreadline -L/opt/homebrew/opt/readline/lib

## Header Files (dedicated and from libraries):

# to compile in Urduliz:
HEADERS	=	-I ./inc -I $(LIBFT)/inc -I/System/Volumes/Data/sgoinfre/goinfre/Perso/$(USER)/homebrew/opt/readline/include

# to compile in my personal laptop:
# HEADERS =   -I ./inc -I $(LIBFT)/inc -I/opt/homebrew/opt/readline/include


## Source Files:
SRC	=	$(wildcard $(SRCDIR)/*.c)
OBJ	=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

## Compilation flags:
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address
RM			=	rm -rf

## Extras:
### Colors:
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;31m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# **************************************************************************** #

# --- Makefile instructions ---

all:		$(NAME)

$(NAME):	libft $(OBJ)
			@mkdir -p $(BINDIR)
			@$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o ./$(BINDIR)/$(NAME)
			@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

libft:
			@$(MAKE) -C $(LIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p $(OBJDIR)
			@printf "$(BLUE)Compiling: $< ...$(DEF_COLOR)"
			@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
			@echo "$(GREEN)Done!$(DEF_COLOR)"

clean:
			@$(RM) $(OBJ) $(OBJDIR)
			@echo "$(YELLOW)$(NAME) object files removed!$(DEF_COLOR)"
			@$(MAKE) -C $(LIBFT) clean

fclean:
			@$(MAKE) -C $(LIBFT) fclean
			@if [ -d $(OBJDIR) ]; then \
				$(RM) $(OBJ) $(OBJDIR); \
				echo "$(YELLOW)$(NAME) object files removed!$(DEF_COLOR)"; \
			fi
			@$(RM) $(NAME) $(BINDIR)
			@echo "$(RED)$(NAME) removed!$(DEF_COLOR)"

re:			fclean all

.PHONY:		all clean fclean re libft