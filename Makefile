# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 20:01:07 by natferna          #+#    #+#              #
#    Updated: 2024/12/22 22:52:56 by natferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iminilibx
LDFLAGS = -L/System/Volumes/Data/opt/X11/lib -Lminilibx
CPPFLAGS = -I/System/Volumes/Data/opt/X11/include

MLX = -lmlx -lX11 -lXext -lm

SRCS = $(wildcard src/*.c)

INCLUD = ./includes/so_long.h \
            ./minilibx/mlx.h

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(MLX)  # Se enlaza con libmlx.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
