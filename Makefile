# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 23:25:02 by hmellahi          #+#    #+#              #
#    Updated: 2020/03/10 03:41:15 by hmellahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =  -Wall -Wextra -Werror
ARG = -c
SRC = maths.c player.c vector.c main.c
CC  = @gcc
#MLX = -lmlx -framework OpenGL -framework AppKit -g
MLX = -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lm
all:
	#$(CC) $(ARG) $(SRC) $(MLX)
	#@gcc -g rendering.c lst.c effects.c events_handler.c ui.c shapes.c main.c maths.c player.c vector.c ray.c Read_file.c ft_split.c func_utils.c func_utils2.c get_next_line.c errors.c -D BUFFER_SIZE=1 $(MLX) -fsanitize=address
	#./a.out "l.cub" -D BUFFER_SIZE=1 $(MLX) -fsanitize=address
	gcc -g -D L_C=N *.c  */*.c -D BUFFER_SIZE=1 $(MLX) -fsanitize=address
clean:
	rm -rf *.o
