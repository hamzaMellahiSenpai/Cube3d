/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 08:29:20 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/08 08:33:00 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	update_sprites()
{
	int	i;

	i = -1;
	while (++i < 1)
		g_world.sprites[i].distance = dist(g_world.sprites[i].pos , g_world.player.position);
	sort_sprites();
}

void	sort_sprites()
{
	int i;
	int j;
	t_sprite tmp;
	t_sprite *sprites;

	sprites = g_world.sprites;
	i = -1;
	while (i++ < g_world.numofsprites)
	{
		j = -1;
		while (j++ < g_world.numofsprites)
		{
			if ((sprites[j]).distance < (sprites[j + 1]).distance)
			{
				tmp = sprites[j];
				sprites[j] = sprites[j+1];
				sprites[j+1] = tmp;
			}
		}
	}
}

void	render_sprite(t_sprite sprite)
{
	unsigned int pixel;
	int i;
	int j;
	i = 0;
	while (++i < (sprite.size / 1))
	{
		if (sprite.s_x + i < 0 || sprite.s_x + i > SWIDTH)
			continue;
		if (sprite.distance >= g_world.wall_rays[(int)sprite.s_x + i].distance)
			continue;
		j = 0;
		while (++j < ((sprite.size - 2) / 1))
		{
			if (sprite.s_y + j < 0 || sprite.s_y + j > SHEIGHT)
				continue;
			if (sprite.anim.isPlayOnAwake || sprite.anim.isPlaying)
			{
				if (sprite.anim.is_loop || sprite.anim.currentframe < sprite.anim.nofframes)
					pixel = sprite.img.data[sprite.img.width * (sprite.img.height * j / (int)sprite.size) + (64  * i / (int)sprite.size)  +
					((sprite.anim.currentframe * sprite.anim.fps / 2 )% sprite.anim.nofframes) * 64];
			}
			else
				pixel = sprite.img.data[sprite.img.width * (sprite.img.height * j / (int)sprite.size) + (64  * i / (int)sprite.size)];
			if (pixel != 0)
				put_pixel(new_vector(sprite.s_x + i, sprite.s_y + j), pixel);
		}
	}
}

void    show_sprites()
{
	int		i;
	float	angle;
	t_sprite	sprite;

	i = -1;
	update_sprites();
	while (++i < g_world.numofsprites)
	{
		
		if (g_world.sprites[i].visible == 1)
		{
			g_world.sprites[i].distance = dist(g_world.sprites[i].pos , g_world.player.position);
			sprite = g_world.sprites[i];
			angle = atan2(sprite.pos.y - PLAYERPOS.y, sprite.pos.x - PLAYERPOS.x);
			while (angle - PROTATIONANGLE > M_PI)
				angle -= 2 * M_PI;
			while (angle - PROTATIONANGLE < -M_PI)
				angle += 2 * M_PI;
			if (g_screen.height > g_screen.width)
				sprite.size = (SHEIGHT / sprite.distance) * BLOCK_SIZE;
			else
				sprite.size = (SWIDTH / sprite.distance) * BLOCK_SIZE;
			sprite.s_y = (SHEIGHT - sprite.size) / 2 + g_world.player.offset;
			sprite.s_x = (angle - PROTATIONANGLE) * (SWIDTH / VIEW_ANGLE) + (SWIDTH / 2 
				- sprite.size / 2);
			render_sprite(sprite);
		}
	}
}