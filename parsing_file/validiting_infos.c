/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validiting_infos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 02:35:16 by marvin            #+#    #+#             */
/*   Updated: 2020/03/25 02:35:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
