/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 08:29:20 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/05 04:34:13 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	update_sprites()
{
	int	i;

	i = -1;
	while (++i < 1)
		g_world.sprites[i].distance = dist(g_world.sprites[i].pos , g_world.player.position);
	//sort_sprites(&g_world.sprites, 1);
}

void	sort_sprites(t_sprite **sprites, int n)
{
	int i;
	int j;
	t_sprite tmp;

	i = -1;
	while (i++ < n - 1)
	{
		j = -1;
		while (j++ < n)
		{
			if ((*sprites[j]).distance > (*sprites[j + 1]).distance)
			{
				tmp = *sprites[j];
				*sprites[j] = *sprites[j+1];
				*sprites[j+1] = tmp;
			}
		}
	}
}

void	render_sprite(t_sprite sprite)
{
	int pixel;
	int i;
	int j;

	//init_sprite(k, &x_s, &y_s);
	i = -1;
	//printf("%f\n", sprite.size);
	update_sprites();
	while (++i < sprite.size)
	{
		if (sprite.s_x + i < 0 || sprite.s_x + i > SWIDTH)
			continue;
		//if (sprite.distance >= g_world.wall_rays[(int)sprite.pos.x + i].distance)
		//	continue;
		j = -1;
		while (++j < sprite.size)
		{
			pixel = sprite.img.data[(int)sprite.size * j * sprite.img.width + i * (int)sprite.size ];
			if (pixel != 0)
				//if (((sprite.s_x + i) >= 0 && (sprite.s_y + i) < SWIDTH) &&
				//	((y + j) >= 0 && (y  + j) < SHEIGHT))
					put_pixel(new_vector(sprite.s_x + i, sprite.s_y + j), pixel);
			//printf("%d | %d \n", sprite.s_x + i, sprite.s_y + j);
		}
	}
}

void    show_sprites()
{
	int		i;
	float	angle;
	t_sprite	sprite;

	i = -1;
	while (++i < 1)
	{
		g_world.sprites[i].distance = dist(g_world.sprites[i].pos , g_world.player.position);
		sprite = g_world.sprites[i];
		angle = atan2(sprite.pos.y - PLAYERPOS.y, sprite.pos.x - PLAYERPOS.x);
		//print_vector(sprite.pos);
		//print_vector(g_world.player.position);
		while (angle - PROTATIONANGLE > M_PI)
			angle -= 2 * M_PI;
		while (angle - PROTATIONANGLE < -M_PI)
			angle += 2 * M_PI;
		if (g_screen.height > g_screen.width)
		 	sprite.size = (SHEIGHT / sprite.distance) * BLOCK_SIZE;
		else
			sprite.size = (SWIDTH / sprite.distance) * BLOCK_SIZE;
		sprite.s_y = (SHEIGHT - sprite.size) / 2;
		sprite.s_x = (angle - PROTATIONANGLE) * (SWIDTH / VIEW_ANGLE) + (SWIDTH / 2 
			- sprite.size / 2);
		//printf("%f\n", angle);
		//printf("%d | %d | %f \n", sprite.s_x, sprite.s_y, sprite.size);
		//print_vector(sprite.pos);
		render_sprite(sprite);
	}
}