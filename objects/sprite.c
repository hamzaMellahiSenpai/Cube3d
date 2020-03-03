/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 08:29:20 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/03 09:06:21 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void    show_sprites()
{
	int		i;
	float	angle;
	float	sprite_x;
	float	sprite_y;
	float	sprite_dist;

	i = -1;
	while (++i < 1)
	{
		sprite_x = g_world.sprites[i].pos.y;
		sprite_y = g_world.sprites[i].pos.x;
		sprite_dist =  g_world.sprites[i].distance;
		angle = atan2(sprite_y - PLAYERPOS.y, sprite_x - PLAYERPOS.x);
		while (angle - PROTATIONANGLE > 2 * M_PI)
			angle -= 2 * M_PI;
		while (angle - PROTATIONANGLE < 2 * M_PI)
			angle += 2 * M_PI;
		if (g_screen.height > g_screen.width)
			g_world.sprites[i].size = g_screen.height / sprite_dist * BLOCK_SIZE;
		else
			g_world.sprites[i].size = g_screen.height / sprite_dist * BLOCK_SIZE;
		g_world.sprites[i].pos.y = SHEIGHT - g_world.sprites[i].size;
		//g_world.sprites[i].pos.x = (s);
		//X    = (sp_angle - (g_player.rotation_angle[RAD])) * g_game_data.res.width / (FOV_ANGLE[RAD]) + (g_game_data.res.width / 2 - SIZE / 2);

		render_sprite(g_world.sprites[i]);
	}
}