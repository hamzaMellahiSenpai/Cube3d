/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 03:44:13 by marvin            #+#    #+#             */
/*   Updated: 2020/03/25 03:44:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	draw_cursor()
{
	int i;

	i = -1;
	while (++i < 60)
    {
		put_pixel(new_vector(SWIDTH / 2 - i, SHEIGHT / 2), RED);
		put_pixel(new_vector(SWIDTH / 2 - 30, SHEIGHT / 2 - i + 30), RED);
    }
}

void    draw_weapon()
{
    float ystep = g_world.sprites[0].img.height / (SHEIGHT / 3);
	float xStep = g_world.sprites[0].img.width / (SWIDTH / 3);
	float f = 0;
    float x = 0;
    int i = -1;
    int j;
	while (++i < (SWIDTH / 3))
	{
		j = 0;
		f = 0;
		while (++j < (SHEIGHT / 3))
		{
			int pixel = g_world.sprites[0].img.data[(int)f * g_world.sprites[0].img.width + (int)x];
			if (pixel != 0)
				put_pixel(new_vector(i - g_world.sprites[0].img.width, j) , pixel);
			f += (float)ystep;
		}
		x += xStep;
	}
    draw_cursor();
}