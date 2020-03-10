/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 13:55:39 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/10 03:56:53 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <fcntl.h>

void    read_resolution(t_string line)
{
	if (g_infos[resolution]++)
		return (handle_error(MISSING_INFO, FAIL));
	g_screen.width = ft_atoi(line + 2);
	g_screen.height = ft_atoi(line + 3 + numofdigits(g_screen.width));
}

void	load_image(int i, t_string path, int type)
{
	check_for_file(path);
	if (type == TEXTURE)
	{
		g_textures[i].img = mlx_xpm_file_to_image(g_mlx, path, &g_textures[i].width, &g_textures[i].height);
		g_textures[i].data = (int *)mlx_get_data_addr(g_textures[i].img, &g_textures[i].bits_per_pixel, &g_textures[i].bits_per_pixel, &g_textures[i].endian);
	}
	else if(type == SPRITE)
	{
		g_world.sprites[i].img.img = mlx_xpm_file_to_image(g_mlx, path, &g_world.sprites[i].img.width, &g_world.sprites[i].img.height);
	 	g_world.sprites[i].img.data = (int *)mlx_get_data_addr(g_world.sprites[i].img.img, &g_world.sprites[i].img.bits_per_pixel, &g_world.sprites[i].img.bits_per_pixel, &g_world.sprites[i].img.endian);
		g_world.sprites[i].visible = 1;
	}
}

void	fillCell(int x, int y, char type)
{
	printf("[%d] | [%d] | [%c]\n",x,y,g_game_map[y][x]);
	if (g_game_map[y][x] == '0')
		g_game_map[y][x] = type;
	else
		return (handle_error(INVALID_SPRITE_PLACEMENT, FAIL));
}

int		tab_len(void **tab)
{
	int i;

	i = 0;
	while (*tab)
		i++;
	return (i);
}

void	load_texture(t_string line, int index)
{
	t_string path;
	t_string *tab;

	if (g_infos[index])
		return (handle_error(DUPLICATE_TEXTURE, FAIL));
	tab = ft_split(line, ' ');
	if (tab[1])
	{
		path = ft_strjoin(tab[1], ".xpm", 3);
		load_image(index, path, TEXTURE);
		printf("%s has been loaded\n", path);
	}
	else
		return (handle_error(INVALID_PATH, FAIL));
}

void	load_sprite(t_string line, int index)
{
	t_string *tab;
	t_sprite sprite;
	t_string *tab2;

	tab = ft_split(line, '|');
	tab2 = ft_split(tab[0], ' ');
	sprite.path = ft_strjoin(tab2[1], ".xpm", 3);
	sprite.type = tab2[0][1];
	sprite.anim.isPlayOnAwake = ft_atoi(tab[3]);
	sprite.anim.is_running = sprite.anim.isPlayOnAwake ? 1 : 0;
	sprite.anim.nofframes = ft_atoi(tab[4]);
	sprite.anim.is_loop = ft_atoi(tab[5]);
	sprite.anim.fps = ft_atoi(tab[6]);
	sprite.n = ft_atoi(tab[7]);
	sprite.bc = ft_atoi(tab[8]);
	sprite.pos_in_map = new_vector(ft_atoi(tab[1]), ft_atoi(tab[2]));
	sprite.pos.x = sprite.pos_in_map.x * BLOCK_SIZE + BLOCK_SIZE / 2;
	sprite.pos.y = sprite.pos_in_map.y * BLOCK_SIZE + BLOCK_SIZE / 2;
	sprite.anim.currentframe = 0;
	sprite.is_static = (sprite.type == 'G' || sprite.type == 'B') ? 1 : 0;
	sprite.y_offset = tab2[0][1] == 'G' ? 1 : 0;
	g_world.sprites[index - 4 + g_world.numofsprites] = sprite;
	load_image(index - 4 +  g_world.numofsprites, sprite.path, SPRITE);
	//printf("[%d | %d | %d | %d]\n", sprite.bc, sprite.anim.nofframes, sprite.anim.is_loop, sprite.anim.fps);
	fillCell(sprite.pos_in_map.x,sprite.pos_in_map.y,sprite.type);
	g_world.numofsprites++;
	printf("%s has been loaded\n", sprite.path);
}

void    read_image(t_string line, int index)
{
	t_string *tab;
	t_sprite sprite;
	t_string *tab2;

	if (index <= 3)
		load_texture(line, index);
	else
		load_sprite(line, index);
	g_infos[index]++;
}

void    read_color(t_string line, int index, int space)
{
	t_string *colors;

	if (g_infos[index]++)
		 return (handle_error(DUPLICATE_COLOR, FAIL));
	colors = ft_split(line + 2, ',');
	g_world.colors[space] = rgb_to_int(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	//free_space(colors);
}

void    check_for_info(t_string line)
{
	if (*line == 'R')
		read_resolution(line);
	else if (line[0] == 'N')
		read_image(line, north_texture);
	else if (line[0] == 'S' && line[1] == 'O')
		read_image(line, south_texture);
	else if (line[0] == 'W')
		read_image(line, east_texture);
	else if (line[0] == 'E')
		read_image(line, west_texture);
	else if (line[0] == 'S')
		read_image(line, sprite_texture);
	else if (line[0] == 'F')
		read_color(line, floor_color, ground);
	else if (line[0] == 'C')
		read_color(line, ceil_color, skybox);
}

void    check_missing_info()
{
	for (int i = 0;i<9;i++)
		if (g_infos[i] == 0)
			handle_error(MISSING_INFO, FAIL);
}

void    read_file(t_string file_name)
{
	int fd;
	char *line;
	int size;
	char **tab;

	tab = ft_split(file_name, '.');
	//if (ft_strcmp(tab[sizeof(tab) / sizeof(tab[0]) - 1] , "cub") != 0)
	//    handle_error(INVALID_FILE_NAME, FAIL);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		handle_error(NON_EXISTENECE_FILE, FAIL);
	int j = 0;
	int i;
	int x = 1;
	//char *p = "wsne";
	while (x > 0)
	{
		x = get_next_line(fd, &line);
		if (*line == '0')
			handle_error(INVALID_MAP, FAIL);
		else if (*line == '1')
		{
			tab = ft_split(line, ' ');
			size = ft_strlen(line) / 2 + 1;
			if (g_world.cols == 0)
				g_world.cols += size;
			i = -1;
			while (++i < size)
				g_game_map[j][i] = tab[i][0];
			j++;
			g_world.rows++;
		}
		else
			check_for_info(line);
		free_space(&line);
	}
	// check_missing_info();
}
