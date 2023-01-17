# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 15:28:36 by isojo-go          #+#    #+#              #
#    Updated: 2023/01/17 11:48:20 by isojo-go         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Makefile structure ---

## Program Name:
NAME		=	libft.a

## Libraries:

## Header Files (dedicated and from libraries):
HEADERS	=	-I ./inc

## Source Files:
SRCS	=	$(shell find ./src -name "*.c")
OBJS	=	$(SRCS:.c=.o)

## Compilation flags:
CC			=	gcc
AR			=	ar rc
CFLAGS		=	-Wall -Wextra -Werror
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

$(NAME):	$(OBJS)
			@$(AR) $(NAME) $(OBJS)
			@echo "$(GREEN)extended libft compiled!$(DEF_COLOR)"
			@echo "$(CYAN)             w                  8          8    8 w 8     d8b  w   "
			@echo ".d88b Yb dP w8ww .d88b 8d8b. .d88 .d88b .d88    8 w 88b.  8'  w8ww "
			@echo "8.dP'  \`8.   8   8.dP' 8P Y8 8  8 8.dP' 8  8    8 8 8  8 w8ww  8   "
			@echo "\`Y88P dP Yb  Y8P \`Y88P 8   8 \`Y88 \`Y88P \`Y88    8 8 88P'  8    Y8P "
			@echo "                                                               $(DEF_COLOR)"

%.o: %.c
			@printf "$(BLUE)Compiling: $(notdir $<) ...$(DEF_COLOR)"
			@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
			@echo "$(GREEN)Done!$(DEF_COLOR)"

clean:
			@$(RM) $(OBJS)
			@echo "$(YELLOW)$(NAME) object files removed!$(DEF_COLOR)"

fclean:		clean
			@$(RM) $(NAME)
			@echo "$(RED)$(NAME) removed!$(DEF_COLOR)"

re:			fclean all

.PHONY:		all clean fclean re
