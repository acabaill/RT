#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmartin <pmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/11 18:23:17 by pmartin           #+#    #+#              #
#    Updated: 2017/04/06 20:07:36 by pmartin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#


NAME = rtv1
CC = cc
FLAGS = -Wall -Wextra -Werror
IDIR = includes/
LMLX = -framework OpenGL -framework AppKit -framework SDL2
LIBFT = libft/
SRC := $(filter %.c, $(shell find src -type f))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@$(CC) -o $@ $^ $(FLAGS) $(LIBFT)libft.a $(LMLX) -I $(IDIR)

%.o: %.c
	@$(CC) $(FLAGS) -o $@ -c $< -I $(IDIR)

clean:
	@rm -f $(OBJ)
	@rm -f *~*
	@rm -f *#*

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all $(NAME) clean fclean re