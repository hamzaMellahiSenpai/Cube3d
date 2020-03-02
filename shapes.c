/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 03:10:00 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/01 04:08:43 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_traingle(t_vector *a, t_vector *b, t_vector *c, int color)
{
	line(a->x, a->y, b->x, b->y, color);
	line(b->x, b->y, c->x, c->y, color);
	line(c->x, c->y, a->x, a->y, color);
}

void	rect(t_vector position, float width, float height, int color)
{
	int start;

	start = position.y - 1;
	while (++start < height)
		line(position.x, position.y + start,
		position.x + width, position.y + start, color);
}

void	draw_square(int row, int col, t_shape grid_size)
{
	double y;
	double max_y;
	double max_x;
	double x;

	max_x = col * grid_size.width + grid_size.width;
	max_y = row * grid_size.height + grid_size.height;
	y = row * grid_size.height;
	while (y < max_y)
	{
		x = grid_size.width * col;
		while (x < max_x)
			put_pixel(new_vector(x++, y), 0x4B77BE);
		y++;
	}
}

void	circle(t_vector a, int radius, int color)
{
	int		col;
	float	angle;
	float	step;

	col = 0;
	angle = -2 * M_PI;
	step = 2 * M_PI / (float)g_screen.width;
	while (col <= g_screen.width)
	{
		line(a.x, a.y, a.x + radius * cos(angle),
		a.y + radius * sin(angle), color);
		angle += step;
		col++;
	}
}

void	line(int x0, int y0, int x1, int y1, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	xinc;
	float	yinc;
	int		i;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	xinc = dx / (float)steps;
	yinc = dy / (float)steps;
	i = -1;
	while (++i <= steps)
	{
		put_pixel(new_vector(x0, y0), color);
		x0 += xinc;
		y0 += yinc;
	}
}
