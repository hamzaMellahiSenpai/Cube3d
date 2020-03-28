/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 03:26:18 by marvin            #+#    #+#             */
/*   Updated: 2020/03/25 03:26:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	fill_map(t_string file_name, t_string line)
{
	int			j;
	int			i;
	int			fd;
	int			size;
	t_string	tmp;

	fd = open(file_name, O_RDONLY);
	j = 1;
	while (get_next_line(fd, &line))
	{
		tmp = trim(line, " \t");
		if (*tmp == '1')
		{
			size = ft_strlen(line);
			get_player_pos(line, j);
			i = 0;
			while (++i < g_world.cols)
			{
				g_game_map[j][i] = (i - 1) < size ? line[i - 1] : ' ';
				if (!ft_strchr("10NWSE ", g_game_map[j][i]))
					return (handle_error(INVALID_MAP, FAIL));
			}
			j++;
		}
		else
			check_for_info(line);
	}
	close(fd);
}

void	check_closed_map()
{
	int j;
	int i;

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
					return (handle_error(INVALID_MAP, FAIL));
			}
		}
	}
	if (!is_info_full())
		return(handle_error(MISSING_INFO, FAIL));
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

void	get_rows_cols(t_string file_name)
{
	int 		fd;
	t_string	line;
	int			flag;
	t_string	tmp;

	check_for_file(file_name);
	fd = open(file_name, O_RDONLY);
	g_world.rows = 2;
	flag = 0;
	while (get_next_line(fd, &line))
	{
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