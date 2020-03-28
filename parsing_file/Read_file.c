/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 13:55:39 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/25 04:17:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	fillCell(int x, int y, char type)
{
	if (g_game_map[y][x] == '0')
		g_game_map[y][x] = type;
	else
		return (handle_error(INVALID_SPRITE_PLACEMENT, FAIL));
}

void	get_player_pos(t_string line,int row)
{
	t_string	str;
	int			col;

	str = "NSWE";
	col = 0;
	while (*str)
	{
		if (ft_strchr(line, *str))
		{
			if (g_infos[player_position]++)
				return (handle_error(DUPLICATE_PLAYER, FAIL));
			else
			{
				while (*line++ != *str)
					col++;
				PLAYERPOS = new_vector(BLOCK_SIZE * col + BLOCK_SIZE / 2,
				BLOCK_SIZE * row + BLOCK_SIZE / 2);
				if (*str == 'N')
					g_world.player.rotation.angle = 90;
				else if (*str == 'S')
					g_world.player.rotation.angle = -90;
				else if (*str == 'E')
						g_world.player.rotation.angle = 180;
			}
		}
		str++;
	}
}

void 	put_sprites_in_map()
{
	int	i;
	t_sprite sprite;

	i = -1;
	while (++i < g_world.numofsprites)
	{
		sprite = g_world.sprites[i];
		//printf("[%c]\n", g_game_map[(int)sprite.pos_in_map.y][(int)sprite.pos_in_map.x]);
		//print_vector(sprite.pos_in_map);
		fillCell(sprite.pos_in_map.y, sprite.pos_in_map.x, sprite.type);
	}
}

void    read_file(t_string file_name)
{
	int fd;
	char *line;
	int size;
	char **tab;
	t_string tmp;

	init_errors();
	tab = ft_split(file_name, '.');
	if (ft_strcmp(tab[tablen((void**)tab) - 1] , "cub") != 0)
	    handle_error(INVALID_FILE_NAME, FAIL);
	get_rows_cols(file_name);
	allocate_map();
	fill_map(file_name, line);
	put_sprites_in_map();
	//check_closed_map();
}
