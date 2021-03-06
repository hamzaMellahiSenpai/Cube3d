/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:33:35 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/25 04:25:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int		look_for_sp(int x, int y)
{
	for (int i = 0;i<g_world.numofsprites;i++)
		if (g_world.sprites[i].pos_in_map.x == x &&
			g_world.sprites[i].pos_in_map.y == y)
			return i;
	return -1;
}

void	Destroy(int x, int y)
{
	g_game_map[y][x] = '0';
	g_world.sprites[look_for_sp(x,y)].visible = 0;
}

void	Die()
{
	// Show Game Over Menu with blood 
}

void	damage(int amount)
{
	g_world.player.health -= amount;
	if (g_world.player.health <= 0)
		Die();
}

void	heal(int amount)
{
	if (g_world.player.currenthealth + amount <= g_world.player.maxhealth)
		g_world.player.currenthealth += amount;
}


int		object_at(t_vector coordinate)
{
	int		x;
	int		y;
	int		i;

	x = coordinate.x / g_world.grid_size.width;
	y = coordinate.y / g_world.grid_size.height;
	if (x == 2 && y == 2)
		return 0;
	if (g_game_map[y][x] == 'C')
	{
		//tpid = fork();
		//if (tpid == 0)
		//	system("mpg123 -q assets/sounds/coin.mp3");
		Destroy(x,y);
	}
	else if (g_game_map[y][x] == 'T')
	{
		damage(10);
		Destroy(x,y);
	}
	else if (g_game_map[y][x] == 'H')
	{
		heal(10);
		Destroy(x,y);
	}
	return (ft_strchr("1THU", g_game_map[y][x]) == NULL ? 0 : 1);
}

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
	if (object_at(add_vectors(&n_p_position, &a)) != 1)
		g_world.player.position = n_p_position;
}

int		wall_at(t_vector coordinate)
{
	int		map_grid_index_x;
	int		map_grid_index_y;

	map_grid_index_x = coordinate.x / g_world.grid_size.width;
	map_grid_index_y = coordinate.y / g_world.grid_size.height;
	return (g_game_map[map_grid_index_y][map_grid_index_x] == '1');
}


int		is_out_of_window(t_vector A)
{
	int height = g_world.rows * g_world.grid_size.height;
  	int width = g_world.cols * g_world.grid_size.width;
	if (A.x <= width && A.y <= height && A.x >= 0 && A.y >= 0)
		return (0);
	return (1);
}