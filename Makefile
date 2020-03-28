# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 23:25:02 by hmellahi          #+#    #+#              #
#    Updated: 2020/03/10 23:05:48 by hmellahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =#  -Wall -Wextra -Werror
ARG = -c
SRC = maths.c player.c vector.c main.c
CC  = @gcc
#MLX = -lmlx -framework OpenGL -framework AppKit -g
#MLX = -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lm -lmlx
MLX = -lm -lmlx -lXext -lX11

all:
	gcc -g *.c  */*.c -D BUFFER_SIZE=1 $(FLAGS) $(MLX) -fsanitize=address
clean:
	rm -rf *.o
