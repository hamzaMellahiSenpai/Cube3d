/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 09:51:10 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/08 05:48:31 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_string messages[] = {
	"Invalid file name!",
	"Missing info",
	"Duplicate Texture",
	"Duplicate Color",
	"Duplicate Resolution",
	"Stop Idiot! You have reached the range of g_screen",
	"Invalid Map",
	"NO SUCH FILE OR DIRECTORY",
	"Allocation Failed",
	"PROCCESS_CANT_BE_CREATED",
	"INVALID_PATH",
	"INVALID_SPRITE_PLACEMENT"
};

void		free_map()
{

}

void		handle_error(int error_index, int status)
{
	free_map();
	perror(messages[error_index]);
	free_all(status);
}

void	check_for_file(t_string file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		//perror("NO SUCH FILE OR DIRECTORY : ");
		perror(file_name);
		free_all(FAIL);
	}
}
