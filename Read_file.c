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


int		tablen(void **tab)
{
	int i;

	i = 0;
	while (*tab++)
		i++;
	return (i);
}

int		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		isnumber(t_string str)
{
	while (*str)
		if (!(ft_isdigit(*str++)))
			return (0);
	return (1);
}

void    read_resolution(t_string line)
{
	t_string *tab;
	t_string tmp;

	if (g_infos[resolution]++)
		return (handle_error(DUPLICATE_RESOLUTION, FAIL));
	tab = ft_split(line, ' ');
	//printf("[%d]\n", tablen((void**)tab));
	if (tablen((void**)tab) != 3)
		return (handle_error(INVALID_RESOLUTION, FAIL));
	tmp = ft_strtrim(tab[1], " ");
	if (!isnumber(tmp))
		return (handle_error(INVALID_RESOLUTION, FAIL));
	g_screen.width = ft_atoi(tmp);
	tmp = ft_strtrim(tab[2], " ");
	if (!isnumber(tmp))
		return (handle_error(INVALID_RESOLUTION, FAIL));
	g_screen.height = ft_atoi(tmp);
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

void	load_texture(t_string line, int index)
{
	t_string path;
	t_string *tab;

	if (g_infos[index])
		return (handle_error(DUPLICATE_TEXTURE, FAIL));
	tab = ft_split(line, ' ');
	if (tablen((void**)tab) != 2 || ft_strlen(tab[0]) != 2)
		return (handle_error(INVALID_PATH, FAIL));
	path = ft_strjoin(tab[1], ".xpm", 3);
	load_image(index, path, TEXTURE);
	printf("%s has been loaded\n", path);
}

void	load_sprite(t_string line, int index)
{
	t_string	*tab;
	t_sprite	sprite;
	t_string	*tab2;
	t_string	tmp;

	tab = ft_split(line, '|');
	tab2 = ft_split(tab[0], ' ');
	sprite.path = ft_strjoin(tab2[1], ".xpm", 3);
	sprite.type = tab2[0][1];
	tmp = ft_strtrim(tab[3], " ");
	//if (ft_isdigit(tmp))
//		return (handle_error(INVALID_SPRITE_INFO, FAIL));
	sprite.anim.isPlayOnAwake = ft_atoi(tmp);
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
	t_string	*colors;
	t_string	*tab;

	if (g_infos[index]++)
		 return (handle_error(DUPLICATE_COLOR, FAIL));
	//tab = ft_split(line, ' ');
	colors = ft_split(line + 2, ',');
	//tmp = ;
	g_world.colors[space] = rgb_to_int(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	
	//free_space(colors);
}

void    check_for_info(t_string line)
{
	if (*line == 'R')
		read_resolution(line);
	else if (line[0] == 'N')
		read_image(line, north_texture);
	else if (ft_strlen(line) >= 2 && line[0] == 'S' && line[1] == 'O')
			read_image(line, south_texture);
	else if (line[0] == 'W')
		read_image(line, east_texture);
	else if (line[0] == 'E')
		read_image(line, west_texture);
	else if (line[0] == 'S' && line[1] != 'O')
		read_image(line, sprite_texture);
	else if (line[0] == 'F')
		read_color(line, floor_color, ground);
	else if (line[0] == 'C')
		read_color(line, ceil_color, skybox);
	//else
	//	return (handle_error(INVALID_FROMAT,FAIL));
}

int		is_info_full()
{
	int i;

	i = -1;
	while (++i < 9)
		if (g_infos[i] == 0)
			return (0);
	return (1);
}

void	check_line(t_string line)
{
	t_string usual;

	usual = "1RNSWESFC";
	if (!ft_strchr(usual, line[0]))
		handle_error(INVALID_MAP, FAIL);
}

void	set_up_map(t_string file_name)
{
	int 		fd;
	int 		ret;
	t_string	line;
	t_string	*tab;
	int			flag;
	t_string	tmp;
	fd = open(file_name, O_RDONLY);
	//check_for_file(file_name);
	g_world.rows = 1;
	g_world.cols = 1;
	flag = 0;
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		tmp = ft_strtrim(line, " ");
		//printf("%s\n", line);
		check_line(tmp);
		if (*tmp == '1')
		{
			g_world.cols = ft_strlen(line) > g_world.cols ? ft_strlen(line) : g_world.cols;
			g_world.rows += 1;
			flag = 1;
		}
		else if (tmp[0] != 0 && flag == 1)
			return (handle_error(INVALID_MAP, FAIL));
	}
	//printf("[%d | %d]\n", g_world.cols, g_world.rows);
	close(fd);
}

void	allocate_map()
{
	int i;
	int j;

	i = -1;
	g_world.map = (char**)sf_malloc((g_world.rows + 1) * sizeof(char*));
	g_world.map[g_world.rows] = 0;
	while (++i < g_world.rows)
	{
		g_world.map[i] = (char*)sf_malloc(g_world.cols + 1 * sizeof(char));
		g_world.map[i][g_world.cols] = 0;	
	}
	memset(&g_world.map, 48, g_world.rows * g_world.cols);
	i = -1;
	j = -1;
	/*while (++i < g_world.rows)
	{
		j = -1;
		while (++j < g_world.cols)
			g_world.map[i][j] = ' ';
			//printf("%c", g_world.map[i][j]);
		//printf("\n");
	}*/
}

void    read_file(t_string file_name)
{
	int fd;
	char *line;
	int size;
	char **tab;
	t_string tmp;

	set_up_map(file_name);
	allocate_map();
	tab = ft_split(file_name, '.');
	//if (ft_strcmp(tab[sizeof(tab) / sizeof(tab[0]) - 1] , "cub") != 0)
	//    handle_error(INVALID_FILE_NAME, FAIL);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		handle_error(NON_EXISTENECE_FILE, FAIL);
	int j = 1;
	int i;
	int x = 1;
	//char *p = "wsne";
	while (x > 0)
	{
		x = get_next_line(fd, &line);
		tmp = ft_strtrim(line, " ");
		//if (*tmp == '1' && !is_info_full())
		//	return (handle_error(MISSING_INFO, FAIL));
		if (*tmp == '1')
		{
			tab = ft_split(line, ' ');
			size = ft_strlen(line);
			if (g_world.cols == 0)
				g_world.cols += size;
			i = 1;
			while (++i < size)
				g_game_map[j++][i++] = tab[i][0];
			g_world.rows++;
		}
		else
			check_for_info(line);
		free_space(&line);
	}
	// /*
	close(fd);
	if (!is_info_full())
		return(handle_error(MISSING_INFO, FAIL));
// 	printf('
// 	// ******  **     ** ******   ********  ****  *******  
//  // **////**/**    /**/*////** /**/////  */// */**////** 
// // **    // /**    /**/*   /** /**      /    /*/**    /**
// //**       /**    /**/******  /*******    *** /**    /**
// //**       /**    /**/*//// **/**////    /// */**    /**
// //**    **/**    /**/*    /**/**       *   /*/**    ** 
//  //****** //******* /******* /********/ **** /*******  
//   //////   ///////  ///////  ////////  ////  ///////   
//   ');

}
