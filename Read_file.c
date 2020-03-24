/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 13:55:39 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/11 01:10:01 by hmellahi         ###   ########.fr       */
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

	if (g_infos[resolution]++)
		return (handle_error(DUPLICATE_RESOLUTION, FAIL));
	tab = ft_split(line + 1, ' ');
	validate_args(&tab, 2);
	g_screen.width = ft_atoi(tab[0]);
	g_screen.height = ft_atoi(tab[1]);
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
	//printf("%s has been loaded\n", path);
}

void	load_sprite(t_string line, int index)
{
	t_string	*tab;
	t_sprite	sprite;
	t_string	*tab2;

	tab = ft_split(line, '|');
	tab2 = ft_split(tab[0], ' ');
	if (tablen((void**)tab2) != 2)
		return (handle_error(INVALID_SPRITE_ARG, FAIL));
	sprite.path = ft_strjoin(tab2[1], ".xpm", 3);
	sprite.type = tab2[0][1];
	validate_args(&tab, 9);
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
	print_vector(sprite.pos_in_map);
	//fillCell(sprite.pos_in_map.x,sprite.pos_in_map.y,sprite.type);
	g_world.numofsprites++;
}

void validate_args(t_string **args, int nargs)
{
	int i;

	i = 1;
	while((*args)[i])
	{
		(*args)[i] = trim((*args)[i], " ");
		if (!isnumber((*args)[i]))
			return (handle_error(INVALID_SPRITE_ARG, FAIL));
		i++;
	}
	if (nargs != i)
		return (handle_error(INVALID_SPRITE_ARG, FAIL));
}

void    read_image(t_string line, int index)
{
	if (index <= 3)
	{
		g_infos[index]++;
		load_texture(line, index);
	}
	else
		load_sprite(line, index);
}

void    read_color(t_string line, int index, int space)
{
	t_string	*colors;
	t_string	*tab;
	int			i;

	if (g_infos[index]++)
		 return (handle_error(DUPLICATE_COLOR, FAIL));
	colors = ft_split(line + 1, ',');
	//if (tablen((void**)colors) != 3)
	//	return (handle_error(INVALID_COLORS, FAIL));
	// i = -1;
	// while(colors[++i])
	// {
	// 	colors[i] = trim(colors[i], " ");
	// 	if (!isnumber(colors[i]))
	// 		return (handle_error(INVALID_COLORS, FAIL));	
	// }
	validate_args(&colors, 3);
	g_world.colors[space] = rgb_to_int(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
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
	while (*line)
		if (!ft_strchr(usual, *line++))
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
	check_for_file(file_name);
	g_world.rows = 2;
	flag = 0;
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		tmp = trim(line, " \t");
		if (*tmp == '1')
		{
			g_world.cols = ft_strlen(line) > g_world.cols ? ft_strlen(line) : g_world.cols;
			g_world.rows++;
			flag = 1;
		}
		else if (*tmp != 0 && flag == 1)
			return (handle_error(INVALID_MAP, FAIL));
	}
	g_world.cols += 2;
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
		j = -1;
		g_world.map[i] = (char*)sf_malloc(g_world.cols + 1 * sizeof(char));
		g_world.map[i][g_world.cols] = 0;
		while (++j < g_world.cols)
			g_game_map[i][j] = ' ';
	}
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
				while (*line && *line != *str)
				{
					col++;
					line++;
				}
				PLAYERPOS = new_vector(BLOCK_SIZE * col + BLOCK_SIZE / 2, BLOCK_SIZE * row + BLOCK_SIZE / 2);
				if (*str == 'N')
					g_world.player.rotation.angle = 90;
				else if (*str == 'S')
					g_world.player.rotation.angle = -90;
				else if (*str == 'W')
						g_world.player.rotation.angle = 0;
				else
					g_world.player.rotation.angle = 180;
			}
		}
		str++;
	}
}

void    read_file(t_string file_name)
{
	int fd;
	char *line;
	int size;
	char **tab;
	t_string tmp;

	check_for_file(file_name);
	set_up_map(file_name);
	allocate_map();
	tab = ft_split(file_name, '.');
	fd = open(file_name, O_RDONLY);
	//if (ft_strcmp(tab[sizeof(tab) / sizeof(tab[0]) - 1] , "cub") != 0)
	//    handle_error(INVALID_FILE_NAME, FAIL);
	int j = 1;
	int i;
	int x = 1;
	while (x > 0)
	{
		x = get_next_line(fd, &line);
		tmp = trim(line, " \t");
		if (*tmp == '1')
		{
			size = ft_strlen(line);
			get_player_pos(line, j);
			i = 0;
			while (++i < g_world.cols)
				g_game_map[j][i] = (i - 1) < size ? line[i - 1] : ' ';
			//printf("%s\n", g_game_map[j]);
			j++;
		}
		else
			check_for_info(line);
		free_space(&line);
	}
	fillCell(11, 9, 'C');
	j = 0;
	while (++j < g_world.rows)
	{
		i = 0;
		while (++i < g_world.cols)
		{
			if (!ft_strchr("1 ", g_game_map[j][i]))
			{
				if (g_game_map[j][i + 1] == ' ' || g_game_map[j][i - 1] == ' ' || 
					g_game_map[j + 1][i] == ' ' || g_game_map[j - 1][i] == ' ')
				{
					//printf("%d|%d\n", i, j);
					//printf("%c | %c |%c |%c\n", g_game_map[j][i + 1], g_game_map[j + 1][i], g_game_map[j][i - 1], g_game_map[j - 1][i]);
					//return (handle_error(INVALID_MAP, FAIL));
				}
			}
		}
		printf("\n");
	}
	close(fd);
	//if (!is_info_full())
	//	return(handle_error(MISSING_INFO, FAIL));
	/*printf("\n\
        CCCCCCCCCCCCCUUUUUUUU     UUUUUUUUBBBBBBBBBBBBBBBBB   EEEEEEEEEEEEEEEEEEEEEE      333333333333333   DDDDDDDDDDDDD \n\
     CCC::::::::::::CU::::::U     U::::::UB::::::::::::::::B  E::::::::::::::::::::E     3:::::::::::::::33 D::::::::::::DDD  \n\
   CC:::::::::::::::CU::::::U     U::::::UB::::::BBBBBB:::::B E::::::::::::::::::::E     3::::::33333::::::3D:::::::::::::::DD \n\
  C:::::CCCCCCCC::::CUU:::::U     U:::::UUBB:::::B     B:::::BEE::::::EEEEEEEEE::::E     3333333     3:::::3DDD:::::DDDDD:::::D  \n\
 C:::::C       CCCCCC U:::::U     U:::::U   B::::B     B:::::B  E:::::E       EEEEEE                 3:::::3  D:::::D    D:::::D\n\
C:::::C               U:::::D     D:::::U   B::::B     B:::::B  E:::::E                              3:::::3  D:::::D     D:::::D\n\
C:::::C               U:::::D     D:::::U   B::::BBBBBB:::::B   E::::::EEEEEEEEEE            33333333:::::3   D:::::D     D:::::D\n\
C:::::C               U:::::D     D:::::U   B:::::::::::::BB    E:::::::::::::::E            3:::::::::::3    D:::::D     D:::::D\n\
C:::::C               U:::::D     D:::::U   B::::BBBBBB:::::B   E:::::::::::::::E            33333333:::::3   D:::::D     D:::::D\n\
C:::::C               U:::::D     D:::::U   B::::B     B:::::B  E::::::EEEEEEEEEE                    3:::::3  D:::::D     D:::::D\n\
C:::::C               U:::::D     D:::::U   B::::B     B:::::B  E:::::E                              3:::::3  D:::::D     D:::::D\n\
 C:::::C       CCCCCC U::::::U   U::::::U   B::::B     B:::::B  E:::::E       EEEEEE                 3:::::3  D:::::D    D:::::D \n\
  C:::::CCCCCCCC::::C U:::::::UUU:::::::U BB:::::BBBBBB::::::BEE::::::EEEEEEEE:::::E     3333333     3:::::3DDD:::::DDDDD:::::D  \n\
   CC:::::::::::::::C  UU:::::::::::::UU  B:::::::::::::::::B E::::::::::::::::::::E     3::::::33333::::::3D:::::::::::::::DD \n\
     CCC::::::::::::C    UU:::::::::UU    B::::::::::::::::B  E::::::::::::::::::::E     3:::::::::::::::33 D::::::::::::DDD   \n\
        CCCCCCCCCCCCC      UUUUUUUUU      BBBBBBBBBBBBBBBBB   EEEEEEEEEEEEEEEEEEEEEE      333333333333333   DDDDDDDDDDDDD\n\
		");
*/
}
