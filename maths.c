/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 23:34:12 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/01 03:35:45 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int *g_p;

void			put_pixel(t_vector a, int color)
{
	if (a.x < g_screen.width && a.y < g_screen.height && a.x >= 0 && a.y >= 0)
		g_p[(int)a.x + (int)a.y * (int)g_screen.width] = color;
}

void			update_field_of_view(void)
{
	t_ray		ray;
	int			col;
	t_ray		rays[(int)g_screen.width];
	float		ray_angle;
	float		step;

	ray_angle = (g_world.player.rotation.angle - VIEW_ANGLE / 2);
	step = (float)VIEW_ANGLE / (float)g_screen.width;
	ray = new_ray(ray_angle);
	col = 0;
	while (col <= g_screen.width)
	{
		ray.angle = norm_angle(ray_angle);
		cast(&ray, col);
		rays[col] = ray;
		ray_angle += step;
		col++;
	}
}

float			modulo(float num, float divisor)
{
	float		rem;
	int			i;

	if (divisor == 0)
	{
		perror("Error: divisor can't be zero \n");
		exit(0);
	}
	i = 0;
	while (divisor * i < num)
		i++;
	rem = num - divisor * (i - 1);
	return (rem);
}

float			norm_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

int				rgb_to_int(int r, int g, int b)
{
	return (r * 256 * 256 + g * 256 + b);
}
