/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:33:35 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/01 03:00:15 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	update_player(void)
{
	t_vector	n_p_position;
	float		n_p_rotation;
	float		player_speed;
	t_vector	a;

	player_speed = g_world.player.speed;
	n_p_rotation = g_world.player.rotation.angle;
	n_p_position = g_world.player.position;
	n_p_position.x += player_speed * cos(n_p_rotation) * WALKDIRECTION;
	n_p_position.y += player_speed * sin(n_p_rotation) * WALKDIRECTION;
	n_p_rotation = norm_angle(n_p_rotation + TURNDIRECTION * PROTATIONSPEED);
	g_world.player.rotation.angle = n_p_rotation;
	a = new_vector(3, 3);
	if (walls_at(add_vectors(&n_p_position, &a)) != 1)
		g_world.player.position = n_p_position;
}

int		walls_at(t_vector coordinate)
{
	int		map_grid_index_x;
	int		map_grid_index_y;

	map_grid_index_x = coordinate.x / g_world.grid_size.width;
	map_grid_index_y = coordinate.y / g_world.grid_size.height;
	return (g_game_map[map_grid_index_y][map_grid_index_x] == '1');
}
