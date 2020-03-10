/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 08:29:20 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/10 04:04:51 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	update_sprites(void)
{
	int	i;

	i = -1;
	while (++i < 1)
		g_world.sprites[i].distance = dist(g_world.sprites[i].pos, g_world.player.position);
	sort_sprites();
}

void	sort_sprites(void)
{
	int			i;
	int			j;
	t_sprite	tmp;
	t_sprite	*sprites;

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
	unsigned int	pixel;
	int				i;
	int				j;

	i = 0;
	int sp_height = sprite.img.height / sprite.n;
	int sp_width = sprite.img.width / sprite.anim.nofframes;
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
					pixel = sprite.img.data[sprite.img.width * (sp_height * j / (int)sprite.size) + (sp_width  * i / (int)sprite.size)  +
					((sprite.anim.currentframe * sprite.anim.fps / 100) % sprite.anim.nofframes) * sp_width + sp_height * sprite.y_offset * sprite.img.width];
			}
			else
				pixel = sprite.img.data[sprite.img.width * (sprite.img.height * j / (int)sprite.size) + (sprite.img.width / sprite.anim.nofframes  * i / (int)sprite.size)];
			if (pixel != sprite.bc)
				put_pixel(new_vector(sprite.s_x + i, sprite.s_y + j), shadow(pixel, sprite.distance));
		}
	}
}

void    show_sprites()
{
	int			i;
	float		angle;
	t_sprite	sprite;

	i = -1;
	while (++i < g_world.numofsprites)
	{
		
		if (g_world.sprites[i].visible == 1)
		{
			g_world.sprites[i].distance = dist(g_world.sprites[i].pos, g_world.player.position);
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
			if (g_world.sprites[i].is_static == 0)
			{
				sprite.s_y = (SHEIGHT - sprite.size) / 2 + g_world.player.offset;
				sprite.s_x = (angle - PROTATIONANGLE) * (SWIDTH / VIEW_ANGLE) + (SWIDTH / 2 
				- sprite.size / 2);
			}
			else
			{
				if (sprite.type == 'G')
				{
					sprite.size = 200;
					sprite.s_x = SWIDTH/3;
					sprite.s_y = SHEIGHT *2/3;
				}
				else if (sprite.type == 'B')
				{
					sprite.size = 50;
					sprite.s_x = SWIDTH / 20;
					sprite.s_y = SHEIGHT / 20;
					sprite.distance = 0;
				}
				
				//sprite.distance = 0;
				//printf("%d | %d\n", sprite.anim.is_running, sprite.anim.is_loop);
			}			
			render_sprite(sprite);
		}
	}
}