/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 13:55:39 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/03 06:20:18 by hmellahi         ###   ########.fr       */
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

t_image   load_image(t_pair *content)
{
	t_string	path;
	int			index;

	index = *((int*)content->a);
	path = (t_string)content->b;

	printf("image has been loaded %s at %d\n", path, index);

	g_textures[index].img = mlx_xpm_file_to_image(g_mlx, path, &g_textures[0].width, &g_textures[0].height);
	g_textures[index].data = (int *)mlx_get_data_addr(g_textures[index].img, &g_textures[index].bits_per_pixel, &g_textures[index].bits_per_pixel, &g_textures[index].endian);
	return (g_textures[index]);
}

void    read_image(t_string line, int index)
{
	t_string path;
	if (g_infos[index])
		return (handle_error(DUPLICATE_TEXTURE, FAIL));
	//printf("%s\n", line);
	path = ft_strjoin("assets/sprites/", ft_strjoin(line + 5, ".xpm", 3), 3);
	//load_image(index, path);
	//printf("%s | %d", path, index);
	t_pair *p = make_pair(&index, &path);
	//printf("%d || %s\n", (*(int*)p->a), (t_string)p->b);
	printf("has been loaded %s\n", path);
	if (index == 4)
		g_world.sprites[0].path = path;
	//push_back(&(g_world.images),  new_lst(make_pair(&index, &path)));
	g_infos[index]++;
}

void    read_color(t_string line, int index, int space)
{
	t_string *colors;

	if (g_infos[index]++)
		 return (handle_error(DUPLICATE_COLOR, FAIL));
	colors = ft_split(line + 2, ',');
	g_world.colors[space] = rgb_to_int(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));	
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
		   /* while(*p)
				if (ft_strchr(tab[]))
			if (ft_strchr(p))*/
				
			size = ft_strlen(line) / 2 + 1;
			if (g_world.cols == 0)
				g_world.cols += size;
			i = -1;
			while (++i < size)
				g_game_map[j][i] = tab[i][0];
			j++;
			g_world.rows++;
			free_space(tab);
		}
		else
			check_for_info(line);
		free_space(&line);
	}
	free_space(tab);
	// check_missing_info();
}
